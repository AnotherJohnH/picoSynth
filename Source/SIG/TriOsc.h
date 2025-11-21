//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "OscBase.h"
#include "Gain.h"

class TriOsc : public OscBase
{
public:
   TriOsc() = default;

   Sample operator()(Sample mod_ = 0)
   {
      Phase phase_shift = phase + PHASE_QUARTER;

      Phase p = phase_shift >= PHASE_HALF ? -phase * 2
                                          : +phase * 2;

      Sample sample = Sample::rescale(p);

      phase += delta + mod_;

      return gain(sample);
   }

   Gain gain{};
};
