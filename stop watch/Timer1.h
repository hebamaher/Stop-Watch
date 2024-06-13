

#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void Timer1_Comp_Init(void);
ISR(TIMER1_COMPA_vect);



#endif /* TIMER1_H_ */
