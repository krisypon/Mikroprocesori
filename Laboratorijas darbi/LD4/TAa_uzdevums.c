#include <msp430.h> 

#define red_time 614
#define green_time 7168

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    BCSCTL1 |= DIVA_1; // ACLK = 32768 / 2 = 16384 HZ

    TACTL = TASSEL_1 + ID_2 + MC_2; // TA using ACLK/4 in cont. mode
    TACCR0 = green_time;
    TACCR1 = red_time;
    TACCTL1 = OUTMOD_4; // Toggle output

    P1DIR |= BIT0;
    P1OUT &= ~BIT0; //init P1.0 Led - green off

    P1DIR |= BIT6;
    P1SEL |= BIT6; //P1.6 red LED controlled from TA CCR1

    while(1){
        if(TACCTL0 & CCIFG){ //tad kad karodzons tiks iestadits izpildisies nosacijums
            TACCR0 += green_time; // add next half-period
            TACCTL0 &= ~CCIFG; //clear event flag
            P1OUT ^= BIT0; // Toggle green led
        }

        if(TACCTL1 & CCIFG){
            TACCR1 += red_time;
            TACCTL1 &= ~CCIFG;
        }

    }


}
