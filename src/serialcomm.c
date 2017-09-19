#include "serialcomm.h"

void sendserial(char* ar) {
    
    //High and low bits
    UBRR0H = (BAUD_RATE_CALC >> 8); 
    UBRR0L = BAUD_RATE_CALC; 
    //////////////// 
    //transimit and recieve enable
    UCSR0B = (1 << TXEN0)| (1 << TXCIE0) | (1 << RXEN0) | (1 << RXCIE0); 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //8 bit data format
    ////////////////////////////////////////////////////////////////
    int i = 0;
    while (( UCSR0A & (1<<UDRE0))  == 0){};
    for (i = 0; i < strlen(ar); i++){ 
        while (( UCSR0A & (1<<UDRE0))  == 0){};
        UDR0 = ar[i]; 
    }
}