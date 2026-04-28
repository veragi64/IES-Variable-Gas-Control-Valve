#include <msp430.h>

//extern float SetPoint_F;
//extern float Thermistor_F;
extern volatile _Bool FlameDetectV;
extern volatile unsigned int SetP;
extern volatile unsigned int TMist;
extern volatile unsigned int TCoup;
extern volatile char STATE;