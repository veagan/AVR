#ifndef TIM0_H_
#define TIM0_H_
#include <avr/interrupt.h>
#include <stdint.h>
#include "main.h"

void tim0_ini(void);
int16_t delay_left(int16_t delay);
#endif /* TIM0_H_ */