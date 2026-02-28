//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "Patch.h"

namespace SH_101 {

const unsigned NUM_PROGRAM = 1;

const Patch program[NUM_PROGRAM] =
{
//   LFO        | VCO                  | SOURCE                      | VCF                     | ENV                          | VCA     |
//   Wave     R | Mod  R  Wdth Pwm Src | Sqr  Rmp  Sub  Mode     Nse | Freq Res  Env  Mod  Kbd | Mode     A    D    S    R    | Mode    |
   { LFO_TRI, 0,  0.0, 0, 0.0, PWM_MAN,  9.9, 9.9, 0.0, SUB_1OS, 0.0,  9.9, 0.0, 0.0, 0.0, 0.0,  ENV_GTE, 0.0, 0.0, 9.9, 0.0,   VCA_GTE,  "INIT"}
};

} // namespace SH_101
