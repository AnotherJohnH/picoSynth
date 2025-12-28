//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include <cmath>

#include "SIG/Osc/Base.h"
#include "SIG/Gain.h"

namespace Osc {

class Sine : public Base
{
public:
   Sine() = default;

   Sample operator()()
   {
      float theta = uphase2sample(phase) * M_PI;

      phase += delta;

      return gain(sinf(theta));
   }

   Sample operator()(Sample mod_)
   {
      float theta = uphase2sample(phase) * M_PI;

      phase += modDelta(mod_);

      return gain(sinf(theta));
   }

   Gain gain{};
};

} // namespace Osc
