#------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

add_library(Juno106 STATIC
            Program.cpp
            SysEx.cpp)

target_include_directories(Juno106 PUBLIC ..)
