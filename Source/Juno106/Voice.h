//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "Juno106/SysEx.h"

#include "SIG/TriOsc.h"
#include "SIG/RampOsc.h"
#include "SIG/PulseOsc.h"
#include "SIG/Noise.h"
#include "SIG/LfoEnv.h"
#include "SIG/Adsr.h"
#include "SIG/Gain.h"

namespace Juno106 {

class Voice
{
public:
   Voice()
   {
      lfo_env.setAttack_mS(200);
   }

   //! Program a voice from a SYSEX patch
   void program(const SysEx* patch_)
   {
      lfo_env.setDelay_mS(3000 * patch_->lfo_delay / 127);

      lfo.setFreq_dHz(1 + 299 * patch_->lfo_rate / 127);
      lfo.gain = 127;

      switch(patch_->range)
      {
      case SysEx::RANGE_16: transpose = -12; break;
      case SysEx::RANGE_8:  transpose =   0; break;
      case SysEx::RANGE_4:  transpose = +12; break;
      default:              transpose =   0; break;
      }

      updateDCOFreq();

      if (patch_->dco_pwm_man)
      {
         dco_pwm.setWidth(patch_->dco_pwm * 112 / 128);
         dco_pwm_lfo = false;
      }
      else
      {
         dco_pwm_lfo_gain = patch_->dco_pwm * Sample::MAX * 2 / 127;
         dco_pwm_lfo      = true;
      }

      dco_lfo = patch_->dco_lfo << 8;

      dco_saw.gain = patch_->saw ? 127 : 0;
      dco_pwm.gain = patch_->pwm ? 127 : 0;
      dco_sub.gain = patch_->sub_osc_level;
      noise.gain   = patch_->noise_level;

      env.setAttack_mS(1 + patch_->env_attack * 3000 / 127);
      env.setDecay_mS(1 + patch_->env_decay * 12000 / 127);
      env.setSustain(patch_->env_sustain);
      env.setRelease_mS(1 + patch_->env_release * 12000 / 127);

      vca.setGain(patch_->vca_level);
      vca_gate = patch_->vca_gate;
   }

   void mute()
   {
      env.mute();
      gate = 0;
   }

   //! Note on
   void on(uint8_t note_, uint8_t velocity_)
   {
      note = note_;

      updateDCOFreq();

      lfo.sync();
      dco_saw.sync();
      dco_sub.sync();
      dco_pwm.sync();

      lfo_env.on();
      env.on();

      gate = Sample::MAX << 1;
   }

   //! Note off
   void off(uint8_t velocity_)
   {
      env.off();

      gate = 0;
   }

   //! Get next sample

   Sample sample()
   {
      Sample lfo_out = lfo() * lfo_env();

      if (dco_pwm_lfo)
      {
         lfo_out = lfo_out * dco_pwm_lfo_gain;

         dco_pwm.setWidth((0x8000 + lfo_out) * 112 / 0x10000);
      }

      Sample fmod = int32_t(lfo_out * dco_lfo) << 8;

      Sample dco_out = (dco_saw(fmod) + dco_pwm(fmod) + dco_sub(fmod) + noise()) / 4;

      Sample env_out = env();

      return vca(dco_out * (vca_gate ? gate : env_out));
   }

private:
   void updateDCOFreq()
   {
      dco_saw.setNote(transpose + note);
      dco_sub.setNote(transpose + note - 12);
      dco_pwm.setNote(transpose + note);
   }

   signed   transpose{0};
   uint8_t  note{};
   TriOsc   lfo{};
   LfoEnv   lfo_env{};
   Sample   dco_lfo{};
   Sample   dco_pwm_lfo_gain{};
   bool     dco_pwm_lfo{};
   RampOsc  dco_saw{};
   PulseOsc dco_pwm{};
   PulseOsc dco_sub{};
   Noise    noise{};
   Adsr     env{};
   Gain     vca{};
   bool     vca_gate{};
   Sample   gate{};
};

} // namespace Juno106
