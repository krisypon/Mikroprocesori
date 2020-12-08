#include <msp430.h> 

#define red_period 450
#define red_on 225
#define green_period 5250
#define green_on 2625

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    BCSCTL3 |= LFXT1S1; // ACLK using VLO
    BCSCTL1 |= DIVA_3; // ACLK = 12000 / 8 = 1500 HZ

    TA0CTL = TASSEL_1 + MC_3 + TACLR; // UP-DOWN mode, ACLK, Fta = 1500 Hz
    TA0CCR0 = red_period/2;
    TA0CCR1 = red_on/2;
    TA0CCTL1 = OUTMOD_6;

    P1DIR |= BIT6;
    P1SEL |= BIT6;
    P1SEL2 &= ~BIT6; // P1.6 red LED controlled by TimerA0 1st output

    TA1CTL = TASSEL_1 + MC_3 + TACLR + TAIE; // UP made, ACLK, Fta = 1500 Hz
    TA1CCR0 = green_period/2;
    TA1CCR1 = green_on/2;
    //TA1CCTL0 = CCIE;
    TA1CCTL1 = CCIE;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0; //P1.0 green LED is off

    _bis_SR_register(CPUOFF+GIE);
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1_ISR (void){
    if (TA1CCTL1 & CCIFG){
        P1OUT ^= BIT0; // toggle green LED
        TA1CCTL1 &= ~CCIFG;
    }

    if (TA1CTL & TAIFG){
        P1OUT &= ~BIT0; // turn off green LED
        TA1CTL &= ~TAIFG;
    }
}
