//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include "Patch.h"

namespace SH_101 {

const unsigned NUM_PROGRAM = 4;

const Patch program[NUM_PROGRAM] =
{
// | LFO          | VCO                  | SOURCE                      | VCF                     | VCA     | ENV                         | VCA     |
// | Rate Wave    | Mod  R  Wdth Pwm Src | Sqr  Rmp  Sub  Mode     Nse | Freq Res  Env  Mod  Kbd | Mode    | Mode     A    D    S    R   | Mode    |
   { 0.0, LFO_TRI,  0.0, 0, 0.0, PWM_MAN,  9.9, 9.9, 0.0, SUB_1OS, 0.0,  9.9, 0.0, 0.0, 0.0, 0.0,  VCA_GTE,  ENV_GTE, 0.0, 0.0, 9.9, 0.0,  "INIT"},
   { 5.0, LFO_TRI,  0.0, 1, 0.0, PWM_MAN,  9.9, 0.0, 0.0, SUB_1OS, 0.0,  1.5, 0.0, 5.0, 3.5, 9.0,  VCA_ENV,  ENV_GTE, 2.0, 0.0, 9.9, 1.5,  "Flute"},
   { 5.0, LFO_TRI,  1.0, 1, 0.0, PWM_MAN,  9.9, 0.0, 0.0, SUB_1OS, 0.0,  4.0, 0.0, 4.0, 0.0, 8.0,  VCA_ENV,  ENV_GTE, 2.0, 0.0, 9.9, 1.5,  "Clarinet"},
   { 5.0, LFO_TRI,  1.0, 1, 8.5, PWM_MAN,  9.9, 0.0, 0.0, SUB_1OS, 0.0,  6.0, 5.5, 0.0, 0.0, 4.0,  VCA_ENV,  ENV_GTE, 1.5, 0.0, 9.9, 2.0,  "Oboe" },
};

} // namespace SH_101
