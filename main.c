#include <msp430.h>
#include "RGBLED.h"
#include "init_Servo.h"
#include "Sensors.h"
#include "init_ThermC.h"
#include "Solenoid.h"
#include "Pilot.h"

float SetPoint_F;
float Thermistor_F;
unsigned int ThermCoupVal;

int main(){

    WDTCTL = WDTPW | WDTHOLD;

init_Pilot();

init_RGB();

init_Sensors();

init_ThermC();

init_Servo();

init_PilotV();

 PM5CTL0 &= ~LOCKLPM5;



}

