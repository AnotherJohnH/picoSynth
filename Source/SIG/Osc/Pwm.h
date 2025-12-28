//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "SIG/Osc/Base.h"
#include "SIG/Gain.h"

namespace Osc {

template <Sample HIGH, Sample LOW>
class PwmShift : public Base
{
public:
   PwmShift() = default;

   //! Set pulse width 0.0 => square
   void setWidth(Sample width_)
   {
      limit = UPHASE_HALF + sample2uphase(width_);
   }

   Sample operator()()
   {
      Sample sample = phase < limit ? HIGH : LOW;

      float t = uphase2float(phase);
      sample += polyBLEP(t);
      t = uphase2float(phase - limit);
      sample -= polyBLEP(t);

      phase += delta;

      return gain(sample);
   }

   Sample operator()(Sample mod_)
   {
      setDelta(modDelta(mod_));

      Sample sample = phase < limit ? HIGH : LOW;

      float t = uphase2float(phase);
      sample += polyBLEP(t);
      t = uphase2float(phase - limit);
      sample -= polyBLEP(t);

      phase += delta;

      return gain(sample);
   }

   Gain gain{};

private:
   UPhase limit{UPHASE_HALF};
};

using Pwm = PwmShift<+1.0f,-1.0f>;

} // namespace Osc
