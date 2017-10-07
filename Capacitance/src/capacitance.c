#include "capacitance.h"

int ADCvalue = 0;

resistor r;

int main(void)
{
    int i = 0;
    start_adc();
    long double * capacitance = (long double*) malloc(sizeof(long double));;
    unsigned int * time = (unsigned int*) malloc(sizeof(unsigned int));
    unsigned int * a = (unsigned int*) malloc(sizeof(unsigned int)*2);
    resistor r_list[5] = {{EC_1, R_1}, {EC_2, R_2}, {EC_3, R_3}, {EC_4, R_4}, {EC_5, R_5}};
    for(i; i>=0; i++)
    {
        r = r_list[3];
        charge_capacitor();
        discharge_capacitor(time, &a);
        determine_capacitance(time, &a, capacitance);
        display_capacitance(capacitance);
    }
    free(capacitance);
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
    DDRB = CP;
    DDRD = CM;
    PORTD = 0x00;
    PORTB = CP;
    _delay_ms(CHARGE_DELAY);
}

void discharge_capacitor(int * time, unsigned int ** a){   //discharges the capacitor and measures the discharge rate
    DDRB = 0x00;
    DDRD = r.address + CM;
    PORTB = 0x00;
    PORTD = 0x00;
    unsigned int i = 0;
    _delay_ms(100);
    (*a)[0] = (*a)[1] = ADCvalue;
    while((*a)[1]>1000){
        _delay_ms(1);
        (*a)[1] = ADCvalue;
        i++;

    }
    *time = i;

}
void determine_capacitance(int * time, unsigned int ** a, long double * capacitance){ //calculates the capacitance
    *capacitance =((double)(*time) * TIME_CORRECTION) / (-1000 * r.resistance * (log((*a)[1]) - log((*a)[0])));
}
void display_capacitance(long double * capacitance){    //displays the resistance, so far only on serial
    _delay_ms(10);
    char* out = "                     ";
    sprintf(out, "%10lf\t%u\n", *capacitance, r.address);
    sendserial(out);

}

ISR(ADC_vect)   //ADC interrupts
{

    ADCvalue = ADC;

}
