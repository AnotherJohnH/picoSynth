#-------------------------------------------------------------------------------
# Copyright (c) 2025 John D. Haughton
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------

# pylint: disable=bad-indentation

# Attenuation table...
# 0x00 => is -20 dB
# 0x40 => is   0 dB  0xFFFF
# 0x7F => is +20 dB

import math
import table

DB_RANGE = 20

def amp_fn(x):
   return math.pow(10, (DB_RANGE / 20) * (x - 1))

table.gen('gain7',
          func      = lambda i,x : int(amp_fn(x * 2) * 0xFFFF + 0.5),
          typename  = 'uint32_t',
          log2_size = 7,
          fmt       = table.hex_fmt(24),
          is_const  = True)
