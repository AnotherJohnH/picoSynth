//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "../SynthVoice.h"
#include "VL1/Voice.h"
#include "VL1/Program.h"

namespace VL1 {

class Synth : public ::SynthVoice<Voice, /* NUM_VOICES */ 2>
{
public:
   Synth() = default;

private:
   void synthInit() override
   {
      setText(0, "   CASIO VL-1   ");

      setPatch(program[0]);
   }

   void setPatch(const Program& patch_)
   {  
      patch = patch_;
   
      patch.print();
      setText(1, patch.name);

      programVoices(&patch);
   }

   void voiceProgram(unsigned index_, uint8_t num_) override
   {
      if (num_ >= NUM_PROGRAM)
         return;

      setPatch(program[num_]);
   }

   Program patch{};
};

} // namespace VL1
