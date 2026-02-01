//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "SynthVoice.h"

#include "Effect.h"
#include "Voice.h"
#include "Patch.h"

namespace AcornProton {

class Synth : public ::SynthVoice<Effect, Voice, /* NUM_VOICES */ 8>
{
public:
   Synth() = default;

private:
   void synthInit() override
   {
      setText(0, "  Acorn Proton  ");
   }

   void synthControl(uint8_t control_, uint8_t value_) override
   {
      switch(control_)
      {
      case 16:
         patch.env_t = editInt("ENV T", value_, 1, 127);
         programVoices(&patch);
         break;

      case 17:
         patch.env_pi1 = editInt("ENV PI1", value_, -128, 127);
         programVoices(&patch);
         break;

      case 21:
         patch.env_pi2 = editInt("ENV PI2", value_, -128, 127);
         programVoices(&patch);
         break;

      case 25:
         patch.env_pi3 = editInt("ENV PI3", value_, -128, 127);
         programVoices(&patch);
         break;

      case 18:
         patch.env_pn1 = editInt("ENV PN1", value_, 0, 255);
         programVoices(&patch);
         break;

      case 22:
         patch.env_pn2 = editInt("ENV PN2", value_, 0, 255);
         programVoices(&patch);
         break;

      case 26:
         patch.env_pn3 = editInt("ENV PN3", value_, 0, 255);
         programVoices(&patch);
         break;

      case 19:
         patch.env_aa = editInt("ENV AA", value_, -127, 127);
         programVoices(&patch);
         break;

      case 23:
         patch.env_ad = editInt("ENV AD", value_, -127, 127);
         programVoices(&patch);
         break;

      case 27:
         patch.env_as = editInt("ENV AS", value_, -127, 0);
         programVoices(&patch);
         break;

      case 31:
         patch.env_ar = editInt("ENV AR", value_, -127, 0);
         programVoices(&patch);
         break;

      case 49:
         patch.env_ala = editInt("ENV ALA", value_, 0, 126);
         programVoices(&patch);
         break;

      case 53:
         patch.env_ald = editInt("ENV ALD", value_, 0, 126);
         programVoices(&patch);
         break;
      }
   }

   Patch patch{};
};

} // namespace AcornProton
