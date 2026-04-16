#include <msp430.h>
#include "RGBLED.h"
#include "init_Servo.h"
#include "Sensors.h"
#include "init_ThermC.h"
#include "Solenoid.h"

int main(){

    WDTCTL = WDTPW | WDTHOLD;

    

unsigned int ThermC_Value;

unsigned int Thermistor_Value;

float Thermistor_F;

float Setpoint_F;

 init_Sensors();

 init_ThermC();

 init_Servo();

init_Solenoid();

 PM5CTL0 &= ~LOCKLPM5;
 
_Bool Detect_Flame;

read_Thermocouple();

if (read_Thermocouple() >= 80)
{
  Detect_Flame = 1;
}
else {
Detect_Flame = 0;
}

}

