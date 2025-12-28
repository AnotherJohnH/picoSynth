//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "SIG/SIG.h"

#include "VL1/Program.h"

namespace VL1 {

class Effect
{
public:
   Effect() = default;

   void program(const Program* program_)
   {
   }

   void program(const Control* control_)
   {
   }

   void pre()
   {
   }

   Sample post(Sample sample_)
   {
      return sample_;
   }
};

} // namespace VL1
