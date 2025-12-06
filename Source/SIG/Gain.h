//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "Sample.h"

class Gain
{
public:
   Gain() = default;

   Sample operator=(Sample gain_) { return gain = gain_; }

   Sample operator()(Sample in_) { return in_ * gain; }

private:
   Sample gain{1.0};
};
