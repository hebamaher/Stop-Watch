#include <avr/io.h>
#include <util/delay.h>
#include "Timer1.h"
#include "SevenSegment.h"

extern unsigned char flag1;
unsigned char seconds;
unsigned char minutes;
unsigned char hours;

void INT0_Init(void){
	DDRD &= ~(1<<PD2); //i/p
	PORTD |= (1<<PD2); //internal pull up
	MCUCR |= (1<<ISC01); //falling edge
	GICR |= (1<<INT0);
	SREG |= (1<<7);
}

ISR(INT0_vect){
	TCNT1 = 0; //to count from the start

	seconds = 0;
	minutes = 0;
	hours = 0;
}

void INT1_Init(void){
	DDRD &= ~(1<<PD3); //i/p
	//external pull down
	MCUCR = (1<<ISC11) | (1<<ISC10); //rising edge
	GICR |= (1<<INT1);
	SREG |= (1<<7);
}

ISR(INT1_vect){
	TCCR1B &= ~(1 << CS12);  //clear clock source
	TCCR1B &= ~(1 << CS10);
}

void INT2_Init(void){
	DDRB &= ~(1<<PB2); //i/p
	PORTB |= (1<<PB2); //internal pull up
	MCUCSR &= ~(1<<ISC2); //falling edge
	GICR |= (1<<INT2);
	SREG |= (1<<7);
}

ISR(INT2_vect){
	TCCR1B |= (1<<CS10) | (1<<CS12); //enable clock source
}

int main(void){
	Timer1_Comp_Init();
	INT0_Init();
	INT1_Init();
	INT2_Init();
	sevenSegment_Init();

	while(1){
		flag1 = 0;

		PORTA = (PORTA & 0xC0) | 0x01;
		PORTC = (PORTC & 0xF0) | ((seconds%10) & 0x0F); //to display the first seconds digit
		_delay_ms(3);
		PORTA = (PORTA & 0xC0) | 0x02;
		PORTC = (PORTC & 0xF0) | ((seconds/10) & 0x0F); //to display the second seconds digit
		_delay_ms(3);
		PORTA = (PORTA & 0xC0) | 0x04;
		PORTC = (PORTC & 0xF0) | ((minutes%10) & 0x0F);
		_delay_ms(3);
		PORTA = (PORTA & 0xC0) | 0x08;
		PORTC = (PORTC & 0xF0) | ((minutes/10) & 0x0F);
		_delay_ms(3);
		PORTA = (PORTA & 0xC0) | 0x10;
		PORTC = (PORTC & 0xF0) | ((hours%10) & 0x0F);
		_delay_ms(3);
		PORTA = (PORTA & 0xC0) | 0x20;
		PORTC = (PORTC & 0xF0) | ((hours/10) & 0x0F);
		_delay_ms(3);

		if (flag1 == 1) {
			if (seconds < 60) {
				seconds++;
			}

			 if (seconds == 60) {
				minutes++;
				seconds = 0;
			}

			if (minutes == 60) {
				hours++;
				minutes = 0;
			}

			if (hours == 100) {
				hours = 0;
			}
		}

	}
}

