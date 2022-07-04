#include "tim0.h"

static volatile int16_t compare_cnt = 0;

ISR(TIMER0_COMPA_vect){
	compare_cnt++;
	OCR0A += 249;
}

void tim0_ini(void){
	TCCR0B|= (0<<CS02)|(1<<CS01)|(1<<CS00);
	TIMSK0|= (0<<OCIE0B)|(1<<OCIE0A)|(0<<TOIE0);
}

int16_t delay_left(int16_t delay){
	return (compare_cnt-delay);
}