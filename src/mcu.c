#include <avr/io.h>
#include <stdio.h>
#include "serialcomm.h"
#include <avr/interrupt.h>
#include <util/delay.h>


//B register
#define CP 0b00000010
#define CM 0b00000100
#define EC 0b00000001

//D register
#define TEST_LED 0b10000000

#define LN_1_3 -0.85235130009 //empirical!!
#define CAPACITANCE 0.0000047
#define TIME_CORRECTION 1.00806451613

void start_timer();

void charge_capacitor();
void discharge_capacitor(int*);
void determine_resistance(int*, float*);
void display_resistance(float);

int elapsed_ms = 0;


int main(void)
{
    start_timer();
    
    while(1) 
    {
        int time = elapsed_ms;
        float resistance = 0.0;
        charge_capacitor();
        discharge_capacitor(&time);
        determine_resistance(&time, &resistance);
        display_resistance(resistance);
    }
    
}

void start_timer(){
    TCCR0A |= (1 << WGM01);     //activate time interrupts every 1ms (0x1E * 8000000Hz) !!! need factor of 1.00806451613 to make up for rounding
    OCR0A = 0x1E;
    TIMSK0 |= (1 << OCIE0A);
    sei();
    TCCR0B |= (1 << CS02);
}


void charge_capacitor(){
    DDRB = CP+CM;
    PORTB = CP;
    _delay_ms(2000);
}

void discharge_capacitor(int * time){
    DDRB = EC + CM;
    *time = elapsed_ms;
    PORTB = 0x00;
    while(PINB != 0x00){
        //wait
    }
    *time = elapsed_ms - *time;

    
}
void determine_resistance(int* time, float * resistance){
    /*
    V = 3V * e^(-t/RC)
    ln(1/3) = -t / RC
    ln(1/3)*R = -t / C
    R = -t/(C*ln(1/3))
    */

    *resistance = ((float)*time) * TIME_CORRECTION / (-100000.0 * CAPACITANCE * LN_1_3);
    char *str = "";
    sprintf(str, "%d\t%d\n\0", *time, (int)*resistance);
    sendserial(str);


}
void display_resistance(float resistance){

}


ISR (TIMER0_COMPA_vect)  
{
    elapsed_ms+=1;
}
