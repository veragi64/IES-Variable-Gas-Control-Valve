#include <msp430.h>

void init_Pilot(){
    P5DIR |= BIT0; // Set as output
    
    P5OUT &= ~BIT0; // Sets it to zero by default

}


void set_Ignite(_Bool input){
    if(input){
        P5OUT |= BIT0; //Enables the pilot
    }
    else{
        P5OUT &= ~BIT0; //Extinguishes the pilot
    }
}