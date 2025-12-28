//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "SIG/Osc/Base.h"
#include "SIG/Gain.h"

namespace Osc {

class Triangle : public Base
{
public:
   Triangle() = default;

   Sample operator()()
   {
      UPhase phase_shift = phase + UPHASE_QUARTER;

      UPhase p = phase_shift >= UPHASE_HALF ? -phase * 2
                                          : +phase * 2;

      Sample sample = uphase2sample(p);

      phase += delta;

      return gain(sample);
   }

   Sample operator()(Sample mod_)
   {
      UPhase phase_shift = phase + UPHASE_QUARTER;

      UPhase p = phase_shift >= UPHASE_HALF ? -phase * 2
                                          : +phase * 2;

      Sample sample = uphase2sample(p);

      phase += modDelta(mod_);

      return gain(sample);
   }

   Gain gain{};
};

} // namespace Osc
