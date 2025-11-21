//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

class LfoEnv
{
public:
   LfoEnv() = default;

   //! Set LFO delay (mS)
   void setDelay_mS(unsigned delay_ms_)
   {
      delay_samples = (delay_ms_ * Sample::RATE / 1000) + 1;

      if ((phase == DELAY) && (samples > delay_samples))
      {
         samples = delay_samples;
      }
   }

   //! Set LFO attack time(mS)
   void setAttack_mS(unsigned attack_ms_)
   {
      attack_samples = (attack_ms_ * Sample::RATE / 1000) + 1;
      attack_rate    = MAX / attack_samples;
   }

   //! Gate on
   void on()
   {
      phase   = DELAY;
      samples = delay_samples;
      level   = 0;
      rate    = 0;
   }

   //! Return next envelope sample
   Sample operator()()
   {
      level += rate;

      if (--samples == 0)
      {
         if (phase == DELAY)
         {
            phase   = ATTACK;
            samples = attack_samples;
            rate    = attack_rate;
         }
         else
         {
            phase = SUSTAIN;
            level = MAX;
            rate  = 0;
         }
      }

      return level >> 8;
   }

private:
   static constexpr Sample MAX = Sample::MAX << 8;

   enum Phase { DELAY, ATTACK, SUSTAIN };

   Phase    phase{SUSTAIN};
   Sample   level{0};
   Sample   rate{0};
   unsigned samples{0};
   unsigned delay_samples{0};
   unsigned attack_samples{};
   Sample   attack_rate{0};
};
