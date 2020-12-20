#include <msp430.h> 

int state = 0;
int cnt = 1;
int skaititajs = 0;

int main(void)
{
    BCSCTL1 = BIT5;//DIV = 4

    P1DIR |= BIT0 + BIT6; //enable green & red LEDs = t0 => state = 0
    P1OUT = 0;

    IFG1 = 0; //clear WDT IFG
    IE1 = WDTIE; //enable WDT interrupt
    WDTCTL = WDTPW | WDTTMSEL | WDTSSEL | WDTCNTCL | WDTIS1 ; //run WDT as timer from ACLK with 32768 threshold

    _BIS_SR(GIE + CPUOFF); //enable global interrupt
}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void){
skaititajs++; // enable next state
    if (skaititajs == 16){ //16 times => 1 second
        cnt--;
        if (cnt == 0){
            switch (state){
            case 0:
                P1OUT = 0;
                state++; // enable next state
                cnt = 1;
                break;
            case 1:
                P1OUT |= BIT6; //red on
                state++; // enable next state
                cnt = 1;
                break;
            case 2:
                P1OUT = BIT0; //green on
                state++; // enable next state
                cnt = 4;
                break;
            case 3:
                P1OUT = BIT6;
                state++; // enable next state
                cnt = 8;
                break;
            case 4:
                P1OUT = BIT0; //red on
                state++; // enable next state
                cnt = 2;
                break;
            case 5:
                P1OUT = BIT0 + BIT6; //green on
                state++; // enable next state
                cnt = 4;
                break;
            default:
                state = 0;
                cnt = 1;
            }
        }
        skaititajs = 0;
    }
}
