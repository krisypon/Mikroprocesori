#include <msp430.h> 


/**
 * main.c
 */


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P2SEL = 0;
	P2SEL2 = 0;

	P2OUT = 0b00110011;
	P2DIR = 0b11111111;

	while(1){

		P2DIR = P2DIR ^ (BIT0 + BIT1 + BIT6 + BIT7);// inverte 0,1,6,7 bitu
		_delay_cycles(2000000); //pauze
		P2DIR = P2DIR ^ 0b11111111; // inverte visus bitus
		_delay_cycles(2000000); //pauze
	}


	

}
