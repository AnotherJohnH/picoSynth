//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include <cstdint>

namespace Juno106 {

struct Traits
{
   static const unsigned NUM_VOICES     = 6;
   static const unsigned DIVISOR        = 8;
   static const uint8_t  MIDI_MANUF_ID  = 0x41; // Roland
   static const unsigned MAX_SYSEX_SIZE = 3 + 18;
};

} // namespace Juno106
