//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "SIG/PwmOsc.h"
#include "SIG/PulseOsc.h"
#include "SIG/TriOsc.h"
#include "SIG/Noise.h"
#include "SIG/Adsr.h"
#include "SIG/Gain.h"

#include "VL1/Program.h"

namespace VL1 {

class Voice
{
public:
   Voice()
   {
      lpf.setFreq(3000);
      lpf.setQ(0.1);

      perc_env.setAttack_mS(0);
      perc_env.setSustain(0);
      perc_env.setRelease_mS(0);
   }

   void program(const Program* patch_)
   {
      transpose = (patch_->octave - 1) * 12;

      switch(patch_->wave)
      {
      case 0: // Piano
         melody_osc.setPattern(uint16_t(0b1111111111100000));
         break;

      case 1: // Fantasy
         melody_osc.setPattern(uint16_t(0b1111000011110000));
         break;

      case 2: // Violin
         melody_osc.setPattern(uint16_t(0b1111011101101010));
         break;

      case 3: // Flute
         melody_osc.setPattern(uint16_t(0b1111111100000000));
         break;

      case 4: // Guitar 1
         melody_osc.setPattern(uint16_t(0b1000000100000000));
         transpose -= 12;
         break;

      case 5: // Guitar 2
         melody_osc.setPattern(uint16_t(0b1011110011000000));
         transpose -= 12;
         break;

      case 6: // English Horn
         melody_osc.setPattern(uint16_t(0b1100000000000000));
         transpose -= 12;
         break;

      case 7: // Electro-Sound 1 (octave modulated Piano)
         melody_osc.setPattern(uint16_t(0b1111111111100000));
         break;

      case 8: // Electro-Sound 2 (octave modulated Fantasy)
         melody_osc.setPattern(uint16_t(0b1111000011110000));
         break;

      case 9: // Electro-Sound 3 (octave modulated Flute)
         melody_osc.setPattern(uint16_t(0b1111111100000000));
         break;
      }

      //melody_env.setAttack_mS(patch_->attack_time);
      //melody_env.setDecay_mS(patch_->decay_time);
      //melody_env.setSustain(patch_->sustain_level);
      //melody_env.setRelease_mS(patch_->release_time);
   }

   void noteOn(uint8_t note_, uint8_t velocity_)
   {
      switch(note_)
      {
      case 48: // Po
         perc_osc.sync();
         perc_osc.setFreq(770);
         perc_env.setDecay_mS(30);
         perc_env.on();
         mode = PERC_OSC;
         break;

      case 49: // Pi
         perc_osc.sync();
         perc_osc.setFreq(1667);
         perc_env.setDecay_mS(20);
         perc_env.on();
         mode = PERC_OSC;
         break;

      case 50: // Sha
         perc_env.setDecay_mS(160);
         perc_env.on();
         mode = PERC_NOISE;
         break;

      default:
         melody_osc.setNote(note_ + transpose);
         melody_osc.sync();
         melody_env.on();
         mode = MELODY;
         break;
      }
   }

   void noteOff(uint8_t velocity_)
   {
      melody_env.off();
   }

   Sample sample()
   {
      Sample value;

      switch(mode)
      {
      case PERC_OSC:   value = perc_env() * perc_osc();          break;
      case PERC_NOISE: value = perc_env() * perc_noise();        break;
      case MELODY:     value = melody_env() * lpf(melody_osc()); break;
      }

      return gain(value);
   }

   static Sample effect(Sample sample_)
   {
      return sample_;
   }

private:
   enum Mode { PERC_OSC, PERC_NOISE, MELODY };

   Mode           mode{};
   Adsr           melody_env{};
   PulseOsc       melody_osc{};
   signed         transpose{0};
   Filter::BiQuad lpf{Filter::LOPASS};
   Adsr           perc_env{};
   PwmOsc         perc_osc{};
   Noise          perc_noise{};
   TriOsc         tremlo_osc{};
   TriOsc         vibrato_osc{};
   Gain           gain{};
};

} // namespace VL1
