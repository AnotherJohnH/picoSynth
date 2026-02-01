//-------------------------------------------------------------------------------
// Copyright (c) 2025 John D. Haughton
// SPDX-License-Identifier: MIT
//-------------------------------------------------------------------------------

#pragma once

template <typename TYPE>
struct Control
{
   uint8_t     midi1{};
   uint8_t     midi2{};
   TYPE        min{};
   TYPE        max{};
   const char* name{};
   const char* unit{""};
   TYPE*       patch{};
};

