#include <msp430.h>

void init_PilotV(){
P5DIR |= BIT4;          //Set P5.4 as an output

P5OUT &= ~BIT4;        //ensure that the solenoid begins closed
}

void set_PilotV(_Bool open){
if(open){
    P5OUT |= BIT4;      //Opens the solenoid
}
else{
    P5OUT &= ~BIT4;     //Closes the solenoid
}

}

