#include "btn_enc.h"

void button_ini(Button_typedef *butn, volatile uint8_t *ddr, uint8_t pin){
	butn->ddr = ddr;
	butn->port = ddr + 1;
	butn->pin = ddr - 1;
	butn->pin_num = pin;
	*(butn->ddr)&=~(1<<butn->pin_num);
	*(butn->port)|=(1<<butn->pin_num);
	butn->polling_rate = 25;
	butn->next_polling = 0;	
	butn->hold_cnt = 0;
	butn->state = 0;
	butn->old_state = 1;
	butn->new_state = 1;
}

void button_state(Button_typedef *butn){
	if (delay_left(butn->next_polling) == 0){
	butn->new_state = (*butn->pin >> butn->pin_num)&0x01;
		if (butn->old_state != butn->new_state && ((*butn->pin >> butn->pin_num)&0x01) == 1){
			butn->state &= ~((1<<falling_edge)|(1<<on)|(1<<repeat));
			butn->state |= (1<<rising_edge);
		}
		if (butn->old_state != butn->new_state && ((*butn->pin >> butn->pin_num)&0x01) == 0){
			butn->state &= ~(1<<rising_edge);
			butn->state |= (1<<falling_edge)|(1<<on)|(1<<short_click);
		}
	if (butn->state&(1<<falling_edge)) butn->hold_cnt++;
	else butn->hold_cnt = 0;
//------------------------------------------------------------
	if (butn->hold_cnt > HOLD_BUTTON_MS(250) && butn->state&(1<<on)){
		butn->state &= ~(1<<short_click);
	}
//------------------------------------------------------------
	if (butn->hold_cnt > HOLD_BUTTON_MS(500) && butn->hold_cnt < HOLD_BUTTON_MS(1000) && butn->state&(1<<on)){
		butn->state |= (1<<long_click);
	}
//------------------------------------------------------------
	if (butn->hold_cnt > HOLD_BUTTON_MS(1000)){
		butn->state &= ~(1<<long_click);
		butn->state |= (1<<repeat);
	}
//------------------------------------------------------------	
	butn->old_state = butn->new_state;
	butn->next_polling += butn->polling_rate;
	}
}

void button_short_click(Button_typedef *butn){
	if(butn->state&(1<<short_click) && butn->state&(1<<rising_edge)){
		 // do some thing
		butn->state &= ~(1<<short_click);
	}	
}

void button_long_click(Button_typedef *butn){
	if(butn->state&(1<<long_click) && butn->state&(1<<rising_edge)){
		// do some thing
		butn->state &= ~(1<<long_click);
	}
}

void button_repeat(Button_typedef *butn){
	if(butn->state&(1<<repeat)){
		// do some thing
	}
}

void led(uint8_t pin){
	PORTD^=(1<<pin);
}
