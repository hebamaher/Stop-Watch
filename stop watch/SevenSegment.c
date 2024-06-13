#include "SevenSegment.h"

void sevenSegment_Init(){
	DDRC |= 0x0F; //4 o/p pins for the 7-segments decoder
	PORTC &= 0xF0; //display 0 on the six 7-segments;
	DDRA |= 0x3F; //6 o/p pins for 7-segment enables
	PORTA |= 0x3F; //6 enables for the six 7-segments
}
