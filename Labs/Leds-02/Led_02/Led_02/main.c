/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN0  PB0     // AVR pin where green LED is connected
#define LED_GREEN1  PB1 
#define LED_GREEN2  PB2 
#define LED_GREEN3  PB3 
#define LED_GREEN4  PB4 
#define BUTTON_LED  PC1
#define BTN			PD0
#define BLINK_DELAY 500
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed.
 */
int main(void)
{
	int btn_memory = 0; // turnig off and on leds
	
	
    // LED 0
    DDRB = DDRB | (1<<LED_GREEN0);
    PORTB = PORTB & ~(1<<LED_GREEN0);
	
	// LED 1 
	DDRB = DDRB | (1<<LED_GREEN1);
	PORTB = PORTB & ~(1<<LED_GREEN1);

	// LED 2
	DDRB = DDRB | (1<<LED_GREEN2);
	PORTB = PORTB & ~(1<<LED_GREEN2);

	// LED 3
	DDRB = DDRB | (1<<LED_GREEN3);
	PORTB = PORTB & ~(1<<LED_GREEN3);

	// LED 4
	DDRB = DDRB | (1<<LED_GREEN4);
	PORTB = PORTB & ~(1<<LED_GREEN4);

	//BUTTON
	
	DDRD = DDRD & ~(1<<BTN);
	PORTD = PORTD | (1<<BTN);
	
   //button led
   DDRC = DDRC | (1<<BUTTON_LED); 
   PORTC = PORTC & ~(1<<BUTTON_LED);
   
    // Infinite loop
    while (1)
	{

		if (bit_is_clear(PIND, BTN))
		{
			if (btn_memory == 0)
			{
				btn_memory = 1;  // turning on
				PORTC = PORTC ^ (1<<BUTTON_LED);  // Turning on button led to see if it works
			}else{
				btn_memory = 0;
				PORTC = PORTC ^ (1<<BUTTON_LED);  // Turning off button led
				_delay_ms(5000); // Time for turning off button 
			}
		}
		
		if (btn_memory == 1)
		{	
			PORTB = PORTB ^ (1<<LED_GREEN0);  // Turning on Led0
			_delay_ms(BLINK_DELAY);
			
			PORTB = PORTB ^ (1<<LED_GREEN0);  // Turning off Led0
			PORTB = PORTB ^ (1<<LED_GREEN1);  // Turning on  Led1
			_delay_ms(BLINK_DELAY);
				
			PORTB = PORTB ^ (1<<LED_GREEN1);  // Turning off Led1
			PORTB = PORTB ^ (1<<LED_GREEN2);  // Turning on  Led2
			_delay_ms(BLINK_DELAY);
				
			PORTB = PORTB ^ (1<<LED_GREEN2);  // Turning off Led2
			PORTB = PORTB ^ (1<<LED_GREEN3);  // Turning on  Led3
			_delay_ms(BLINK_DELAY);
				
			PORTB = PORTB ^ (1<<LED_GREEN3);  // Turning off Led3
			PORTB = PORTB ^ (1<<LED_GREEN4);  // Turning on  Led4
			_delay_ms(BLINK_DELAY);
				
			PORTB = PORTB ^ (1<<LED_GREEN4);  // Turning off Led4
			PORTB = PORTB ^ (1<<LED_GREEN3);  // Turning on  Led3
			_delay_ms(BLINK_DELAY);
			
			PORTB = PORTB ^ (1<<LED_GREEN3);  // Turning off Led3
			PORTB = PORTB ^ (1<<LED_GREEN2);  // Turning on  Led2
			_delay_ms(BLINK_DELAY);
			
			PORTB = PORTB ^ (1<<LED_GREEN2);  // Turning off Led2
			PORTB = PORTB ^ (1<<LED_GREEN1);  // Turning on  Led1
			_delay_ms(BLINK_DELAY);
			
			PORTB = PORTB ^ (1<<LED_GREEN1);  // Turning off Led1
			PORTB = PORTB ^ (1<<LED_GREEN0);  // Turning on  Led0
			_delay_ms(BLINK_DELAY);
			
			PORTB = PORTB ^ (1<<LED_GREEN0);  // Turning on  Led0
			_delay_ms(BLINK_DELAY);
			
		}else
		{
		}
		
	}
	return 0;
		
	}