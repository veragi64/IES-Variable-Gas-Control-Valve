#include <msp430.h>
#include "RGBLED.h"
#include "init_Servo.h"
#include "Sensors.h"
#include "init_ThermC.h"
#include "Solenoid.h"
#include "Pilot.h"
#include <global_vars.h>
#include "UART.h"
#include <stdio.h>


            //This section of code was made with the help of Notebook LM//
//-----------------------------------------------------------------------------------------//
void init_Clock_System(void) {
    __bis_SR_register(SCG0);                // 1. Disable FLL
    CSCTL3 = SELREF__REFOCLK;               // 2. Select REFO (32.768kHz) as FLL ref
    CSCTL0 = 0;                             // 3. Clear DCO and MOD bits
    CSCTL1 = DCORSEL_0;                     // 4. Set DCO range to 1MHz
    CSCTL2 = FLLD_0 + 31;                   // 5. Set multiplier (N=31) for 1.048MHz
    __bic_SR_register(SCG0);                // 6. Enable FLL
    
    // 7. Wait until FLL is locked (FLLUNLOCK bits = 00b)
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); 
}
//-----------------------------------------------------------------------------------------//
char display_msg[80];
char STATE = 'I';
/*
void init_Interrupt_Timer(){

        TB0CTL = TBSSEL__ACLK | MC__UP | ID__8 | TBCLR;
        TB0EX0 = TBIDEX__8;
        TB0CCR0 = 1024;  
        TB0CCTL0 = CCIE; 
        }
*/
int main(){

    WDTCTL = WDTPW | WDTHOLD;

    
    //init_Interrupt_Timer();
    //init_Clock_System();
    
    init_ADC_HardwareTimer();
    
    init_CFH();
    
    init_Pilot();

    init_RGB();

    init_Sensors();

    init_ThermC();

    init_Servo();

    init_PilotV();

    unsigned int FlameTries;

    PM5CTL0 &= ~LOCKLPM5;

    UART_WIFI_Init();
    UART_BCL_Init();

    __enable_interrupt();

 
    
    while(1){
        switch (STATE) {
            //IDLE STATE
            case 'I':
                set_RGB(255,0,50);
                set_Servo(0);
                set_Ignite(0);
                set_PilotV(0);
                if(CallForHeat() || Thermistor_F < SetPoint_F){
                    STATE = 'F'; 
                }
                break;
            //IGNITION STATE
            case 'F':
                set_RGB(0,255,0);
                FlameTries = 0;
                set_Ignite(1);
                set_PilotV(1);
                while(!FlameDetectV){
                    __delay_cycles(1000000);
                    FlameTries++;
                    if(FlameTries > 5){
                        STATE = 'S';
                        break;
                    }
                }
                if(FlameDetectV){
                    set_Servo(100);
                    set_Ignite(0);
                    set_PilotV(0);
                    STATE = 'H';
                }
                
                break;
            //SAFETY STATE
            case 'S':
                set_RGB(255,0,0);
                set_Servo(0);
                set_Ignite(0);
                set_PilotV(0);
                while(1){

                }
                break;
            //HEATING STATE
            case 'H':
                if(1){
                    set_RGB(0,0,255);
                    int valve = SetPoint_F - Thermistor_F;
                    if(valve > 20){
                        valve = 20;
                    }
                    if(valve < 0){
                        valve = 0;
                    }
                    valve *= 5;
                    set_Servo(valve);
                }
                else{
                    STATE = 'F';
                }
                if((SetPoint_F - Thermistor_F) < -2)
                {
                    STATE = 'I';
                }
                break;
            //DEFAULT TO IDLE
            default:
                STATE = 'I';

        }

        sprintf(display_msg, "Pot: %d, Therm: %d, TC: %d\r\n", 
                SetP, TMist, TCoup);
                UART_BCL_SendCharArray(display_msg);
                 __delay_cycles(1000000);

        //Simple 100ms delay
        //__delay_cycles(100000);

        

    }

}


        /*#pragma vector = TIMER0_B0_VECTOR
        __interrupt void Reporting_ISR(){
            sprintf(reportBuffer,"SP: %d F | Temp %d F | Flame: %s\r\n", SetPoint_F, Thermistor_F, (FlameDetectV) );

             UART_BCL_SendCharArray(reportBuffer);
        }
        */
        #pragma vector=ADC_VECTOR
        __interrupt void ADC_ISR(void) {
            // Read the bits (3-0) to see which channel just finished (Source 1068)
            static unsigned int currentChannel = 9;
            unsigned int rawData = ADCMEM0;
            switch(currentChannel) {
                case 9: // Result from A9 (Thermistor)
                    TMist = rawData;
                    break;
                case 5:
                    SetP = rawData;
                    break;
                case 1: // Result from A3 (Thermocouple)
                    TCoup = rawData;
                    break;
                    
                default:
                    // Must read ADCMEM0 to clear the interrupt flag (Source 1037)
                    { unsigned int dummy = ADCMEM0; }
                    break;
            }
            
        if (currentChannel == 0) currentChannel = 9; // Reset for next RTC trigger
        else currentChannel--;
        }