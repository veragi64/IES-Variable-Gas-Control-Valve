#include "UART.h"


void UART_BCL_Init(){

 
    P4DIR |= BIT3;               // TX Output
    P4DIR &= ~BIT2;              // RX Input
    P4OUT |= BIT2 | BIT3;        // Set TX High; Set RX Pull-up if REN was on
    P4REN &= ~(BIT2 | BIT3);     // CRITICAL: Disable resistors for both!   
    
    // Configure UART pins
    P4SEL1 &= ~(BIT2 | BIT3);                    // set 2-UART pin as second function
    P4SEL0 |= BIT2 | BIT3;



    // Configure UART
    UCA1CTLW0 |= UCSWRST;
    UCA1CTLW0 |= UCSSEL__SMCLK;

    UCA1BRW = 109;
    UCA1MCTLW = 0x2200;

    UCA1CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
    UCA1IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt


}

void UART_WIFI_Init(){

    // Configure UART pins
    P1SEL0 |= BIT6 | BIT7;                    // set 2-UART pin as second function
    P1SEL1 &= ~(BIT6 | BIT7);

    // Configure UART
    UCA0CTLW0 |= UCSWRST;
    UCA0CTLW0 |= UCSSEL__SMCLK;

    UCA0BRW = 109;
    UCA0MCTLW = 0x2200;


    UCA0CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
    UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt


}


/*
The following code for "UART_BCL_SendCharArray" was written by hand, with debugging help provided
to capture the "\0" in the char array and iterate correctly.

Tool: Gemini
Mode: Thinking
Date of Access: Mar 29, 2026
Transcript available: https://docs.google.com/document/d/1d_5UyO1Xhi9d7KIZvhhafN5gfyQ2QrPeFwRpGOdhUo4/edit?usp=sharing 
*/

void UART_BCL_SendCharArray(char *charArray){
    char char_count = 0;

    while((char_count < 30) && (*charArray != '\0')){
        while(!(UCA1IFG&UCTXIFG));
        
        UCA1TXBUF = *charArray;
        __delay_cycles(100);
        char_count++;
        *charArray++;
        }
}


void UART_WIFI_SendCharArray(char *charArray){
    char char_count = 0;

    while((char_count < 30) && (*charArray != '\0')){
        while(!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = *charArray;
        __delay_cycles(100);
        char_count++;
        *charArray++;
        }
}



/********************************
UART INTERRUPT SERVICE ROUTINES
********************************/

#pragma vector=USCI_A0_VECTOR
__interrupt void WIFI_UART_ISR(void)

{
  switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:
      while(!(UCA0IFG&UCTXIFG));
      UCA0TXBUF = UCA0RXBUF;
      __no_operation();
      break;
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
    default: break;
  }
}

#pragma vector=USCI_A1_VECTOR
__interrupt void BCL_UART_ISR(void)

{
  switch(__even_in_range(UCA1IV,USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:
      while(!(UCA1IFG&UCTXIFG));
      UCA1TXBUF = UCA1RXBUF;
      __no_operation();
      break;
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
    default: break;
  }
}