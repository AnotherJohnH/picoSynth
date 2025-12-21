//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "SIG/Osc/Base.h"
#include "SIG/Gain.h"

namespace Osc {

class Pwm : public Base
{
public:
   Pwm() = default;

   //! Set pulse width 0.0 => square
   void setWidth(Sample width_)
   {
      limit = PHASE_HALF + sample2phase(width_);
   }

   Sample operator()()
   {
      Sample sample = phase >= limit ? -1.0f : +1.0f;

      phase += delta;

      return gain(sample);
   }

   Sample operator()(Sample mod_)
   {
      Sample sample = phase >= limit ? -1.0f : +1.0f;

      phase += modDelta(mod_);

      return gain(sample);
   }

   Gain gain{};

private:
   Phase limit{PHASE_HALF};
};

} // namespace Osc
