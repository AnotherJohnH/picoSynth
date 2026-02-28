//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include <cmath>

#include "SIG/SIG.h"

#include "NoEffect.h"
#include "Patch.h"
#include "Control.h"

namespace SH_101 {

class Voice
{
public:
   Voice()
   {
      noise.gain = 3.8f;
      noise_filter.setFreq(1800.0f);
      noise_filter.setQ(0.40f);
   }

   void program(const Patch* patch_)
   {
      // LFO
      lfo_wave = patch_->lfo_wave;
      float lfo_freq = 30.0f * powf(2.0f, 255.0f * (patch_->lfo_rate * 0.1f - 1.0f) / 51.0f);
      lfo_triangle.setFreq(lfo_freq);
      lfo_square.setFreq(lfo_freq);
      lfo_random.setFreq(lfo_freq);

      // VCO
      vco_octave = patch_->vco_range;
      vco_rect.setWidth(patch_->vco_pulse_width * 0.092);

      // SOURCE
      vco_rect.gain = patch_->source_square * -0.03;
      vco_ramp.gain = patch_->source_ramp   * +0.04;
      vco_sub.gain  = patch_->source_sub    * -0.02;
      noise_mix     = patch_->source_noise  * +0.07;

      switch(patch_->source_sub_mode)
      {
      case SUB_2OS: vco_sub_octave = -2; break;
      case SUB_1OS: vco_sub_octave = -1; break;
      case SUB_2OP: vco_sub_octave = -2; break;
      }

      updateFreq();

      // VCF
      vcf.setFreq(16000.0f * powf(2.0f, 255.0f * (patch_->vcf_freq * 0.1f - 1.0f) / 21.0f));
      vcf.setQ(0.4f + patch_->vcf_res * 1.5f);

      // ENV
      env_mode = patch_->env_mode;
      env.setAttack_mS(unsigned(patch_->env_a* 400));
      env.setDecay_mS(unsigned(patch_->env_d* 1000));
      env.setSustain(patch_->env_s * 0.1f);
      env.setRelease_mS(unsigned(patch_->env_r * 1000));

      // VCA
      vca_mode = patch_->vca_mode;
   }

   void program(const Control* control_)
   {
      volume = SIG::dBGainLookup(control_->volume);

      //noise_filter.setFreq(1000.0f + control_->tune1 * 2000.0f);
      //noise_filter.setQ(0.1 + control_->tune2);
      //noise.gain = control_->tune3 * 10.0f;
   }

   void noteOn(uint8_t note_, uint8_t velocity_)
   {
      note = note_;

      updateFreq();

      vco_rect.sync();
      vco_ramp.setPhase(SIG::UPHASE_HALF);
      vco_sub.sync();

      env.on();
      gate = 1.0;
   }

   void noteOff(uint8_t velocity_)
   {
      env.off();
      gate = 0.0;
   }

   void tick(const NoEffect& effect_, unsigned n_) {}

   SIG::Signal sample(const NoEffect& effect_)
   {
      SIG::Signal noise_out = noise_filter( noise());
      SIG::Signal env_out   = env();
      SIG::Signal lfo_out;

      switch(lfo_wave)
      {
      case LFO_TRI:   lfo_out = lfo_triangle(); break;
      case LFO_SQR:   lfo_out = lfo_square();   break;
      case LFO_RAND:  lfo_out = lfo_random();   break;
      case LFO_NOISE: lfo_out = noise_out;      break;
      }

      (void) lfo_out;

      SIG::Signal source_mix = vco_rect() +
                               vco_ramp() +
                               vco_sub() +
                               noise_mix(noise_out);

      vca = vca_mode == VCA_ENV ? env_out : gate;

      return volume( vca( vcf( source_mix )));
   }

private:
   void updateFreq()
   {
      vco_rect.setNote(note + vco_octave * 12);
      vco_ramp.setNote(note + vco_octave * 12);
      vco_sub.setNote(note + vco_sub_octave * 12);
   }

   SIG::Osc::Noise      noise{};
   SIG::Filter::BiQuad  noise_filter{SIG::Filter::LOPASS};

   // LFO
   LfoWave            lfo_wave{};
   SIG::Osc::Triangle lfo_triangle{};
   SIG::Osc::Square   lfo_square{};
   SIG::Osc::Random   lfo_random{};

   // VCO
   uint8_t         note;              // Currently playing MIDI note
   unsigned        vco_octave{};
   unsigned        vco_sub_octave{};
   SIG::Osc::Pwm   vco_rect{};
   SIG::Osc::Ramp  vco_ramp{};
   SIG::Osc::Pwm   vco_sub{};

   // SOURCE
   SIG::Gain       noise_mix;

   // VCF
   SIG::Filter::BiQuad vcf{SIG::Filter::LOPASS};

   // ENV
   EnvMode        env_mode{};
   SIG::Float     gate{};
   SIG::Env::Adsr env{};

   // VCA
   VcaMode   vca_mode{};
   SIG::Gain vca{};

   // AMP
   SIG::Gain volume{};
};

} // namespace SH_101
