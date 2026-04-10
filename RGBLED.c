
#include <msp430.h>

void RGB_init(){
    // Pin Initializations
    P6DIR |= BIT0 | BIT1 | BIT2;        // Set RGB Pins 
    P6SEL1 &= ~(BIT0 | BIT1 | BIT2);    // Set Pins for
    P6SEL0 |= BIT0 | BIT1 | BIT2;       //


    //Timer Initialization
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;

    TB3CCTL1 = OUTMOD_7;                // Set RED CCR1 to Reset/Set
    TB3CCTL2 = OUTMOD_7;                // Set Green CCR2 to Reset/Set
    TB3CCTL3 = OUTMOD_7;                // Set Blue CCR3 to Reset/Set

    // Initialize Output Duty Cycle to 0%
    TB3CCR1 = 0;
    TB3CCR2 = 0;
    TB3CCR3 = 0;

    // Setting Initial Period of PWM
    TB3CCR0 = 1024-1;                   // 1ms Period (1024 counts * 1us)
}

void RGB_setColor( char Red, char Green, char Blue){

    int RedValue = 255 - Red;
    RedValue = RedValue << 2;            // Multiply Red Hex Value by 4
    if (RedValue >= 1000)               // If RedValue Range of 999
    {              
        RedValue = 999;
    }

    int GreenValue = 255 - Green;
    GreenValue = GreenValue << 2;    // Multiply Green Hex Value by 4
    if (GreenValue >= 1000)             // If GreenValue Range of 999
    {              
        GreenValue = 999;
    }
    int BlueValue = 255 - Blue;
    BlueValue = BlueValue << 2;    // Multiply Blue Hex Value by 4
    if (BlueValue >= 1000)             // If BlueValue Range of 999
    {              
        BlueValue = 999;
    }

    TB3CCR1 = RedValue;
    TB3CCR2 = GreenValue;
    TB3CCR3 = BlueValue;
    /*
    TB3CCR1
    TB3CCR1
    TB3CCR1
    */
}