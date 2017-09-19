#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <avr/io.h> 
#include <string.h>

#define F_CPU 8000000 
#define BAUD 9600 
#define BAUD_RATE_CALC ((F_CPU/16/BAUD) - 1)  

void sendserial(char *);
#endif