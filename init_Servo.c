#include <msp430.h>

void init_Servo(){
    // Pin Initializations

    P2DIR |= BIT1;          // Set pins for Servo

    // Setting Pin As a Timer (TB1.2)

    P2SEL1 &= ~(BIT1);        //P2SEL0 = 0  
    P2SEL0 |= BIT1;         //P2SEL1 = 1

    //Timer Initialization

    TB1CTL = TBSSEL__SMCLK | MC__UP | TBCLR;

    TB1CCTL2 = OUTMOD_7;   // Initialize Output Duty Cycle to 0

    TB1CCR2 = 0;            // Set the Servo's angle to 0


    // Setting Initial Period of PWM

    TB1CCR0 = 20000 -1;     // 20ms Period (20000 cycles *1us)

}

void setServo(unsigned char Percent){

if(Percent >= 100){        // Setting Boundries for Percent
    Percent = 100;
}

if(Percent <=0){
    Percent = 0;
}

int Cycle = 1000 + (Percent * 10); //Setting duty cycle value based on percent
                                   // Helped by Lm NOTEBOOK

TB1CCR2 = Cycle;                   //Updating TB1.2

}
