	#ifndef F_CPU
	#define F_CPU 16000000
	#endif
	char keypad[4][3]  =
	{
		{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'},
		{'*','0','#'}
	};
	
	#define keypad[0][0]   PD0
	#define Second_row  PD1
	#define Third_row   PD2
	#define Fourth_row  PD3
	#define LED			PC0
	
	#define First_column PD4
	#define Second_column PD5
	#define Third_column PD6
	
	
	#include <util/delay.h>
	#include <avr/io.h>
	#include "gpio.h"
	#include "keypad.h"
	
	
	
	int main(void)
	{ 
		
		
		GPIO_config_output(&DDRC,LED );
		GPIO_write_low(&PORTC,LED);
		
		//GPIO_config_input_pullup(&DDRD,First_row);
		GPIO_config_input_pullup(&DDRD,Second_row);
		GPIO_config_input_pullup(&DDRD,Third_row);
		GPIO_config_input_pullup(&DDRD,Fourth_row);
		
		//GPIO_config_input_pullup(&DDRD,First_column);
		GPIO_config_input_pullup(&DDRD,Second_column);
		GPIO_config_input_pullup(&DDRD,Third_column);
		
	
		while (1)
		{
					
			if(GPIO_read(PIND0,keypad[0][0]) == 1)
			{
				GPIO_toggle(&PORTC,LED);
			}
					
					
					
					
		}
				
		return ;0
		
		
		
		
	}