//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "Sample.h"
#include "Table_amp7.h"
#include "Table_gain7.h"

class Gain
{
public:
   Gain() = default;

   void setGain(uint8_t level7_)
   {
      //gain = table_amp7[level7_];;
      gain = table_gain7[level7_];
      //if (gain > 0xFFFF) gain = 0xFFFF;
   }

   uint8_t operator=(uint8_t level7_)
   {
      gain = table_amp7[level7_];;
      return level7_;
   }

   Sample operator()(Sample in_)
   {
      return in_ * gain;
   }

private:
   Sample gain{0xFFFF};
};
