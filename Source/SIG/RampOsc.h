//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "OscBase.h"
#include "Gain.h"

class RampOsc : public OscBase
{
public:
   RampOsc() = default;

   Sample operator()(Sample mod_ = 0)
   {
      Sample sample = phase2sample(phase);

      phase += delta + sample2phase(mod_);

      return gain(sample);
   }

   Gain gain{};
};
