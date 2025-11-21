#------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

add_subdirectory(SIG)
add_subdirectory(Juno106)

add_picoX7_executable(dinkySynth
                         dinkySynth.cpp
                      LIBRARIES
                         Juno106 SIG)
