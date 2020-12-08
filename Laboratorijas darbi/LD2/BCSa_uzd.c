#include <msp430.h> 

/**
 * 15 variants
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT4;
    P1SEL |= BIT4;
    P1SEL2 &= ~BIT4; //P1.4 AS SMCLK output

    DCOCTL = DCO1 + DCO2 + MOD2 + MOD1 + MOD0;//DCOCLT = 110|00111
    BCSCTL1 = XT2OFF + RSEL1 + RSEL0; // FDCO = 0.384 MHz; RSEL=3; BCSCTL1 =1|0|00|0011
    BCSCTL2 |= DIVM0; //MCLK = fdco/2 = 192 kHz; BCSCTL2 = 00|01|0|00|0

    P2DIR |= BIT1 +BIT3 + BIT5; //enable RGB LEDs

    while(1){
        P2OUT ^= BIT1 + BIT3 + BIT5; //Toggle RGB LEDs
        _delay_cycles(384400);
    }
}
