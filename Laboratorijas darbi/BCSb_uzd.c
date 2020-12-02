#include <msp430.h> 

/**
15 variants
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0 + BIT6; //enable green and red leds
    P1OUT |= (BIT0 + BIT6);// both LED on
    P1OUT &= ~(BIT0 + BIT6); //both LEDs off

    DCOCTL = DCO0 + DCO1;//DCO = 3
    BCSCTL1 = XT2OFF + RSEL2 + RSEL1; // FDCO = 0,8 MHz; RSEL = 6;
    //BCSCTL1 = XT2OFF + RSEL3 + RSEL2 + RSEL1 + RSEL0; // FDCO = 20 MHz

    while (1){
        //14824
        _delay_cycles(800000);//1s delay
        P1OUT |= BIT6;
        BCSCTL2 = 0;//div=1

        _delay_cycles(800000);//1s delay
        P1OUT ^= BIT6 + BIT0;
        BCSCTL2 = DIVM1; //div=4

        _delay_cycles(800000);//1s delay
        P1OUT ^= BIT6 + BIT0;
        BCSCTL2 = DIVM1 + DIVM0;//div=8

        _delay_cycles(800000);//1s delay
        P1OUT ^= BIT6 + BIT0;
        BCSCTL2 = DIVM0; //div=2

        _delay_cycles(800000);//1s delay
        P1OUT |= BIT6 + BIT0;
        BCSCTL2 = DIVM1; //div=4

        _delay_cycles(800000);//1s delay
        P1OUT &= ~(BIT6 + BIT0);
        BCSCTL2 = 0;//div=1
    }

}
