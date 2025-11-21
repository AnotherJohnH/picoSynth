//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "Table_amp15.h"

class Adsr
{
public:
   Adsr()
   {
      phase_rate[OFF]      = 0;
      phase_level[OFF]     = 0;

      phase_rate[ATTACK]   = MAX;
      phase_level[ATTACK]  = MAX;

      phase_rate[DECAY]    = 0;
      phase_level[DECAY]   = MAX; 

      phase_rate[SUSTAIN]  = 0;
      phase_level[SUSTAIN] = MAX;

      phase_rate[RELEASE]  = MAX;
      phase_level[RELEASE] = 0;
   }

   bool isOff() const { return phase == OFF; }

   void setAttack_mS(unsigned time_ms_)
   {
      unsigned samples = (time_ms_ * Sample::RATE / 1000) + 1;
      phase_rate[ATTACK] = MAX / samples;

      if (phase == ATTACK)
      {
         rate = phase_rate[ATTACK];
      }
   }

   void setDecay_mS(unsigned time_ms_)
   {
      unsigned samples = (time_ms_ * Sample::RATE / 1000) + 1;
      Sample rate = MAX / samples;
      phase_rate[DECAY] = -rate;

      if (phase == DECAY)
      {
         rate = phase_rate[DECAY];
      }
   }

   void setSustain(uint8_t level7_)
   {
      phase_level[DECAY] = phase_level[SUSTAIN] = scaleLevel(level7_);

      if (phase == DECAY)
      {
         target = phase_level[SUSTAIN];
      }
      else if (phase == SUSTAIN)
      {
         level = target = phase_level[SUSTAIN];
      }
   }

   void setRelease_mS(unsigned time_ms_)
   {
      unsigned samples = (time_ms_ * Sample::RATE / 1000) + 1;
      Sample rate = MAX / samples;
      phase_rate[RELEASE] = -rate;

      if (phase == RELEASE)
      {
         rate = phase_rate[RELEASE];
      }
   }

   //! Gate on
   void on() { setPhase(ATTACK); }

   //! Gate off
   void off() { setPhase(RELEASE); }

   void mute() { setPhase(OFF); }

   //! Return next envelope sample
   Sample operator()()
   {
      level += rate;

      if (rate > 0)
      {
         if (level < target)
            return table_amp15[level >> 8];
      }
      else
      {
         if (level >= target)
            return table_amp15[level >> 8];
      }

      level = target;
      setPhase(Phase(phase + 1));
      return table_amp15[level >> 8];
   }

private:
   static constexpr Sample MAX = Sample::MAX << 8;

   enum Phase { OFF, ATTACK, DECAY, SUSTAIN, RELEASE, NUM_PHASES };

   static Sample scaleLevel(uint8_t level7_)
   {
      return (level7_ << 16) | (level7_ << 9) | (level7_ << 2) | (level7_ >> 5);
   }

   void setPhase(Phase phase_)
   {
      if (phase_ == NUM_PHASES)
      {
         phase_ = OFF;
      }

      phase  = phase_;
      rate   = phase_rate[phase];
      target = phase_level[phase];
   }

   Phase  phase{OFF};
   Sample level{0};
   Sample rate{0};
   Sample target{0};
   Sample phase_rate[NUM_PHASES]  = {};
   Sample phase_level[NUM_PHASES] = {};
};
