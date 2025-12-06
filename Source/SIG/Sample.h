//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include <cstdint>

using Sample = float;
using Phase  = uint32_t;

//! Convert phase to -1.0..1.0 (pi)
inline Sample phase2sample(Phase phase_)
{
   return Sample(int32_t(phase_)) / 0x80000000;
}

//! Convert sample -1.0..1.0 to 32-bit phase
inline Phase sample2phase(Sample sample_)
{
   return int32_t(sample_ * 0x7FFFFFFF);
}

static const unsigned SAMPLE_RATE{48000};   //!< 48 kHz
