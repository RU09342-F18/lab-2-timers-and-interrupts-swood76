# Button Interrupt
Included in this repository is two examples of source code which is used to eliminate the inefficient use of polling, and waiting around until something is changed within a specific register, an intterupt service for Port1 is utilized to act to toggle LED on the act of a user controlled button. This is done so with use of the P1IE and P1IES registers on both the MSP430G2553 and MSP430FR2311. The purpose of this code is to make use of a single interrupt service routine, which is within Port 1 of the port 1 vector such that it is called when the button is pressed of either the MSP430G2553 (P1.3) or MSP430FR2311 (P1.1), and toggles their respective LED1, GREEN for the MSP430G2553 and RED for the MSP430FR2311. 

# Author

Scott Wood
