//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include "OscBase.h"
#include "Gain.h"

class PwmOsc : public OscBase
{
public:
   PwmOsc() = default;

   //! Set pulse width 0.0 => square
   void setWidth(Sample width_)
   {
      limit = PHASE_HALF + sample2phase(width_);
   }

   //! Get next sample
   Sample operator()(Sample mod_ = 0)
   {
      Sample sample = phase >= limit ? -1.0 : +1.0;

      phase += delta + sample2phase(mod_);

      return gain(sample);
   }

   Gain gain{};

private:
   Phase limit{PHASE_HALF};
};

