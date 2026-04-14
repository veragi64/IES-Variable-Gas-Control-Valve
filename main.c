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

 init_Sensors();

 init_ThermC();

 init_Servo();

init_Solenoid();

 PM5CTL0 &= ~LOCKLPM5;
 
 /*while(1) {

   ThermC_Value = read_Thermocouple();

     __no_operation();  
     
 }
*/

/*unsigned int count = 0;
while(1){
  while(count <= 100){
  setServo(count);
  count += 10;
  __delay_cycles(100000);
  }
  count = 0;
  setServo(count);
  __delay_cycles(1000000);
}*/


/*while(1) {

Thermistor_Value = read_Thermistor();

}*/

while(1){

  Pilot_Open();

  __delay_cycles(1000000);

  Pilot_Close();

    __delay_cycles(1000000);


}

}