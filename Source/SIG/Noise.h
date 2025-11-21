//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "Sample.h"

class Noise
{
public:
   Noise() = default;

   Sample operator()()
   {
      noise_state ^= noise_state << 13;
      noise_state ^= noise_state >> 17;
      noise_state ^= noise_state << 5;

      return gain(Sample::rescale(noise_state));
   }

   Gain gain{};

private:
   uint32_t noise_state{1};
};
