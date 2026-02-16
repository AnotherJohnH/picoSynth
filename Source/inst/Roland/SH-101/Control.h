//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

namespace SH_101 {

struct Control
{
   float tuning{0.0};
   float volume{0.0};
   float hpf_freq{80.0};
   float hpf_q{1.20};
};

} // namespace SH_101
