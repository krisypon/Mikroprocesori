#include <msp430.h> 


/**
 * main.c
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P2SEL = 0;
	P2SEL2 = 0;

	while(1){
	//P2DIR = P2DIR | 0b00111100;

		P2DIR = 0b11111111; //XXXXXXXX
		P2OUT = 0b00110011; //GGRRGGRR
		_delay_cycles(2000000); //pauze

		P2DIR = 0b00111100; //NNXXXXNN
		P2OUT = 0b00110000; //NNRRGGNN
		_delay_cycles(2000000); //pauze

		P2DIR = 0b11000011; //XXNNNNXX
		P2OUT = 0b00000011; //GGNNNNRR
		_delay_cycles(2000000); //pauze

		P2DIR = 0b00000000; //XXXXXXXX
		P2OUT = 0b00000000; //NNNNNNNN
		_delay_cycles(2000000); //pauze


	}


	

}
