


            // THIS CODE WAS PROVIDED BY "Texas Instruments Incorporated" //
//------------------------------------------------------------------------------------//
#include <msp430.h>

void init_ThermC()
{

  P1SEL0 |= BIT1 + BIT2 + BIT3;             // Select P1.1 P1.2 P1.3 OA function
  P1SEL1 |= BIT1 + BIT2 + BIT3;             // Select P1.1 P1.2 P1.3 OA function
  SAC0OA |= NMUXEN + PMUXEN;                // Enable negative and positive input
  SAC0OA |= PSEL_0;
  SAC0OA |= NSEL_1;


//------------------------------------------------------------------------------------//




       // This section of code was assisted with Notebook Lm//
//-------------------------------------------------------------------//
SAC0PGA = MSEL_2 | GAIN2 | GAIN1| GAIN0;   // Select the Non-inverting amplifier, then set gain to max value
SAC0OA |= SACEN + OAEN;                     // Enable Op-amp module
//-------------------------------------------------------------------//
}


