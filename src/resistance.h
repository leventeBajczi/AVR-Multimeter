#ifndef RESISTANCE_H
#define RESISTANCE_H

#include <avr/io.h>
#include <stdio.h>
#include "serialcomm.h"
#include <avr/interrupt.h>
#include <math.h>
#include <util/delay.h>


//B register
#define CP 0b00000010
#define CM 0b00000100
#define EC 0b00000001

#define CAPACITANCE 0.000001

#endif