/*

 * The purpose of this code is to resolve the issue of polling and allow it so that a more efficient method
 * is implemented to detect switch press and blink an LED on the press of a button, so that is this program, which
 * enables the user to press the button and the LED blinks. The program makes use of the Port 1, specifically, P1.0 and P1.3, the green LED and the button.
 *
 */
#include <msp430.h>

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    P1DIR &= ~BIT3; //Configures button as input
    P1REN|=BIT3; //Enable pullup/pulldown resistors for P1.3
    P1OUT|=BIT3; // Sets resistor to pullup

    P1IE|=BIT3; // Configures enable interrupt on P1.3
    P1IES|=BIT3; //Set interrupt flag on the falling edge of logic level on P1.3

    __enable_interrupt(); //Function call to enables maskable interrupts

    P1DIR |= BIT0; // Initializes the Green LED as an output
    P1OUT &= ~BIT0; // Sets the Green LED to be off prior to the switch being pressed

    __low_power_mode_0(); // call to Initiate low power mode
     return 0;
}
// Port 1 ISR is activated when button is pressed and the state is transistioned from high to low
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
P1OUT ^=  BIT0;// Toggles the green led on and off
P1IFG &= ~BIT3; // Allows for reset interrupt flag to be activated when the button is pressed
}






