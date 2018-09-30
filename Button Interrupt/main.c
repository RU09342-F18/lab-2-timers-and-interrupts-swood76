/*

 * The purpose of this code is to resolve the issue of polling and allow it so that a more efficient method
 * is implemented to detect switch press and blink an LED on the press of a button, so that is this program, which
 * enables the user to press the button and the LED blinks. The program makes use of the Port 1, specifically, P1.0 and P1.1, the RED
 *  LED and the button.
 *
 * Code is mean to be implemented for the MSP430FR2311
 *
 */
#include <msp430.h>

int main(void)
{

   WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Without this line the GPIO functionality was locked, it disables the GPIO power-on default high-impedance mode
    P1DIR &= ~BIT1; //Configures button as input
    P1REN|=BIT1; //Enable pullup/pulldown resistors for P1.1
    P1OUT|=BIT1; // Sets resistor to pullup

    P1IE|=BIT1; // Configures enable interrupt on P1.1,
    P1IES|=BIT1; //Set interrupt flag on the falling edge of logic level on P1.1

    __enable_interrupt(); //Function call to enables maskable interrupts

    P1DIR |= BIT0; // Initializes the RED LED as an output
    P1OUT &= ~BIT0; // Sets the RED LED to be off prior to the switch being pressed

    __low_power_mode_0(); // call to Initiate low power mode
     return 0;
}
// Port 1 ISR is activated when button is pressed and the state is transistioned from high to low
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
P1OUT ^=  BIT0;// Toggles the red LED on and off
P1IFG &= ~BIT1; // Allows for reset interrupt flag to be activated when the button is pressed
}
