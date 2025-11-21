//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "Delay.h"
#include "Gain.h"

class FFComb
{
public:
   FFComb() = default;

   Sample operator()(Sample x_)
   {
      return x_ + alpha(delay(x_));
   }

   Gain alpha{};

private:
   Delay<1> delay;
};
