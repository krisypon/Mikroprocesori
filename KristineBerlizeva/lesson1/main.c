#include <msp430.h> 


void main(void)
{
	//unsigned int i; //define mainigo i
	volatile unsigned int i; //define mainigo i

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//P1DIR = 0; //viss saturs ir 0 un neviena diode nedeg

	P1DIR = P1DIR | (BIT0 + BIT6); //aktivizet zalo un sarkano diodi
	P1OUT = P1OUT | (BIT0 + BIT6); //ieslegt abas diodes

	while(1){
		P1OUT = P1OUT ^ (BIT0 + BIT6); // parslegtabas diodes uz pretejo stavokli
		//_delay_cycles(1000000); //pauze
		for (i=0;i<20000;i++){}
		//for (i=20000;i<0;i--){}

	}


}
