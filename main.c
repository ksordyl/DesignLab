#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include <stdlib.h>
#include <stdio.h>

int ADC0_Read()						//channel ADC0
{
	int lower_bits,higher_bits,result;
	ADMUX = 0b01000000;
	_delay_ms(1);
	ADCSRA|=(1<<6);              //Turning on conversion
	while(ADIF==0);
	lower_bits=ADCL;
	higher_bits=ADCH;
	result=lower_bits|higher_bits<<8;         //Accessing converted value by shifting
	return result;
}
int ADC1_Read()						//channel ADC1
{
	ADMUX = 0b01000001;
	int lower_bits,higher_bits,result;
	_delay_ms(1);
	ADCSRA|=(1<<6);              //Turning on conversion
	while(ADIF==0);
	lower_bits=ADCL;
	higher_bits=ADCH;
	result=lower_bits|higher_bits<<8;         //Accessing converted value by shifting
	return result;
}
int ADC2_Read()						//channel ADC2
{
	ADMUX = 0b01000010;
	int lower_bits,higher_bits,result;
	_delay_ms(1);
	ADCSRA|=(1<<6);              //Turning on conversion
	while(ADIF==0);
	lower_bits=ADCL;
	higher_bits=ADCH;
	result=lower_bits|higher_bits<<8;         //Accessing converted value by shifting
	return result;
}

void led(int val){
	//ports as outputs
	DDRB=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5);
	PORTB &= (0<<0)|(0<<1)|(0<<2)|(0<<3)|(0<<4)|(0<<5);

	if(val >= 0 && val <= 511){
		PORTB |= (1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);
	}
	if(val >= 512 && val <= 1022){
		PORTB |= (1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1);
	}
	if(val >= 1023 && val <= 1533){
		PORTB |= (1<<5)|(1<<4)|(1<<3)|(1<<2);
	}
	if(val >= 1534 && val <= 2044){
		PORTB |= (1<<5)|(1<<4)|(1<<3);
	}
	if(val >= 2045 && val <= 2555){
		PORTB |= (1<<5)|(1<<4);
	}
	if(val >= 2556 && val <= 3069){
		PORTB |= (1<<5);
	}
}

int main(void)
{
	//DDRC=(0<<0)|(0<<1)|(0<<2);			//ADC0, ADC1, ADC2 ports as input
	//DDRB=(1<<1);					//set PB1 as output
	DDRD=(0<<2);					//set PD2 as input (for pushbutton)
	DDRC=(1<<3);					//ADC3 as output //pompka
	ADCSRA = 0x87;					//enable ADC with given parameters
	int ADC0val=0, ADC1val=0, ADC2val=0, suma = 0;
	
	while (1)
	{
		ADC0val=ADC0_Read();			//if the sensor does not detect moisture
		ADC1val=ADC1_Read();			//it outputs the value 1023
		ADC2val=ADC2_Read();
		suma = ADC0val + ADC1val + ADC2val; //0 - 3069
		led(suma);
		//logika dla 3 czujnikow wilgoci
		
		if(PIND & (1<<2)) //If switch is pressed
		{
			PORTC |= (1<<3); //Turns ON LED
			_delay_ms(3000); //3 second delay
			PORTC &= ~( 1<<3 );//Turns OFF LED
		}
		if(ADC0val < 700 || ADC1val < 700 || ADC2val < 700)
		{
			PORTC &= ~( 1<<3 );
		}
		else
		{
			PORTC |= (1<<3);
			_delay_ms(3000);
			PORTC &= ~( 1<<3 );
			_delay_ms(5000);
		}
	}
}






