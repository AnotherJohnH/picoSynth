//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "SIG/Osc/Base.h"
#include "SIG/Gain.h"

namespace Osc {

class Ramp : public Base
{
public:
   Ramp() = default;

   Sample operator()()
   {
      Sample sample = uphase2sample(phase);

      float t = uphase2float(phase - UPHASE_HALF);
      sample -= polyBLEP(t);

      phase += delta;

      return gain(sample);
   }

   Sample operator()(Sample mod_)
   {
      setDelta(modDelta(mod_));

      Sample sample = uphase2sample(phase);

      float t = uphase2float(phase - UPHASE_HALF);
      sample -= polyBLEP(t);

      phase += delta;

      return gain(sample);
   }

   Gain gain{};
};

} // namespace Osc
