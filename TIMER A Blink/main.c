#include <msp430.h>

/**


* main.c


Program allows the user through Up count mode to increase and control the speed of an two LEDS (red and green) until the CRR0 register is reached


*/

int main(void)


{


    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer


    BCSCTL3 = LFXT1S_2; // Initialization of external 32 kHz crystal, with bit name XT1, and its corresponding register of BCSCTL3
    P1REN |= BIT3;
    // Initialization of pull up/ down resistor

    P1DIR |= BIT0;  // Initialization of the  pins 1.0 as an output so that Green LED is on
    P1DIR |= BIT6;  // Initialization of the  pins 1.6 as an output so that RED LED is on




    P1OUT |= BIT3; //Sets button to be high so pull up resistor is enabled








    P1OUT |= BIT0; // Sets initialized Pin 1.0 and Pin 1.6 high at start, so that they are both ON
       P1OUT |= BIT6;
       P1IE |= BIT3; //Sets and enables interrupt such it is configured to Button P1.3
    P1IES |= BIT3; //Enables high - to - low behavior on interrupt (Button press)


    CCTL0 = CCIE;//  Tells 16 bit register of the many timer A register to enables interrupts


    CCR0 =  999; //Stores an initial value in the CCR0 register


    TACTL = TASSEL_1 + MC_1 + ID_3;  // // Determines clock to be ACLK selected since it must pass through a 4*1 mux, where ACLK is 01, and to ensure
    // the clock sour is active and the timer actually counts the MC was set to a value MC>0, 1 Up-Count Enabled, and the divider which is sourced from the ACLK in this case is
    // selected to be a value of, and thi denoted by ID_3






 //Function call to enables interrupts, enable interrupts has been set high
__enable_interrupt();
while (1) //Infinite while loop
 {
 }
}

// Timer A ISR, set to count to CCR0 and interrupt
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A ()
 {

    P1OUT ^= BIT0; // Toggle Red LED
    P1OUT ^= BIT6;//Toggle Green LED
}






// Port 1 ISR
#pragma vector=PORT1_VECTOR //Port 1 ISR that is activated when changes button is set and pressed from high to low


__interrupt void Port_1(void)


{
 // Stores difference of initial stored value 1hz each time pressed which results in an increased frequency and faster blinking LEDS
CCR0 = CCR0 - 200;
P1IFG &= ~BIT3; //Resets interrupt flag initially triggered
}

