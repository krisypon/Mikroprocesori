#include "msp430g2553.h"                     ; #define controlled include file;task1

      org   0xFF00
;-----------------------------------------------
      dw    0x40B2,    0x5A80,    0x0120
      dw    0x43F2,    0x00FF,    0x0022
      dw    0x40F2,    0x007F,    0x0021
      dw    0x1152,    0x0021
      dw    0x2C04
      dw    0x40F2,    0x007F,    0x0021
      dw    0x40B2,    0x7530,    0x0200
      dw    0x8392,    0x0200
      dw    0x23FE
      dw    0x4030,    0xFF10
;-----------------------------------------------
      org   0xFFFE
      dw    0xFF00
      end
