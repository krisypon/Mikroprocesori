#include <msp430.h> 

/*
 * main.c
 */
void main(void) {
	int i;
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    P1DIR = 65;					// P1.6 and P1.0 - outputs
    //P1DIR = BIT0 + BIT6;
    P1OUT = 1;					// Red is on, green is off

    while (1) {
    	//for (i=0;i<20000;i++){}
    	//for (i=20000;i<0;i--){}
    	_delay_cycles(1000000);		//1 sec gara pauze

    	P1OUT = P1OUT ^ 65;
    }


}
