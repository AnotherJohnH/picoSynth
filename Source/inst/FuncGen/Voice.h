//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "SIG/SIG.h"

#include "Control.h"

namespace FuncGen {

class Voice
{
public:
   Voice() = default;

   void program(const Control* control_)
   {
      osc.gain = control_->value / 127.0f;
   }

   void noteOn(uint8_t note_, uint8_t velocity_)
   {
      osc.setNote(note_);
   }

   void noteOff(uint8_t velocity_)
   {
   }

   void tick(const Effect& effect_, unsigned n_) {}

   Signal sample(Effect& effect_)
   {
      Signal sample{};

      switch(mode)
      {
      case SINE:     sample = sine();     break;
      case TRIANGLE: sample = triangle(); break;
      case PWM:      sample = pwm();      break;
      case RAMP:     sample = ramp();     break;
      case NOISE:    sample = noise();    break;
      }

      return gain(sample);
   }

   static Signal effect(Sample sample_)
   {
      return sample_;
   }

private:
   Osc::Sine     sine{};
   Osc::Triangle triangle{};
   Osc::Pwm      pwm{};
   Osc::Ramp     ramp{};
   Osc::Noise    noise{};
   Gain          gain{0.0};
};

} // namespace FuncGen
