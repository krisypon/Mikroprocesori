#include <msp430.h> 

void mydelay();

/**
 * main.c
 * 2 portu versija
 * bitu uzstadisana un dzesana
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR = 0b11111111;
	P1OUT = 0b00110011; //GGRRGGRR

	while(1){

		P1DIR = P1DIR & 0b00111100; //NNRRGGNN
		mydelay();

		P1DIR = P1DIR | 0b11000011;
		P1DIR = P1DIR & 0b11000011; //GGNNNNRR
		mydelay();

		P1DIR = P1DIR & 0b00000000; //NNNNNNNN
		mydelay();

		P1DIR = P1DIR | 0b11111111; //GGRRGGRR
		mydelay();
	}
}

void mydelay(){
	_delay_cycles(2000000); //pauze
	}


