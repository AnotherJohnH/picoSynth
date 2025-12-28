//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include <cstdint>

#if defined(SIG_FP64)
using Sample = double;
using Phase  = double;
#else
using Sample = float;
using Phase  = float;
#endif

using UPhase = uint32_t;

#if defined(SIG_44_1KHz)
static const unsigned SAMPLE_RATE{44100};   //!< 44.1 kHz
#else
static const unsigned SAMPLE_RATE{48000};   //!< 48 kHz
#endif

//! Convert 32-bit unsigned phase to floatin-point -1.0..1.0 (pi)
inline Sample uphase2sample(UPhase uphase_)
{
   return Sample(int32_t(uphase_)) / 0x80000000;
}

//! Convert 32-bit unsigned phase to floating-point 0.0..1.0 (2pi)
inline Phase uphase2float(UPhase uphase_)
{
   return Phase(uphase_ >> 1) / 0x80000000;
}

//! Convert floating point sample -1.0..1.0 to 32-bit unsigned phase
inline UPhase sample2uphase(Sample sample_)
{
   return UPhase(int32_t(sample_ * 0x7FFFFFFF));
}
