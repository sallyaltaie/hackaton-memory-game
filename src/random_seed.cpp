#include "../include/random_seed.hpp"

#include <avr/io.h>
#include <stdlib.h>

// solution from http://www.bytecruft.com/2013/03/seeding-standard-c-random-number.html
// thank you P <3

void setup_seed()
{
    unsigned char oldADMUX = ADMUX;
    ADMUX |=  _BV(MUX0); //choose ADC1 on PB2
    ADCSRA |= _BV(ADPS2) |_BV(ADPS1) |_BV(ADPS0); //set prescaler to max value, 128

    ADCSRA |= _BV(ADEN); //enable the ADC
    ADCSRA |= _BV(ADSC); //start conversion

    while (ADCSRA & _BV(ADSC)); //wait until the hardware clears the flag. Note semicolon!

    unsigned char byte1 = ADCL;

    ADCSRA |= _BV(ADSC); //start conversion

    while (ADCSRA & _BV(ADSC)); //wait again note semicolon!

    unsigned char byte2 = ADCL;

    unsigned int seed = byte1 << 8 | byte2;

    srand(seed);

    ADCSRA &= ~_BV(ADEN); //disable ADC

    ADMUX = oldADMUX;
}