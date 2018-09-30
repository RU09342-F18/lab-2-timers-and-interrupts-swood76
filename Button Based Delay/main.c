#include <msp430.h>
/**


*


 This code is meant to solve the problem of the button delay. In this program the user is able to hold down the already

 blinking red and green LEDs, and the time they hold down is counted, and the LEDs then blink at the time and frequency held down by the user

* Code is meant to be implemented on MSP430G2553

*/


int main(void)


{


   WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer




   P1DIR |= BIT0;  // Initialization of the  pins 1.0 as an output so that Green LED is on
   P1DIR |= BIT6;  // Initialization of the  pins 1.6 as an output so that RED LED is on


   P1REN |= BIT3; // Initialization of pull up/ down resistor

   BCSCTL3 = LFXT1S_2; // Initialization of 32 kHz crystal, with bit name XT1, and its corresponding register of BCSCTL3

   P1OUT |= BIT3; //Sets button to be high so pull up resistor is enabled




   P1OUT |= BIT0; // Sets initialized Pin 1.0 and Pin 1.6 high at start, so that they are both ON
   P1OUT |= BIT6;


   CCR0 =  103;  //Set Frequency in the zeroth capture compare register to 10kHz


   P1IE |= BIT3; //Sets and enables interrupt such it is configured to Button

   P1IES |= BIT3; // Allows for switch functionality of button for the interrupt behavior


   CCTL0 = CCIE; // Tells 16 bit register of the many timer A register to enables interrupts




   TACTL = TASSEL_1 + MC_1 + ID_3;// Determines clock to be ACLK selected since it must pass through a 4*1 mux, where ACLK is 01, and to ensure
   // the clock sour is active and the timer actually counts the MC was set to a value MC>0, 1 Up-Count Enabled, and the divider which is sourced from the ACLK in this case is
   // selected to be a value of, and thi denoted by ID_3







__enable_interrupt(); //Function call to enable maskable interrupts
 while (1) // If nothing, Infinite loop
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

// verifies and checks if button pressed and interrupt and high to low state are both 1
if (P1IES & BIT3)


{

TACTL = TACLR; // Sets any value in Timer A register to zero so that it can count from beginning
TACTL = TASSEL_1 + MC_2 + ID_3;  // Configures and sets Clock to ACLK and to Count in continuous mode since MC_2 is set to 2, sets it so it counts from 0 to 0FFFFh
P1IES &= ~BIT3; // Reset the edge of Port 1 from the already set high to low state from low to high
}


else
{
CCR0 = TA0R; // Stores value that has been set in CCR0 register to Timer A's register
TACTL = TASSEL_1 + MC_1 + ID_3;  // Configuration of timer modes to Up count from zero to the value of TACCR0
P1IES |= BIT3; // Resets back to original state of P1ES such that port 1s edge select transition is high to low
}
P1IFG &= ~BIT3; //if condition not met Enabled to set so interrupt flag is reset and trigger
}






