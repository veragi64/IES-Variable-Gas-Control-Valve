#include <msp430.h>
#include <global_vars.h>


void init_Sensors(){

    P1SEL0 |= BIT5 | BIT3 | BIT6;         //Converting 1.5, 1.3, and 1.6 to analog mode
    P1SEL1 |= BIT5 | BIT3 | BIT6;         // POT (1.5), Thermocouple (1.3), Thermistor (1.6) 

    // NOTE:
    // THIS SECTION OF CODE WAS PROGRAMED WITH THE HELP OF Notebook Lm
    // CODE BLOCKS WILL BE GIVEN IN THE ENGINEERING NOTEBOOK FOR THIS GROUP

    ADCCTL0 |= ADCSHT_2 | ADCON;          // 16 clock cycles for sampling; Turn ADC ON
    ADCCTL1 |= ADCSHP;                    // Use the internal sampling timer
    ADCCTL2 &= ~ADCRES;                   // Clear resolution settings
    ADCCTL2 |= ADCRES_2; 

////////////////////////////////////////////////////////////////////////////////////////////////////////

    // NOTE:
    // THIS SECTION OF CODE WAS PROGRAMED WITH THE HELP OF Notebook Lm
    // CODE BLOCKS WILL BE GIVEN IN THE ENGINEERING NOTEBOOK FOR THIS GROUP
}

    unsigned int get_ADC_Result( unsigned int channel){
        ADCCTL0 &= ~ADCENC;                // Pause the ADC when selecting channels
        ADCMCTL0 = channel;                // Tells the ADC to look at a specific pin
        ADCCTL0 |= ADCENC | ADCSC;         // This line of code "arms" the ADC, and then takes a reading

        while(ADCCTL1 & ADCBUSY);          //Tell the ADC to Finish measuring the value before taking other readings

        return ADCMEM0;                    // Return the 12 bit digital number



    }
////////////////////////////////////////////////////////////////////////////////////////////////////////

    // NOTE:
    // THIS SECTION OF CODE WAS PROGRAMED WITH THE HELP OF Notebook Lm
    // CODE BLOCKS WILL BE GIVEN IN THE ENGINEERING NOTEBOOK FOR THIS GROUP

    unsigned int read_POT(){
        return get_ADC_Result(ADCINCH_5);
    }
    //Had to separate conversion functions as integrating them caused weird glitches when converting int to float
    float convert_POT(int input){
        float TempF = (0.0073f * (-(float)input)) + 120; //Equation to convert potentiometer range to degrees F (90-120)
        SetPoint_F = TempF;
        return TempF;
    }

    unsigned int read_Thermocouple(){
        return get_ADC_Result(ADCINCH_1);
    }

    unsigned int read_Thermistor(){
        return get_ADC_Result(ADCINCH_6);
    }
    
    //Had to separate conversion functions as integrating them caused weird glitches when converting int to float
    float convert_Thermistor(int input){
        float TempF =  (0.04594f * (float)input) - 16.1127f; //Linear Approximation
        Thermistor_F = TempF;
        return TempF;
    }

    _Bool FlameDetect(){
        if(read_Thermocouple() > 80){
            FlameDetectV = 1;
            return 1;
        }
        else{
            FlameDetectV = 0;
            return 0;
        }
    }