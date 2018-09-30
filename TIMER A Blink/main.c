#include "msp.h"

/**



Program allows the user through Up count mode to increase and control the speed of an two LEDS (red and green) of PORT2
until the TA0CRR0 register is reached

Attempt of implementation on the MSP432, so far it compiles, but an error is created when programmed and debugged,
following error: Error connecting to the target.


*/

/* External declarations for the interrupt handlers used by the application. Essential to do for interrupt use on the MSP432 could not use PRAGMA vector*/
extern void PORT1_ISR_handler( void );
extern void TimerA0_N_ISR_handler( void );



int main(void)


{




    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer


    P1REN |= BIT4;
    // Initialization of pull up/ down resistor

    P2DIR |= BIT0;  // Initialization of the  pins 1.0 as an output so that Green LED is on
    P2DIR |= BIT1;  // Initialization of the  pins 1.6 as an output so that RED LED is on




    P1OUT |= BIT4; //Sets button to be high so pull up resistor is enabled






    P2OUT |= BIT0; // Sets initialized Pin 1.0 and Pin 1.6 high at start, so that they are both ON
       P2OUT |= BIT1;
       P1IE |= BIT4; //Sets and enables interrupt such it is configured to Button P1.3
    P1IES |= BIT4; //Enables high - to - low behavior on interrupt (Button press)


    TA0CTL = CCIE;//  Tells 16 bit register of the many timer A register to enables interrupts, Difference in naming convention for each of the registers


    TA0CCR0 =  999; //Stores an initial value in the CCR0 register


    TA0CTL = TASSEL_1 + MC_1 + ID_3;  // // Determines clock to be ACLK selected since it must pass through a 4*1 mux, where ACLK is 01, and to ensure
    // the clock sour is active and the timer actually counts the MC was set to a value MC>0, 1 Up-Count Enabled, and the divider which is sourced from the ACLK in this case is
    // selected to be a value of, and thi denoted by ID_3






 //Function call to enables interrupts, enable interrupts has been set high
__enable_interrupt();
while (1) //Infinite while loop
 {
 }
}

// Timer A ISR, set to count to CCR0 and interrupt, ISR handler unique to MSP432
void TimerA0_ISR_handler( void )
{
    P2OUT ^= BIT0; // Toggle Red LED
       P2OUT ^= BIT1;        //Toggle Green LED
}



void PORT1_ISR_handler( void )    //Port 1 ISR that is activated when changes button is set and pressed from high to low, ISR handler unique to MSP432
{
    TA0CCR0 = TA0CCR0 - 200;
    P1IFG &= ~BIT4;

    // Stores difference of initial stored value 1hz each time pressed which results in an increased frequency and faster blinking LEDS
    //Resets interrupt flag initially triggered
}





