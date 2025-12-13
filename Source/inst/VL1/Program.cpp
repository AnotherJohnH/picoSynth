//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#include <cstdio>

#include "Program.h"

namespace VL1 {

Program program[NUM_PROGRAM] =
{
   { 0x7f, 0x40, 1,  0, 0, 4, 5, 3, 2, 0, 0,  "Piano"   },
   { 0x7f, 0x40, 1,  1, 0, 0, 9, 9, 6, 3, 0,  "Fantasy" },
   { 0x7f, 0x40, 1,  2, 3, 0, 9, 9, 1, 3, 0,  "Violin"  },
   { 0x7f, 0x40, 1,  3, 3, 0, 9, 9, 1, 3, 0,  "Flute"   },
   { 0x7f, 0x40, 1,  4, 1, 0, 7, 1, 2, 0, 0,  "Guitar"  },
   { 0x7f, 0x40, 1,  0, 0, 0, 9, 0, 0, 0, 0,  "ADSR"    }
};

void Program::print() const
{
   printf("PATCH %s\n", name);
}

} // namespace VL1
