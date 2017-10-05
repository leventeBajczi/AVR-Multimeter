#ifndef RESISTANCE_H
#define RESISTANCE_H

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "serialcomm.h"
#include <avr/interrupt.h>
#include <math.h>
#include <util/delay.h>


//B register
#define CP 0b00000010

//D register
#define CM 0b00100000
#define EC 0b00000100

#define CAPACITANCE 1e-7
#define CHARGE_DELAY 2000
#define TIME_CORRECTION 1.0249437 //measured with simulator


void start_adc();
void charge_capacitor();
void discharge_capacitor(int*, unsigned int**);
void determine_resistance(int*, unsigned int**, unsigned long *);
void display_resistance(unsigned long *);


#endif
