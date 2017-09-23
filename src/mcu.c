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

void start_adc();

void charge_capacitor();
void discharge_capacitor(int*, int*);
void determine_resistance(int*, int*);
void display_resistance(double);

int ADCvalue = 0;

int main(void)
{
    start_adc();
    
    while(1) 
    {
        int resistance = 0;
        int time = 0;
        charge_capacitor();
        discharge_capacitor(&time, &resistance);
        determine_resistance(&time, &resistance);
        display_resistance(resistance);
    }
    
}

void start_adc(){
    ADMUX = 0;                
    ADMUX |= (1 << REFS0);    
    ADMUX |= (1 << ADLAR);    

    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
    ADCSRA |= (1 << ADATE);  
    
    ADCSRB = 0;               

    ADCSRA |= (1 << ADEN);    
    ADCSRA |= (1 << ADIE);    

    ADCSRA |= (1 << ADSC);    

    sei(); 
}


void charge_capacitor(){
    DDRB = CP+CM;
    PORTB = CP;
    _delay_ms(2000);
}

void discharge_capacitor(int * time, int * voltages){
    DDRB = EC + CM;
    PORTB = 0x00;
    unsigned int a[2], i = 0;
    _delay_ms(100);
    a[1] = 1001;
    a[0] = ADCvalue;
    while(a[1]>1000){
        a[1] = ADCvalue;
        i++;
        _delay_ms(1);

    }
    unsigned long long voltages2 =((double)i) / (-1000 * CAPACITANCE * (log(a[1]) - log(a[0])));
    _delay_ms(10);
    char* out = "         ";
    sprintf(out, "%7lu\n", (voltages2));
    sendserial(out);
    *time = i;
    
    
}
void determine_resistance(int* time, int * resistance){
    /*
    V = 3V * e^(-t/RC)
    ln(1/3) = -t / RC
    ln(1/3)*R = -t / C
    R = -t/(C*ln(1/3))
   */

   // *resistance = ((double)*time/1000) / (-100.0 * CAPACITANCE * *resistance);

 


}
void display_resistance(double resistance){

}

ISR(ADC_vect)
{

    ADCvalue = ADC;

}
