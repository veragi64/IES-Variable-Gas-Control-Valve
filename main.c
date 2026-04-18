#include <msp430.h>
#include "RGBLED.h"
#include "init_Servo.h"
#include "Sensors.h"
#include "init_ThermC.h"
#include "Solenoid.h"
#include "Pilot.h"
#include <global_vars.h>

int main(){
    //INIT STATE
    WDTCTL = WDTPW | WDTHOLD;
    init_CFH();
    
    init_Pilot();

    init_RGB();

    init_Sensors();

    init_ThermC();

    init_Servo();

    init_PilotV();

    PM5CTL0 &= ~LOCKLPM5;

    
    char STATE = 'I';
    while(1){
        switch (STATE) {
            //IDLE STATE
            case 'I':
                set_RGB(255,0,50);
                if(CallForHeat() || convert_Thermistor(read_Thermistor()) < convert_POT(read_POT())){
                    STATE = 'F'; 
                }
                break;
            //IGNITION STATE
            case 'F':
                set_RGB(0,255,0);
                unsigned int FlameTries = 0;
                set_Ignite(1);
                set_PilotV(1);
                while(!FlameDetect()){
                    __delay_cycles(1000000);
                    FlameTries++;
                    if(FlameTries > 5){
                        STATE = 'S';
                        break;
                    }
                }
                if(FlameDetect()){
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
                if(/*Originally had 1 for debugging purposes in heat stage.*/FlameDetect()){
                    set_RGB(0,0,255);
                    unsigned valve = convert_POT(read_POT()) - convert_Thermistor(read_Thermistor());
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
                if(convert_POT(read_POT()) - convert_Thermistor(read_Thermistor()) < -2)
                {
                    STATE = 'I';
                }
                break;
            //DEFAULT TO IDLE
            default:
                STATE = 'I';

        }
        //Simple 100ms delay
        __delay_cycles(100000);
    }



}
