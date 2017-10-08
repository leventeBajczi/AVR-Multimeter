#ifndef CAPACITANCE_H
#define CAPACITANCE_H

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "serialcomm.h"
#include <avr/interrupt.h>
#include <math.h>
#include <util/delay.h>


//B register
#define CP      0b00000010

//D register
#define CM    0b10000000
#define EC_1  0b01000000
#define EC_2  0b00100000
#define EC_3  0b00010000
#define EC_4  0b00001000
#define EC_5  0b00000100

#define R_1     1E6 //about 3nF to 300nF
#define R_2     1E5 //about 30nF to 3uF
#define R_3     1E4 //about 300nF to 30uF
#define R_4     1E3 //about 3uF to 300uF
#define R_5     1E2 //about 30uF to 3mF, ONLY USE IF 50mA CAN FLOW THROUGH ANY OF YOUR IO PINS

#define CHARGE_DELAY 500    //adjust if first measurement is off (or in the case of nonconsistent results)
#define TIME_CORRECTION 1.0249437 //measured with simulator for the "while"-loop in discharge_capacitor()

typedef struct resistor resistor;

struct resistor {
    uint8_t address;
    double  resistance;
};


void start_adc();
void charge_capacitor();
void discharge_capacitor(int*, unsigned int**);
void determine_capacitance(int*, unsigned int**, long double *);
void display_capacitance(long double *);


#endif
