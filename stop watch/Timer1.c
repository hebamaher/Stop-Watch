#include "Timer1.h"

unsigned char flag1;

void Timer1_Comp_Init(void){
	TCCR1A |= (1<<FOC1A);
	TCCR1B = (1<<CS10) | (1<<CS12) | (1<<WGM12); //prescalling 1024
	TCNT1H = 0;
	TCNT1L = 0;
	OCR1A = 977; //compare value
	TIMSK = (1<<OCIE1A);
	SREG = (1<<7);
}

ISR(TIMER1_COMPA_vect){
	flag1 = 1;

}
