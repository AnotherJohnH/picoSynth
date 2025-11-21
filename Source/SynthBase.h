//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

#include "Synth.h"

template <typename TRAITS, typename VOICE>
class SynthBase : public Synth
{
public:
   SynthBase()
      : Synth(TRAITS::NUM_VOICES)
   {
   }

protected:
   template <typename PATCH>
   void programVoices(const PATCH* patch_)
   {
      for(unsigned i = 0; i < TRAITS::NUM_VOICES; ++i)
      {
         voice[i].program(patch_);
      }
   }

   virtual void processSysEx() {}

   unsigned sysex_size{};
   uint8_t  sysex_buffer[TRAITS::MAX_SYSEX_SIZE];
   VOICE    voice[TRAITS::NUM_VOICES];

private:
   int16_t sample()
   {
      int32_t sample{0};

      for(unsigned i = 0; i < TRAITS::NUM_VOICES; ++i)
      {
         sample += voice[i].sample();
      }

      return int16_t(sample / TRAITS::DIVISOR);
   }

   void getSamples(uint32_t* buffer, unsigned n) override
   {
      for(unsigned i = 0; i < n; ++i)
      {
         int16_t mono = sample();

         buffer[i] = (mono << 16) | (mono & 0xFFFF);
      }
   }

   void voiceOn(unsigned index_, uint8_t midi_note_, uint8_t velocity_) override
   {
      voice[index_].on(midi_note_, velocity_);
   }

   void voiceOff(unsigned index_, uint8_t velocity_) override
   {
      voice[index_].off(velocity_);
   }

   void sysEx(uint8_t byte_) override
   {
      if (byte_ == 0xF0)
      {
         sysex_state = SYSEX_START;
         return;
      }
      else if (byte_ == 0xF7)
      {
         if ((sysex_state == SYSEX_CAPTURE) && (sysex_size > 0))
         {
            processSysEx();
         }
         sysex_state = SYSEX_IGNORE;
         return;
      }

      switch(sysex_state)
      {
      case SYSEX_IGNORE:
         break;

      case SYSEX_START:
         if (byte_ == TRAITS::MIDI_MANUF_ID)
         {
            sysex_size  = 0;
            sysex_state = SYSEX_CAPTURE;
         }
         break;

      case SYSEX_CAPTURE:
         if (sysex_size < TRAITS::MAX_SYSEX_SIZE)
         {
            sysex_buffer[sysex_size++] = byte_;
         }
         break;
      }
   }

   enum SysExState { SYSEX_IGNORE, SYSEX_START, SYSEX_CAPTURE };

   SysExState sysex_state{SYSEX_IGNORE};
};
