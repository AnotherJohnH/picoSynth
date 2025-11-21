#------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

autogen_py(Table_delta14_7)
autogen_py(Table_amp7)
autogen_py(Table_gain7)
autogen_py(Table_amp15)

add_library(SIG STATIC
            Table_delta14_7.cpp
            Table_amp7.cpp
            Table_gain7.cpp
            Table_amp15.cpp)

target_include_directories(SIG PUBLIC .. ${CMAKE_CURRENT_BINARY_DIR})
