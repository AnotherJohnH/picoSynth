//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "Sample.h"

class Gain
{
public:
   Gain(Sample value_ = 1.0) : value(value_) {}

   operator Sample() const { return value; }

   Sample operator=(Sample value_) { return value = value_; }

   Sample operator()(Sample in_) { return in_ * value; }

private:
   Sample value{1.0};
};
