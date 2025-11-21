//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "Sample.h"

template <unsigned LENGTH>
class Delay
{
public:
   Delay() = default;

   Sample operator()() const
   {
      return buffer[index];
   }

   void operator=(Sample x_)
   {
      buffer[index] = x_;

      if (++index > LENGTH)
         index = 0;
   }

   Sample operator()(Sample x_)
   {
      Sample y = buffer[index];

      operator=(x_);

      return y;
   }

private:
   unsigned index{};
   Sample   buffer[LENGTH];
};
