#include <msp430.h>
#include "RGBLED.h"
#include "init_Servo.h"
#include "Sensors.h"
void main(void){

    WDTCTL = WDTPW | WDTHOLD;

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
    
    /*init_Sensors();
    P5DIR |= BIT0;
while(1){
    unsigned int value;
    value = read_POT();
    if (value >= 1000){
        P5OUT |= BIT0;
    }
    else {
        P5OUT &= ~BIT0;
    }
}*/
RGB_init();
init_Sensors();
init_Servo();

__delay_cycles(300000);

while(1){

unsigned int percent = 0;
char red = 0, green = 0, blue = 0;

while(percent < 100){
    
    setServo(percent);

    __delay_cycles(300000);

    percent = percent + 10;

}

    
    RGB_setColor(255, 0, 0);

    __delay_cycles(300000);

    RGB_setColor(255, 100, 0);
    
    __delay_cycles(300000);

    RGB_setColor(255, 255, 0);

    __delay_cycles(300000);

    RGB_setColor(0, 255, 0);

    __delay_cycles(300000);

    RGB_setColor(0, 255, 255);

    __delay_cycles(300000);

    RGB_setColor(0, 0, 255);

    __delay_cycles(300000);
}
}



