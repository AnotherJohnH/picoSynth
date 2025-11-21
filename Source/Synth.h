//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "STB/MIDIInstrument.h"

//! Synth external interface
class Synth : public MIDI::Instrument
{
public:
   Synth(unsigned num_voices_)
      : MIDI::Instrument(num_voices_)
   {
   }

   virtual void init() {}

   virtual const char* getName() const = 0;

   virtual void getSamples(uint32_t* buffer, unsigned n) = 0;

   const char* getInfo() const
   {
      if (not info_update)
         return nullptr;

      return info;
   }

protected:
   void setInfo(const char* text_)
   {
      unsigned i = 0;

      for(; (i < 16) && (text_[i] != '\0'); ++i)
         info[i] = text_[i];

      for(; i < 16; ++i)
         info[i] = ' ';

      info[i] = '\0';

      info_update = true;
   }

private:
   char info[16 + 1];
   bool info_update{false};
};
