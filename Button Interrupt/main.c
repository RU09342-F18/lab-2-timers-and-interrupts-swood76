/*

 * The purpose of this code is to resolve the issue of polling and allow it so that a more efficient method
 * is implemented to detect switch press and blink an LED on the press of a button, so that is this program, which
 * enables the user to press the button and the LED blinks. The program makes use of the Port 1, specifically, P1.0 and P1.3, the green LED and the button.
 *
 */
#include <msp430.h>

int main(void) {

    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    P1DIR&=~BIT3; //Set P1.3 as input
    P1REN|=BIT3; //Enable pullup/pulldown resistors for P1.3
    P1OUT|=BIT3; //Set P1.3 to have pull up resistors

    P1IE|=BIT3; //Enable interrupt on P1.3
    P1IES|=BIT3; //Set interrupt flag on the falling edge of logic level on P1.3

    __enable_interrupt(); //Enable maskable interrupts

    P1DIR|=BIT0; //Set P1.0 as output
    P1OUT&=~BIT0; //Initially turn off the LED


    __low_power_mode_0(); //Go to low power mode 0
     return 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void P1_Function()
{
    int i; //Declare counter variable
   //Toggle the LED
    i=0; //Start a counter variable
   while(i<500) //Wait till the switch is not pressed continusouly for 500 loop cycles
    {
        if((P1IN&BIT3==1))
        {
            i++;
       // __delay_cycles(500);
        }
        else
        {
            i--;
            P1OUT^=BIT0;
        }
       // __delay_cycles(500);//If the switch is pressed, reset the counter variable
    }
    P1IFG&=~BIT3; // Reset interrupt flag
}


