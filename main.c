#include <msp430.h>
#include "RGBLED.h"
#include "init_Servo.h"
#include "Sensors.h"
#include "init_ThermC.h"

int main(){

    WDTCTL = WDTPW | WDTHOLD;

    PM5CTL0 &= ~LOCKLPM5;
    

unsigned int ThermC_Value;

 init_ThermC();

 init_Sensors();


 while(1) {

   ThermC_Value = read_Thermocouple();

     __no_operation();  
 }
}
