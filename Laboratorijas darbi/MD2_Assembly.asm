;Sareiziniet visus 41 16-bitu skaitļu masīva X elementus ar konstanti K = 121

		#include "msp430g2553.h"        ; #define controlled include file
		org	0xD000
;===============================================================================        
main   		nop                             ; main program
        	mov.w   #WDTPW+WDTHOLD, &WDTCTL ; Stop watchdog timer
        	mov	#41*2,		R7	; MAX value of el. counter
                mov     #0,             R6      ; Element counter
		
main_loop       mov	Input_data(R6),	R15	; get element from begining of array
                mov     R15,            R14     ; R14 = R15
                mov     R15,            R13     ; R13 = R15
                mov     #7,             R8      ; loop counter for multiplication1
                mov     #3,             R9      ; loop counter for multiplication2

multiplication1 rla	R15			; Element multiplication(*2)
                dec     R8                      ; loop counter -1
                jnz     multiplication1         ; jump to multiplication1
                                                ; get element*128
multiplication2 rla	R14			; Element multiplication(*2)
                dec     R9                      ; loop counter -1
                jnz     multiplication2         ; jump to multiplication2
                                                ; get element*8
                sub     R14,            R15     ; element*128 - element*8
                                                ; as result element*120

                add     R13,            R15     ; as result element*121

		mov	R15,		0x0200(R6); save result in selected location
                             
                incd	R6			; counter + 2
                cmp     R7,             R6      ; MAX - element counter
		jnz	main_loop		; IF counter!=0 THEN repeat
                                                ; with next element
		
		jmp     $                       ; jump to current location '$'
                                        	; (endless loop)
		bis	#CPUOFF,	SR	; Stop CPU
;-------------------------------------------------------------------------------		
Input_data	dw      0, 156, 309, 454, 588, 707, 809, 891, 951, 988, 1000
                dw      988, 951, 891, 809, 707, 588, 454, 309, 156, 0, -156
                dw     -309, -454, -588, -707, -809, -891, -951, -988, -1000
                dw     -988, -951, -891, -809, -707, -588, -454, -309, -156, 0
;===============================================================================
		org	0xFFFE
		dw	main
				
        	END
