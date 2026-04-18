#include <msp430.h>

void init_CFH(){
    P3DIR &= ~BIT0; //Set direction as input
    //No need for internal resistors because of call for heat circuit
}

_Bool CallForHeat(){
    unsigned int CFH = P3IN & BIT0; //Bitmasking to isolate bit 0 of pin 3
    if(CFH > 0){
        return 1;
    }
    else{
        return 0;
    }
}
