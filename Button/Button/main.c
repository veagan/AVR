#include "main.h"
#include "tim0.h"
#include "btn_enc.h"

int main(void)
{
	DDRD|=(1<<0)|(1<<1)|(1<<2);
	PORTD&=~((1<<0)|(1<<1)|(1<<2));
	tim0_ini();
	sei();
	Button_typedef button1;
	button_ini(&button1, B, 1);
	
	while (1) 
    {
    button_state(&button1);
	button_short_click(&button1);
	}
}

