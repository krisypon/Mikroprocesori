#include <msp430.h> 

#define red_period 3750
#define red_on 1875
#define green_period 43750
#define green_on 21875

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    DCOCTL = 0;//DCOCTL = DCO1 + DCO2 + DCO0 + MOD4 + MOD3;//DCOCLT = 111|11000
    BCSCTL1 &= ~ (RSEL0 +RSEL1 + RSEL2);//BCSCTL1 = RSEL1 + RSEL0; // FDCO = 0.4 MHz; RSEL=3; BCSCTL1 = 0|0|00|0011
    BCSCTL2 = DIVS_2; //SMCLK = fdco/4 = 25000 kHz; BCSCTL2 = 00|00|0|10|0

    //DCOCTL = DCO1 + DCO0;//DCOCLT = 111|11000
    //BCSCTL1 = RSEL1 + RSEL0; // FDCO = 0.4 MHz; RSEL=3; BCSCTL1 = 0|0|00|0011
    //BCSCTL2 = DIVS_2; //SMCLK = fdco/4 = 25000 kHz; BCSCTL2 = 00|00|0|10|0

    TA0CTL = TASSEL_2 + ID_1 + MC_1 + TACLR; // UP made, Fta = 12500 Hz
    TA0CCR0 = red_period;
    TA0CCR1 = red_on;
    TA0CCTL1 = OUTMOD_7;

    P1DIR |= BIT6;
    P1SEL |= BIT6;
    P1SEL2 &= ~BIT6; // P1.6 red LED controlled by TimerA0 1st output

    TA1CTL = TASSEL_2 + ID_1 + MC_1 + TACLR; // UP made, Fta = 12500 Hz
    TA1CCR0 = green_period;
    TA1CCR1 = green_on;
    TA1CCTL0 = CCIE;
    TA1CCTL1 = CCIE;

    P1DIR |= BIT0;
    P1OUT &= ~BIT0; //P1.0 green LED is off

    _bis_SR_register(CPUOFF+GIE);
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_CCR0 (void){
    P1OUT |= BIT0;
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1_CCR1 (void){
    P1OUT &= ~BIT0;
    TA1CCTL1 &= ~CCIFG;
}
