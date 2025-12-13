//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "../SynthVoice.h"
#include "Simple/Voice.h"

namespace Simple {

class Synth : public ::SynthVoice<Voice, /* NUM_VOICES */ 16>
{
public:
   Synth() = default;

private:
   void synthInit() override
   {
      setText(0, "     simple     ");
   }
};

} // namespace Simple
