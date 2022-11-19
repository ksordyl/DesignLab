#include <avr/io.h>
#include <stdlib.h>

int ADC0_Read()						//channel ADC0
{
	ADMUX = 0b01000000;				//REFS0->1, ADLAR->0, ADC->0
	ADCSRA |= (1<<ADSC);			//start conversion
	while ((ADCSRA &(1<<ADIF))==0);	//checking if conversion has ended
	ADCSRA |=(1<<ADIF);				//set ADIF bit of ADCSRA register
	return(ADCW);					//return the ADCW
}
int ADC1_Read()						//channel ADC1
{
	ADMUX = 0b01000001;
	ADCSRA |= (1<<ADSC);
	while ((ADCSRA &(1<<ADIF))==0);
	ADCSRA |=(1<<ADIF);
	return(ADCW);
}
int ADC2_Read()						//channel ADC2
{
	ADMUX = 0b01000010;
	ADCSRA |= (1<<ADSC);
	while ((ADCSRA &(1<<ADIF))==0);
	ADCSRA |=(1<<ADIF);
	return(ADCW);
}

int main(void)
{
	DDRC=(0<<0)|(0<<1)|(0<<2);		//ADC0, ADC1, ADC2 ports as input
	DDRB=(1<<1);					//set PB1 as output
	DDRB=(0<<7);					//set PB7 as input (for pushbutton)
	ADCSRA = 0x87;					//enable ADC with given parameters
	int ADC0val=0, ADC1val=0, ADC2val=0;
    while (1) 
    {
		ADC0val=ADC0_Read();		//if the sensor does not detect moisture
		ADC1val=ADC1_Read();		//it outputs the value 1023
		ADC2val=ADC2_Read();		//(1024 samples in range from 0V to 5V)
		if((PINB & (1<<7)))
		{
			PORTB|=(1<<7);			//for DC motor
				//to be done on interrupts
		}
    }
}

