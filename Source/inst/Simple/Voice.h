//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "SIG/SIG.h"

#include "Effect.h"
#include "Patch.h"

namespace Simple {

class Voice
{
public:
   Voice()
   {
      //lfo.setFreq(30.0f, 1600);
      lfo.setFreq(30.0f);
      lfo_out.setUpdateRate(1600);
   }

   void program(const Patch* patch_)
   {
      osc.gain = patch_->value / 127.0f;
   }

   void noteOn(uint8_t note_, uint8_t velocity_)
   {
      osc.setNote(note_);
      osc.sync();

      gain = 1.0;
   }

   void noteOff(uint8_t velocity_)
   {
      gain = 0.0;
   }

   void tick(const Effect& effect_, unsigned n_)
   {
      lfo_out = lfo();
   }

   SIG::Signal sample(const Effect& effect_)
   {
      return lfo();
   }

private:
   SIG::Osc::Sine   lfo{};
   SIG::LinSlew     lfo_out{};
   SIG::Osc::Sine   osc{};
   SIG::Gain        gain{0.0};
};

} // namespace Simple
