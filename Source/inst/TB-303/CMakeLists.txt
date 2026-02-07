#------------------------------------------------------------------------------
# Copyright (c) 2026 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

add_library(TB303 STATIC 
            Patch.cpp)

target_include_directories(TB303 PUBLIC ..)
