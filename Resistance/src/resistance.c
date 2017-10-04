#include "resistance.h"

int ADCvalue = 0;

int main(void)
{
    start_adc();
    unsigned long * resistance = (unsigned long*) malloc(sizeof(unsigned long));;
    unsigned int * time = (unsigned int*) malloc(sizeof(unsigned int));
    unsigned int * a = (unsigned int*) malloc(sizeof(unsigned int)*2);
    for(;;)
    {
        charge_capacitor();
        discharge_capacitor(time, &a);
        determine_resistance(time, &a, resistance);
        display_resistance(resistance);
    }
    free(resistance);
    free(time);
    free(a);
    
}

void start_adc(){
    ADMUX = 0;                //use ADC0
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


void charge_capacitor(){        //charges up the capacitor
    DDRB = CP+CM;
    PORTB = CP;
    _delay_ms(CHARGE_DELAY);
}

void discharge_capacitor(int * time, unsigned int ** a){   //discharges the capacitor and measures the discharge rate
    DDRB = EC + CM;
    PORTB = 0x00;
    unsigned int i = 0;
    _delay_ms(100);
    *a[0] = *a[1] = ADCvalue;
    while(*a[1]>1000){
        *a[1] = ADCvalue;
        i++;
        _delay_ms(10);

    }
    *time = i*10;

}
void determine_resistance(int * time, unsigned int ** a, unsigned long * resistance){ //calculates the resistance
    /*
    V = 3V * e^(-t/RC)
    ln(1/3) = -t / RC
    ln(1/3)*R = -t / C
    R = -t/(C*ln(1/3))
   */

    *resistance =((double)(*time) * TIME_CORRECTION) / (-1000 * CAPACITANCE * (log(*a[1]) - log(*a[0])));

}
void display_resistance(unsigned long * resistance){    //displays the resistance, so far only on serial
    _delay_ms(10);
    char* out = "         ";
    sprintf(out, "%7lu\n", *resistance);
    sendserial(out);
}

ISR(ADC_vect)   //ADC interrupts
{

    ADCvalue = ADC;

}
