//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "OscBase.h"
#include "Gain.h"

class PulseOsc : public OscBase
{
public:
   PulseOsc() = default;

   void setWidth(uint8_t value7_)
   {
      limit = (128 + value7_) << 24;
   }

   Sample operator()(Sample mod_ = 0)
   {
      Sample sample = phase >= limit ? Sample::MIN
                                     : Sample::MAX;

      phase += delta + mod_;

      return gain(sample);
   }

   Gain gain{};

private:
   Phase limit = PHASE_HALF;
};
