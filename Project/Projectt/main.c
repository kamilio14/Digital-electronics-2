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
static uint16_t counter = 0; // overflow counter value set to 0
static uint8_t keypad = 0;  // keypad value set to 0

int sine[256]= {128,131,134,137,140,143,146,149,152,156,159,162,165,168,171,174,
	176,179,182,185,188,191,193,196,199,201,204,206,209,211,213,216,
	218,220,222,224,226,228,230,232,234,235,237,239,240,242,243,244,
	246,247,248,249,250,251,251,252,253,253,254,254,254,255,255,255,
	255,255,255,255,254,254,253,253,252,252,251,250,249,248,247,246,
	245,244,242,241,239,238,236,235,233,231,229,227,225,223,221,219,
	217,215,212,210,207,205,202,200,197,195,192,189,186,184,181,178,
	175,172,169,166,163,160,157,154,151,148,145,142,138,135,132,129,
	126,123,120,117,113,110,107,104,101,98,95,92,89,86,83,80,
	77,74,71,69,66,63,60,58,55,53,50,48,45,43,40,38,
	36,34,32,30,28,26,24,22,20,19,17,16,14,13,11,10,
	9,8,7,6,5,4,3,3,2,2,1,1,0,0,0,0,
	0,0,0,1,1,1,2,2,3,4,4,5,6,7,8,9,
	11,12,13,15,16,18,20,21,23,25,27,29,31,33,35,37,
	39,42,44,46,49,51,54,56,59,62,64,67,70,73,76,79,
	81,84,87,90,93,96,99,103,106,109,112,115,118,121,124,128,};

//function headers
void converter(int n);

void converter(int n)
{
	// array to store binary number
	int binaryNum[8] = {0,0,0,0,0,0,0,0};
	
	// counter for binary array
	int i = 0;
	//if (n == 0) i = 8; //set converter bits to zeros
	
	while (n > 0)
	{
		// storing remainder in binary array
		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}
	// printing binary array in reverse order
	for (int j = 7; j >= 0; j--)
	{
		switch(j)
		{
			case 0:
				if(binaryNum[j]) GPIO_write_high(&PORTB, DAC0);
				else GPIO_write_low(&PORTB, DAC0);
				break;
			case 1:
				if(binaryNum[j]) GPIO_write_high(&PORTB, DAC1);
				else GPIO_write_low(&PORTB, DAC1);
				break;
			case 2:
				if(binaryNum[j]) GPIO_write_high(&PORTB, DAC2);
				else GPIO_write_low(&PORTB, DAC2);
				break;
			case 3:
				if(binaryNum[j]) GPIO_write_high(&PORTB, DAC3);
				else GPIO_write_low(&PORTB, DAC3);
				break;
			case 4:
				if(binaryNum[j]) GPIO_write_high(&PORTB, DAC4);
				else GPIO_write_low(&PORTB, DAC4);
				break;
			case 5:
				if(binaryNum[j]) GPIO_write_high(&PORTB, DAC5);
				else GPIO_write_low(&PORTB, DAC5);
				break;
			case 6:
				if(binaryNum[j]) GPIO_write_high(&PORTB, DAC6);
				else GPIO_write_low(&PORTB, DAC6);
				break;
			case 7:
				if(binaryNum[j]) GPIO_write_high(&PORTB, DAC7);
				else GPIO_write_low(&PORTB, DAC7);
				break;
			default:;
		}
	}
}

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
    TIM0_overflow_1ms();
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
		converter(sine[counter]);
		counter++;
	   if (counter > 256) counter = 0;
	}
}
