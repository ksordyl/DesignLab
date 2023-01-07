#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

int ADC0_Read()						//channel ADC0
{
    /*
	ADMUX = 0b01000000;				//REFS0->1, ADLAR->0, ADC->0
	ADCSRA |= (1<<ADSC);				//start conversion
	while ((ADCSRA &(1<<ADIF))==0);			//checking if conversion has ended
	ADCSRA |=(1<<ADIF);				//set ADIF bit of ADCSRA register
	return(ADCW);	*/				//return the ADCW
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

int main(void)
{
	//DDRC=(0<<0)|(0<<1)|(0<<2);			//ADC0, ADC1, ADC2 ports as input
	DDRB=(1<<1);					//set PB1 as output
	DDRD=(0<<2);					//set PD2 as input (for pushbutton)
	DDRC=(1<<5);					//ADC5 as output //pompka
	ADCSRA = 0x87;					//enable ADC with given parameters
	int ADC0val=0, ADC1val=0, ADC2val=0;
	
	
	while (1)
	{

		ADC0val=ADC0_Read();			//if the sensor does not detect moisture
		ADC1val=ADC1_Read();			//it outputs the value 1023
		ADC2val=ADC2_Read();
       if(ADC0val < 700 || ADC1val < 700 || ADC2val < 700)
       {
	       PORTC &= ~( 1<<5 );
       }
       else
       {
	       PORTC |= (1<<5);
       }
	}
}
