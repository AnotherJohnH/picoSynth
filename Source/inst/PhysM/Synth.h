//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "SynthVoice.h"
#include "Control.h"

#include "Effect.h"
#include "Voice.h"
#include "Patch.h"

namespace PhysM {

class Synth : public ::SynthVoice<Effect, Voice, /* NUM_VOICES */ 8>
{
public:
   Synth() = default;

private:
   void synthInit() override
   {
      setText(0, "   Phys-Model   ");
   }

   void synthProgram(uint8_t num_) override
   {
      programVoices(&patch);
   }

   void synthControl(uint8_t control_, uint8_t value_) override
   {
      if (this->tableControl(control_, value_, control, NUM_CONTROL))
      {
         programVoices(&patch);
      }
   }

   Patch patch{};

   static const unsigned NUM_CONTROL = 7;

   const Control<float> control[NUM_CONTROL] =
   {
      {19, 2,   1.0,     10.0, "Exc Frq",  "Hz", &patch.exciter_freq},
      {23, 3,  -0.999,   -0.9, "Exc Len",  "",   &patch.exciter_length},
      {27, 4, 100.0,  10000.0, "Exc Cut",  "Hz", &patch.exciter_cutoff},
      {31, 5,   0.0,     10.0, "Loop Dly", "mS", &patch.delay},
      {49, 6, 100.0,  10000.0, "Loop Cut", "Hz", &patch.delay_cutoff},
      {53, 7,  -1.0,      1.0, "Loop FB",  "",   &patch.feedback},
      {62, 9, -60.0,     20.0, "Volume",   "dB", &patch.volume},
   };
};

} // namespace PhysM
