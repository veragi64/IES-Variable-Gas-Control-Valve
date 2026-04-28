#include <msp430.h>
#include <global_vars.h>

void init_30sTimer(){
    TB0CTL; //Clear Timer

    TB0CTL |= TBSSEL__ACLK | ID__8; //Signal source set to aux clock (32768Hz) and first divider set to 8

    TB0EX0 = TBIDEX_7; //expansion divider set to 8  32768/8/8=512

    TB0CCR0 = 15360; // 30 second threshold  512 * 30s = 15360

    TB0CCTL0 = CCIE; //Enables CCR0 interrupt
    TB0CTL |= MC__UP; // Start timer in Up Mode which means it starts at 0 and counts up
}

void init_ADC_HardwareTimer(){
    RTCMOD = 3277-1; // 32,768Hz * 0.1s = ~3277 counts
    RTCCTL = RTCSS_2| RTCPS_0 | RTCSR | RTCIE; //RTCSS_2 = 32kHz aux clock, RTCPS_0 = makes the predivider 1, RTCSR = applies changes to the RTC, RTCIE = enables interrupts
}
void init_Sensors(){

    P1SEL0 |= BIT5 | BIT3;         //Converting 1.5, 1.3, and 5.1 to analog mode
    P1SEL1 |= BIT5 | BIT3;         // POT (1.5), Thermocouple (1.3), Thermistor (5.1) 
    P5SEL0 |= BIT1;
    P5SEL1 |= BIT1;

    // NOTE:
    // THIS SECTION OF CODE WAS PROGRAMED WITH THE HELP OF Notebook Lm
    // CODE BLOCKS WILL BE GIVEN IN THE ENGINEERING NOTEBOOK FOR THIS GROUP

    ADCCTL0 &= ~ADCENC;                 //Disable to modify
    
    ADCCTL1 = ADCCONSEQ_1 | ADCSHS_1 | ADCSHP | ADCSSEL_2 | ADCDIV_7; ////Sets squence of channels to decrement and make the adc triggered by the real time clock                 

    ADCCTL0 |= ADCMSC | ADCON | ADCSHT_15;          // Allows one timer trigger to start the entire sequence; Turn ADC ON
    ADCCTL2 = ADCRES_2;                     //Set resolution to 12-bit 
    
    ADCMCTL0 = ADCINCH_9;               //Sample A9-A0 decending
    ADCIE |= ADCIE0;                    //Enable conversion complete interrupt
    ADCCTL0 |= ADCENC;                  //Re-enable ADC

////////////////////////////////////////////////////////////////////////////////////////////////////////

    // NOTE:
    // THIS SECTION OF CODE WAS PROGRAMED WITH THE HELP OF Notebook Lm
    // CODE BLOCKS WILL BE GIVEN IN THE ENGINEERING NOTEBOOK FOR THIS GROUP
}
    /*
    unsigned int get_ADC_Result( unsigned int channel){
                      // Pause the ADC when selecting channels
        ADCMCTL0 = channel;                // Tells the ADC to look at a specific pin
        ADCCTL0 |= ADCENC | ADCSC;         // This line of code "arms" the ADC, and then takes a reading

        while(ADCCTL1 & ADCBUSY);          //Tell the ADC to Finish measuring the value before taking other readings

        return ADCMEM0;                    // Return the 12 bit digital number



    }
    */
////////////////////////////////////////////////////////////////////////////////////////////////////////

    // NOTE:
    // THIS SECTION OF CODE WAS PROGRAMED WITH THE HELP OF Notebook Lm
    // CODE BLOCKS WILL BE GIVEN IN THE ENGINEERING NOTEBOOK FOR THIS GROUP

    /*unsigned int read_POT(){
        return get_ADC_Result(ADCINCH_5);
    }*/
    //Had to separate conversion functions as integrating them caused weird glitches when converting int to float
    /*
    float convert_POT(int input){
        float TempF = (0.0073f * (-(float)input)) + 120; //Equation to convert potentiometer range to degrees F (90-120)
        SetPoint_F = TempF;
        return TempF;
    }*/
    /*
    unsigned int read_Thermocouple(){
        return get_ADC_Result(ADCINCH_1);
    }

    unsigned int read_Thermistor(){
        return get_ADC_Result(ADCINCH_9);
    }*/
    
    //Had to separate conversion functions as integrating them caused weird glitches when converting int to float
    /*float convert_Thermistor(int input){
        float TempF =  (0.04594f * (float)input) - 16.1127f; //Linear Approximation
        Thermistor_F = TempF;
        return TempF;
    }
    */

    _Bool FlameDetect(int input){
        if(input > 80){
            return 1;
        }
        else{
            return 0;
        }
    }

