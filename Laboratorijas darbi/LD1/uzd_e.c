#include <msp430.h> 


/**
 * main.c
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P2DIR &= ~(BIT6 + BIT7); //P2.6, P2.7 as inputs
	P2SEL &= ~(BIT6 + BIT7); //P2.6, P2.7 as GPIO
	P2SEL2 &= ~(BIT6 + BIT7); //P2.6, P2.7 as GPIO
	P2REN |= BIT6 + BIT7; //enable internal resistors
	P2OUT |= BIT6 + BIT7; //enable pull-up resistors

	P1DIR = 0;

	while(1){
		if ((P2IN & 0b11000000) == 0b11000000) {// PB6 = off  PB7 = off
				P1DIR = 0b11111111; //XXXXXXXX
				P1OUT = 0b00110011; //GGRRGGRR
		}
		if ((P2IN & 0b11000000) == 0b10000000) {// PB6 = off  PB7 = on
				P1DIR = 0b00111100; //NNXXXXNN
				P1OUT = 0b00110000; //NNRRGGNN
		}
		if ((P2IN & 0b11000000) == 0b01000000) {// PB6 = on  PB7 = off
				P1DIR = 0b11000011; //XXNNNNXX
				P1OUT = 0b00000011; //GGNNNNRR
			}
		if ((P2IN & 0b11000000) == 0b00000000) {// PB6 = on  PB7 = on
				P1DIR = 0b00000000; //XXXXXXXX
				P1OUT = 0b00000000; //NNNNNNNN
			}
	}

	//return 0;

}
