
#ifndef BTN_ENC_H_
#define BTN_ENC_H_

#include "main.h"
#include "tim0.h"

#define HOLD_BUTTON_MS(n) (uint8_t)(n/butn->polling_rate)

//typedef void (*func)(void);

enum button_flags{
	on = 0,
	falling_edge,
	rising_edge,
	short_click,
	long_click,
	repeat
};


typedef struct {
	volatile uint8_t *ddr;
	volatile uint8_t *port;
	volatile uint8_t *pin;
	uint8_t pin_num;
	uint8_t old_state;
	uint8_t new_state;
	uint8_t state;
	uint8_t hold_cnt;
	int16_t next_polling;
	uint8_t polling_rate;
}Button_typedef;

void button_ini(Button_typedef *butn, volatile uint8_t *ddr, uint8_t pin);
//void button(Button_typedef *butn);
void button_state(Button_typedef *butn);
void button_short_click(Button_typedef *butn);
void button_long_click(Button_typedef *butn);
void button_repeat(Button_typedef *butn);
void led(uint8_t pin);

#endif /* BUTTON_H_ */