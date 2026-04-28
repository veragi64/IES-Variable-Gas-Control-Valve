#include <msp430.h>

//float SetPoint_F = 0;
//float Thermistor_F = 0;
volatile _Bool FlameDetectV = 0;
volatile unsigned int SetP = 0;
volatile unsigned int TMist = 0;
volatile unsigned int TCoup = 0;
volatile char STATE = 'I'; 