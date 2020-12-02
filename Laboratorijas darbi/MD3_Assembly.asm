;Pārveidojiet 41 16-bitu skaitļu ieejas masīvu X par izejas masīvu Y izmantojot uzdotus elementu pārveidošanas noteikumus. Testa nolūkam ir jāpieņem, ka L=500

#include "msp430g2553.h"                

                org     0xF800

main            mov     #WDTPW+WDTHOLD, &WDTCTL         ;Stop Watchdog
                mov     #0,             R15             ;Initial shift is 0

Process_Number  mov     My_Input_Array(R15),R10         ;Read input data (IN)

                cmp     #0,             R10             ;If IN>=0
                jge     Positive_Value                  ;Jump to Positive_Value

Negative_Value  mov     #0,             R10             ;If IN<0 then OUT=0
                jmp     Common_Point                    ;Jump to Common_Point

Positive_Value  cmp     #500,           R10             ;If IN>=L, L=500
                jge     Positive_fromL                  ;Jump to Positive_fromL
                mov     #0,             R9              ;If IN<L then R9=0
                sub     R10,            R9              ;R9-R10 => R9=0-R10
                mov     R9,             R10             ;R10=OUT=R9
                jmp     Common_Point                    ;Jump to Common_Point

Positive_fromL  mov     #500*2,         R8              ;R8=1000 (2L)
                sub     R8,             R10             ;R10=OUT=R10-R8=R10-2L
                
Common_Point    mov     R10,            200h(R15)       ;Save result
                add     #2,             R15             ;Shift=Shift+2
                cmp     #41*2,          R15             ;For Shifts<41*2
                jl      Process_Number                  ;Process Next Element

                bis     #CPUOFF,        SR              ;Stop CPU
                nop                                     ;For Debugging viewer

My_Input_Array  dw      0, 156, 309, 454, 588, 707, 809, 891, 951, 988, 1000
                dw      988, 951, 891, 809, 707, 588, 454, 309, 156, 0, -156
                dw     -309, -454, -588, -707, -809, -891, -951, -988, -1000
                dw     -988, -951, -891, -809, -707, -588, -454, -309, -156, 0

                org    0xFFFE
                dw     0xF800

                end
