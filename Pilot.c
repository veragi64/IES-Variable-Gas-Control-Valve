#include <msp430.h>

void init_Pilot(){
    P5DIR |= BIT0;
    
    P5OUT &= ~BIT0;

}


void set_Ignite(_Bool input){
    if(input){
        P5OUT |= BIT0;
    }
    else{
        P5OUT &= ~BIT0;
    }
}