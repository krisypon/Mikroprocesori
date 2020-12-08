#include <msp430.h> 

//15 variants
void main(void)
{
    int skaititajs = 0;

    //ACLK = 32768 Hz = fwdt
    BCSCTL1 = BIT5;

    P1DIR |= BIT0; // enable P1.0 LED

    WDTCTL = WDTPW | WDTTMSEL | WDTSSEL | WDTCNTCL | WDTIS1; //WDT is a timer with 512, using ACLK

    while(1){
        if (IFG1 & WDTIFG){
            skaititajs++;//increment WDT cycle counter
            if (skaititajs == 80){
                P1OUT ^= BIT0; // toggle P1.0 LED
                skaititajs = 0; // clear counter
            }
            IFG1 &= ~WDTIFG; //clear WDT flag
        }
    }


}
