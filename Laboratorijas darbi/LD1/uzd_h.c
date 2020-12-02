#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// stop watchdog timer

	P1DIR = 0x01;//P1.0 output,else input
	P2SEL = 0;
	P2SEL2 = 0;
	P2OUT = 0b11000000;//p1.4
	P2REN |= 0b11000000;
	P2IE |= 0b11000000;
	P2IES |= 0b11000000;
	P2IFG |= 0;

	P1DIR=0b11111111;
	P1OUT=0b00110011;

	__bis_SR_register(LPM4_bits + GIE);
}

//Port 1 interupt srvice routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
	//_delay_cycles(500000);
	if (P2IFG & 0b01000000){
		P1DIR = P1DIR ^ 0b00111100;
	}

	if (P2IFG & 0b10000000){
		P1DIR = P1DIR ^ 0b11000011;
	}
	_delay_cycles(500000);

	P2IFG = 0;
}


