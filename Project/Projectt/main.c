

#include <avr/io.h>         
#include "gpio.h"
#include "timer.h"           
int keypad = 0;

#define KEYPAD0     PD0  
#define KEYPAD1     PD1 
#define KEYPAD2     PD2
#define KEYPAD3     PD3
#define KEYPAD4     PD4 
#define KEYPAD5     PD5
#define KEYPAD6     PD6

#define Led			PC6
#define Ledd		PC5


int main(void)
{
	GPIO_config_input_nopull(&DDRD, KEYPAD0);
	GPIO_config_input_nopull(&DDRD, KEYPAD1);
	GPIO_config_input_nopull(&DDRD, KEYPAD2);
	
	
	GPIO_config_output(&DDRD, KEYPAD3);
	GPIO_config_output(&DDRD, KEYPAD4);
	GPIO_config_output(&DDRD, KEYPAD5);
	GPIO_config_output(&DDRD, KEYPAD6);
	
	GPIO_config_output(&DDRC, Led); 
	GPIO_write_low(&PORTC, Led);

	GPIO_config_output(&DDRC, Ledd);
	GPIO_write_low(&PORTC, Ledd);
	
	
while(1)
{
	GPIO_write_low(&PORTD, KEYPAD3);
	GPIO_write_low(&PORTD, KEYPAD4);
	GPIO_write_high(&PORTD, KEYPAD5);
	GPIO_write_low(&PORTD, KEYPAD6);
	if (GPIO_read(&PIND, KEYPAD0) == 1)
	{
		GPIO_write_high(&PINC, Led);
	}
	
	
	GPIO_write_low(&PORTD, KEYPAD3);
	GPIO_write_high(&PORTD, KEYPAD4);
	GPIO_write_low(&PORTD, KEYPAD5);
	GPIO_write_low(&PORTD, KEYPAD6);
	
	if (GPIO_read(&PIND, KEYPAD1) == 1)
	{
		GPIO_write_high(&PINC, Ledd);
	}
	

}

return 0;

	
}






 
 