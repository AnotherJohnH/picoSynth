//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------
   
#pragma once

#include <cstdint>

//! 16 bit 2's complement samples
class Sample
{
public:
   constexpr Sample() = default;

   constexpr Sample(int32_t value_)
      : value(value_)
   {
   }

   constexpr operator int32_t() const { return value; }

   constexpr int32_t operator<<(unsigned bits_) const { return value << bits_; }
   constexpr int32_t operator<<(signed bits_) const { return value << bits_; }

   constexpr int32_t operator>>(unsigned bits_) const { return value >> bits_; }
   constexpr int32_t operator>>(signed bits_) const { return value >> bits_; }

   constexpr int32_t operator*(Sample rhs_) const { return (value * rhs_) >> BITS; }

   int32_t operator=(int32_t value_)
   {
      value = value_;
      return value;
   }

   int32_t operator+=(int32_t value_)
   {
      value += value_;
      return value;
   }

   int32_t operator-=(int32_t value_)
   {
      value -= value_;
      return value;
   }

   template <typename TYPE>
   static Sample rescale(TYPE value_)
   {
      const unsigned WIDTH{sizeof(TYPE) * 8};

      return Sample(value_) >> (WIDTH - BITS);
   }

   static const unsigned RATE{48000};   //!< 48 kHz
   static const unsigned BITS{16};      //!< sample total bit width
   static const int32_t  MAX{+0x7FFF};  //!< ~ +1.0
   static const int32_t  MIN{-0x7FFF};  //!< ~ -1.0

private:
   int32_t value;
};

