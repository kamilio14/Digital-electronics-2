/* Defines -----------------------------------------------------------*/
#define KEYPAD0     PC0     // AVR pin where keypad is connected
#define KEYPAD1     PC1     // AVR pin where keypad is connected
#define KEYPAD2     PC2     // AVR pin where keypad is connected
#define KEYPAD3     PC3     // AVR pin where keypad is connected
#define KEYPAD4     PC4     // AVR pin where keypad is connected
#define KEYPAD5     PC5     // AVR pin where keypad is connected
#define KEYPAD6     PC6     // AVR pin where keypad is connected
#define DAC0        PB0     // AVR pin where DAC is connected
#define DAC1        PB1     // AVR pin where DAC is connected
#define DAC2        PB2     // AVR pin where DAC is connected
#define DAC3        PB3     // AVR pin where DAC is connected
#define DAC4        PB4     // AVR pin where DAC is connected
#define DAC5        PB5     // AVR pin where DAC is connected
#define DAC6        PB6     // AVR pin where DAC is connected
#define DAC7        PB7     // AVR pin where DAC is connected
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for UART speed configuration
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "gpio.h"           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include "uart.h"           // Peter Fleury's UART library
 
// Global variables
static uint8_t counter = 0; // overflow counter value set to 0
static uint8_t keypad = 0;  // keypad value set to 0

// Look-up table for sine wave generation


int main(void)
{	
    // 4x3 keyboard input configuration
    GPIO_config_input_nopull(&DDRC, KEYPAD0);
    GPIO_config_input_nopull(&DDRC, KEYPAD1);
    GPIO_config_input_nopull(&DDRC, KEYPAD2);
    // 4x3 keyboard output configuration
    GPIO_config_output(&DDRC, KEYPAD3);
    GPIO_config_output(&DDRC, KEYPAD4);
    GPIO_config_output(&DDRC, KEYPAD5);
    GPIO_config_output(&DDRC, KEYPAD6);

    // DAC output configuration
    GPIO_config_output(&DDRB, DAC0);
    GPIO_config_output(&DDRB, DAC1);
    GPIO_config_output(&DDRB, DAC2);
    GPIO_config_output(&DDRB, DAC3);
    GPIO_config_output(&DDRB, DAC4);
    GPIO_config_output(&DDRB, DAC5);
    GPIO_config_output(&DDRB, DAC6);
    GPIO_config_output(&DDRB, DAC7);

   

    // Write to LCD display
  

    // Configuration of 8-bit Timer/Counter0 for signal generator
    // Overflow interrupt every 128 us
    TIM0_overflow_128us();
    TIM0_overflow_interrupt_enable();
	
    // Configuration of 16-bit Timer/Counter0 for signal generator
    // Overflow interrupt every 262 us
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();
	
    // Initialization of UART to asynchronous, 8N1, 9600
  
	
    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }
    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/

ISR(TIMER1_OVF_vect)
{
	// 4x3 keypad service
	GPIO_write_high(&PORTC, KEYPAD3);
	GPIO_write_low(&PORTC, KEYPAD4);
	GPIO_write_low(&PORTC, KEYPAD5);
	GPIO_write_low(&PORTC, KEYPAD6);
	if (GPIO_read(&PINC, KEYPAD0) == 1)     
	{keypad = 1; counter=0;}
	if (GPIO_read(&PINC, KEYPAD1) == 1)     
	{keypad = 2; counter=0;}
	if (GPIO_read(&PINC, KEYPAD2) == 1)
	{keypad = 3; counter=0;}
	


	
}
// Interrupts from Timer/Counter0 can generate 6 various signals
ISR(TIMER0_OVF_vect)
{
	
	
   if (keypad == 1)
    {
       
		switch(counter)
		{
			case 15:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_high(&PORTB, DAC4);
				GPIO_write_high(&PORTB, DAC5);
				GPIO_write_high(&PORTB, DAC6);
				GPIO_write_high(&PORTB, DAC7);
			break;
			case 30:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_low(&PORTB, DAC5);
				GPIO_write_high(&PORTB, DAC6);
				GPIO_write_high(&PORTB, DAC7);
			break;
			case 62:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_low(&PORTB, DAC5);
				GPIO_write_low(&PORTB, DAC6);
				GPIO_write_high(&PORTB, DAC7);
				break;
			case 80:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_low(&PORTB, DAC5);
				GPIO_write_high(&PORTB, DAC6);
				GPIO_write_low(&PORTB, DAC7);
			break;
			case 100:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_high(&PORTB, DAC5);
				GPIO_write_low(&PORTB, DAC6);
				GPIO_write_low(&PORTB, DAC7);
			break;
			case 110:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_high(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_low(&PORTB, DAC5);
				GPIO_write_low(&PORTB, DAC6);
				GPIO_write_low(&PORTB, DAC7);
			break;
			case 125:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_low(&PORTB, DAC5);
				GPIO_write_low(&PORTB, DAC6);
				GPIO_write_low(&PORTB, DAC7);
			break;
			case 140:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_high(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_low(&PORTB, DAC5);
				GPIO_write_low(&PORTB, DAC6);
				GPIO_write_low(&PORTB, DAC7);
			break;
			case 150:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_high(&PORTB, DAC5);
				GPIO_write_low(&PORTB, DAC6);
				GPIO_write_low(&PORTB, DAC7);
			break;
			case 170:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_low(&PORTB, DAC5);
				GPIO_write_high(&PORTB, DAC6);
				GPIO_write_low(&PORTB, DAC7);
			break;
			case 192:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_low(&PORTB, DAC5);
				GPIO_write_low(&PORTB, DAC6);
				GPIO_write_high(&PORTB, DAC7);
			break;
			case 224:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_low(&PORTB, DAC4);
				GPIO_write_low(&PORTB, DAC5);
				GPIO_write_high(&PORTB, DAC6);
				GPIO_write_high(&PORTB, DAC7);
			break;
			case 239:
				GPIO_write_low(&PORTB, DAC0);
				GPIO_write_low(&PORTB, DAC1);
				GPIO_write_low(&PORTB, DAC2);
				GPIO_write_low(&PORTB, DAC3);
				GPIO_write_high(&PORTB, DAC4);
				GPIO_write_high(&PORTB, DAC5);
				GPIO_write_high(&PORTB, DAC6);
				GPIO_write_high(&PORTB, DAC7);
			break;
			default: ;			
		}
		counter++;
	   if (counter == 256) counter = 0;
	}
// 		if (counter == 15)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_low(&PORTB, DAC3);
//   			GPIO_write_high(&PORTB, DAC4);
//   			GPIO_write_high(&PORTB, DAC5);
//   			GPIO_write_high(&PORTB, DAC6);
//   			GPIO_write_high(&PORTB, DAC7);
//   		}
//   		
//   		if (counter == 30)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_low(&PORTB, DAC3);
//   			GPIO_write_low(&PORTB, DAC4);
//   			GPIO_write_low(&PORTB, DAC5);
//   			GPIO_write_high(&PORTB, DAC6);
//   			GPIO_write_high(&PORTB, DAC7);
//   		}
//   		
//   		if (counter == 62)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_low(&PORTB, DAC3);
//   			GPIO_write_low(&PORTB, DAC4);
//   			GPIO_write_low(&PORTB, DAC5);
//   			GPIO_write_low(&PORTB, DAC6);
//   			GPIO_write_high(&PORTB, DAC7);
//   		}
//   		if (counter == 80)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_low(&PORTB, DAC3);
//   			GPIO_write_low(&PORTB, DAC4);
//   			GPIO_write_low(&PORTB, DAC5);
//   			GPIO_write_high(&PORTB, DAC6);
//   			GPIO_write_low(&PORTB, DAC7);
//   		}
//   		if (counter == 100)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_low(&PORTB, DAC3);
//   			GPIO_write_low(&PORTB, DAC4);
//   			GPIO_write_high(&PORTB, DAC5);
//   			GPIO_write_low(&PORTB, DAC6);
//   			GPIO_write_low(&PORTB, DAC7);
//   		}
//   		
//   		if (counter == 110)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_high(&PORTB, DAC3);
//   			GPIO_write_low(&PORTB, DAC4);
//   			GPIO_write_low(&PORTB, DAC5);
//   			GPIO_write_low(&PORTB, DAC6);
//   			GPIO_write_low(&PORTB, DAC7);
//   		}
//           if (counter == 125)
//           {
//               GPIO_write_low(&PORTB, DAC0);
//               GPIO_write_low(&PORTB, DAC1);
//               GPIO_write_low(&PORTB, DAC2);
//               GPIO_write_low(&PORTB, DAC3);
//               GPIO_write_low(&PORTB, DAC4);
//               GPIO_write_low(&PORTB, DAC5);
//               GPIO_write_low(&PORTB, DAC6);
//               GPIO_write_low(&PORTB, DAC7);
//           }
//   		if (counter == 140)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_high(&PORTB, DAC3);
//   			GPIO_write_low(&PORTB, DAC4);
//   			GPIO_write_low(&PORTB, DAC5);
//   			GPIO_write_low(&PORTB, DAC6);
//   			GPIO_write_low(&PORTB, DAC7);
//   		}
//   		if (counter == 150)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_low(&PORTB, DAC3);
//   			GPIO_write_low(&PORTB, DAC4);
//   			GPIO_write_high(&PORTB, DAC5);
//   			GPIO_write_low(&PORTB, DAC6);
//   			GPIO_write_low(&PORTB, DAC7);
//   		}
//   		if (counter == 170)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_low(&PORTB, DAC3);
//   			GPIO_write_low(&PORTB, DAC4);
//   			GPIO_write_low(&PORTB, DAC5);
//   			GPIO_write_high(&PORTB, DAC6);
//   			GPIO_write_low(&PORTB, DAC7);
//   		}
//   		if (counter == 192)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_low(&PORTB, DAC3);
//   			GPIO_write_low(&PORTB, DAC4);
//   			GPIO_write_low(&PORTB, DAC5);
//   			GPIO_write_low(&PORTB, DAC6);
//   			GPIO_write_high(&PORTB, DAC7);
//   		}
//   		if (counter == 224)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_low(&PORTB, DAC3);
//   			GPIO_write_low(&PORTB, DAC4);
//   			GPIO_write_low(&PORTB, DAC5);
//   			GPIO_write_high(&PORTB, DAC6);
//   			GPIO_write_high(&PORTB, DAC7);
//   		}
//   		if (counter == 239)
//   		{
//   			GPIO_write_low(&PORTB, DAC0);
//   			GPIO_write_low(&PORTB, DAC1);
//   			GPIO_write_low(&PORTB, DAC2);
//   			GPIO_write_low(&PORTB, DAC3);
//   			GPIO_write_high(&PORTB, DAC4);
//   			GPIO_write_high(&PORTB, DAC5);
//   			GPIO_write_high(&PORTB, DAC6);
//   			GPIO_write_high(&PORTB, DAC7);
//   		}
//   		counter++;
//           if (counter == 256) counter = 0;
//       }
// 	
// 	if (keypad == 2)
// 	{
// 		if (counter == 0)
// 		{
// 			GPIO_write_high(&PORTB, DAC0);
// 			GPIO_write_high(&PORTB, DAC1);
// 			GPIO_write_high(&PORTB, DAC2);
// 			GPIO_write_high(&PORTB, DAC3);
// 			GPIO_write_high(&PORTB, DAC4);
// 			GPIO_write_high(&PORTB, DAC5);	
// 			GPIO_write_high(&PORTB, DAC6);
// 			GPIO_write_high(&PORTB, DAC7);
// 		}
// 		counter ++;
// 		if(counter == 200)
// 		{
// 			GPIO_write_low(&PORTB, DAC0);
// 			GPIO_write_low(&PORTB, DAC1);
// 			GPIO_write_low(&PORTB, DAC2);
// 			GPIO_write_low(&PORTB, DAC3);
// 			GPIO_write_low(&PORTB, DAC4);
// 			GPIO_write_low(&PORTB, DAC5);
// 			GPIO_write_low(&PORTB, DAC6);
// 			GPIO_write_low(&PORTB, DAC7);
// 		}
		
	
	
// 		uint8_t sinevalue = sinewave[counter];     //helping variable used to set output pin values
//  		if (sinevalue-127>0)			    {GPIO_write_high(&PORTB, DAC7);  sinevalue=sinevalue-128;}         
// 		else GPIO_write_low(&PORTB, DAC7);
//   		if (sinevalue-63>0)                 {GPIO_write_high(&PORTB, DAC6); sinevalue=sinevalue-64;}
//  		else GPIO_write_low(&PORTB, DAC6);
//   		if (sinevalue-31>0)                 {GPIO_write_high(&PORTB, DAC5); sinevalue=sinevalue-32;}
//   		else GPIO_write_low(&PORTB, DAC5);
//   		if (sinevalue-15>0)                 {GPIO_write_high(&PORTB, DAC4); sinevalue=sinevalue-16;}
//   		else GPIO_write_low(&PORTB, DAC4);
//   		if (sinevalue-7>0)                  {GPIO_write_high(&PORTB, DAC3); sinevalue=sinevalue-8;}
//  		else GPIO_write_low(&PORTB, DAC3);
//   		if (sinevalue-3>0)                  {GPIO_write_high(&PORTB, DAC2); sinevalue=sinevalue-4;}
//   		else GPIO_write_low(&PORTB, DAC2);
//   		if (sinevalue-->0)                  {GPIO_write_high(&PORTB, DAC1); sinevalue=sinevalue-2;}
//   		else GPIO_write_low(&PORTB, DAC1);
//   		if (sinevalue>0)                    {GPIO_write_high(&PORTB, DAC0);}
//   		else GPIO_write_low(&PORTB, DAC0);
//  		counter++;
		 
  //		if (counter == 255) counter = 0;
// 	
// 		
// 		 if (keypad == 3)
// 		 {
// 			 if (counter == 0)
// 			 {
// 				 GPIO_write_low(&PORTB, DAC0);
// 				 GPIO_write_low(&PORTB, DAC1);
// 				 GPIO_write_low(&PORTB, DAC2);
// 				 GPIO_write_low(&PORTB, DAC3);
// 				 GPIO_write_low(&PORTB, DAC4);
// 				 GPIO_write_low(&PORTB, DAC5);
// 				 GPIO_write_low(&PORTB, DAC6);
// 				 GPIO_write_low(&PORTB, DAC7);
// 			 }
// 			 counter++;
// 			 if (counter <= 127)
// 			 {
// 				
// 				if (counter %1 == 0)		GPIO_toggle(&PORTB, DAC1);
// 				if (counter %2 == 0)		GPIO_toggle(&PORTB, DAC2);
// 				if (counter %4 == 0)		GPIO_toggle(&PORTB, DAC3);
// 				if (counter %64 == 0)		GPIO_toggle(&PORTB, DAC7);
// 				if (counter %16 == 0)		GPIO_toggle(&PORTB, DAC5);
// 				if (counter %32 == 0)		GPIO_toggle(&PORTB, DAC6);
// 				 if (counter %64 == 0)		GPIO_toggle(&PORTB, DAC7);
// 			 }
// 			 if (counter == 127) counter=1;
// 		 }
// 		
// 	
// }


	
}
