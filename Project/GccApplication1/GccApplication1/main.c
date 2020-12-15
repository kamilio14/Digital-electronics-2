
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

uint8_t sine[255]= {128,131,134,137,140,143,146,149,152,156,159,162,165,168,171,174,
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

uint8_t triangle[256] ={2,4,6,8,10,12,14,16,18,20,21,23,25,27,29,31,
	33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,
	64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,
	96,98,100,102,104,105,107,109,111,113,115,117,119,121,123,125,
	127,129,131,133,135,137,139,141,143,145,146,148,150,152,154,156,
	158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,
	189,191,193,195,197,199,201,203,205,207,209,211,213,215,217,219,
	221,223,225,227,229,230,232,234,236,238,240,242,244,246,248,250,
	248,246,244,242,240,238,236,234,232,230,229,227,225,223,221,219,
	217,215,213,211,209,207,205,203,201,199,197,195,193,191,189,188,
	186,184,182,180,178,176,174,172,170,168,166,164,162,160,158,156,
	154,152,150,148,146,145,143,141,139,137,135,133,131,129,127,125,
	123,121,119,117,115,113,111,109,107,105,104,102,100,98,96,94,
	92,90,88,86,84,82,80,78,76,74,72,70,68,66,64,63,
	61,59,57,55,53,51,49,47,45,43,41,39,37,35,33,31,
29,27,25,23,21,20,18,16,14,12,10,8,6,4,2,0,};

uint8_t decay[256] ={0,4,8,11,15,19,22,26,29,33,36,39,43,46,49,52,
	55,58,61,64,67,70,73,75,78,81,83,86,89,91,94,96,
	98,101,103,105,108,110,112,114,116,118,120,122,124,126,128,130,
	132,134,136,137,139,141,142,144,146,147,149,151,152,154,155,157,
	158,159,161,162,164,165,166,168,169,170,171,173,174,175,176,177,
	178,179,181,182,183,184,185,186,187,188,189,190,191,192,192,193,
	194,195,196,197,198,198,199,200,201,202,202,203,204,204,205,206,
	207,207,208,209,209,210,210,211,212,212,213,213,214,215,215,216,
	216,217,217,218,218,219,219,220,220,221,221,222,222,222,223,223,
	224,224,224,225,225,226,226,226,227,227,227,228,228,228,229,229,
	229,230,230,230,231,231,231,232,232,232,232,233,233,233,234,234,
	234,234,235,235,235,235,235,236,236,236,236,237,237,237,237,237,
	238,238,238,238,238,238,239,239,239,239,239,240,240,240,240,240,
	240,240,241,241,241,241,241,241,241,242,242,242,242,242,242,242,
	242,243,243,243,243,243,243,243,243,243,244,244,244,244,244,244,
244,244,244,244,244,245,245,245,245,245,245,245,245,245,245,245,};

uint8_t sinn[20] ={120,157,191,217,234,240,234,217,
	191,157,120,83,49,23,6,0,
6,23,49,83,120,};
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
			if(binaryNum[j]==1) GPIO_write_high(&PORTB, DAC0);
			else GPIO_write_low(&PORTB, DAC0);
			break;
			case 1:
			if(binaryNum[j]==1) GPIO_write_high(&PORTB, DAC1);
			else GPIO_write_low(&PORTB, DAC1);
			break;
			case 2:
			if(binaryNum[j]==1) GPIO_write_high(&PORTB, DAC2);
			else GPIO_write_low(&PORTB, DAC2);
			break;
			case 3:
			if(binaryNum[j]==1) GPIO_write_high(&PORTB, DAC3);
			else GPIO_write_low(&PORTB, DAC3);
			break;
			case 4:
			if(binaryNum[j]==1) GPIO_write_high(&PORTB, DAC4);
			else GPIO_write_low(&PORTB, DAC4);
			break;
			case 5:
			if(binaryNum[j]==1) GPIO_write_high(&PORTB, DAC5);
			else GPIO_write_low(&PORTB, DAC5);
			break;
			case 6:
			if(binaryNum[j]==1) GPIO_write_high(&PORTB, DAC6);
			else GPIO_write_low(&PORTB, DAC6);
			break;
			case 7:
			if(binaryNum[j]==1) GPIO_write_high(&PORTB, DAC7);
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

    // Initialize LCD display
    lcd_init(LCD_DISP_ON);

    // Write to LCD display
    lcd_gotoxy(0, 0);
    lcd_puts("OUTPUT SIGNAL");

    // Configuration of 8-bit Timer/Counter0 for signal generator
    // Overflow interrupt every 128 us
    TIM0_overflow_1ms();
    TIM0_overflow_interrupt_enable();
	
    // Configuration of 16-bit Timer/Counter1 for signal generator
    // Overflow interrupt every 262 us
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();
	
    // Initialization of UART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600,F_CPU));
	
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

// Interrupts from Timer/Counter0 can generate 6 various signals
ISR(TIMER0_OVF_vect)
{
	// Sine
	if (keypad == 1)
	{
		converter(sine[counter]);
		counter++;
		if (counter > 255) counter = 0;
	}
	
	// Triangle
	if (keypad ==2)
	{
		converter(triangle[counter]);
		counter++;
		if (counter > 255) counter = 0;
	}
	
	// Exponential wave
	if (keypad == 3)
	{
		converter(decay[counter]);
		counter++;
		if (counter > 255) counter = 0;
	}
	
	// Square
	if (keypad == 4)
	{
		if (counter == 0)
		{
			GPIO_write_low(&PORTB, DAC0);
			GPIO_write_low(&PORTB, DAC1);
			GPIO_write_low(&PORTB, DAC2);
			GPIO_write_low(&PORTB, DAC3);
			GPIO_write_high(&PORTB, DAC4);
			GPIO_write_high(&PORTB, DAC5);
			GPIO_write_high(&PORTB, DAC6);
			GPIO_write_high(&PORTB, DAC7);
		}
		counter++;
		if (counter == 128)
		{
			GPIO_write_low(&PORTB, DAC0);
			GPIO_write_low(&PORTB, DAC1);
			GPIO_write_low(&PORTB, DAC2);
			GPIO_write_low(&PORTB, DAC3);
			GPIO_write_low(&PORTB, DAC4);
			GPIO_write_low(&PORTB, DAC5);
			GPIO_write_low(&PORTB, DAC6);
			GPIO_write_low(&PORTB, DAC7);
		}
		if (counter == 255) counter = 0;
		
	}
	// Dirac
	if (keypad == 5)
	{
		if (counter == 255)
		{
			counter = 0;
		}
		if (counter == 50)
		{
			GPIO_write_low(&PORTB, DAC0);
			GPIO_write_low(&PORTB, DAC1);
			GPIO_write_low(&PORTB, DAC2);
			GPIO_write_low(&PORTB, DAC3);
			GPIO_write_high(&PORTB, DAC4);
			GPIO_write_high(&PORTB, DAC5);
			GPIO_write_high(&PORTB, DAC6);
			GPIO_write_high(&PORTB, DAC7);
		}
		if (counter == 55)
		{
			GPIO_write_low(&PORTB, DAC0);
			GPIO_write_low(&PORTB, DAC1);
			GPIO_write_low(&PORTB, DAC2);
			GPIO_write_low(&PORTB, DAC3);
			GPIO_write_low(&PORTB, DAC4);
			GPIO_write_low(&PORTB, DAC5);
			GPIO_write_low(&PORTB, DAC6);
			GPIO_write_low(&PORTB, DAC7);
		}
		counter++;
	}
	
	// Noise
	if (keypad == 6)
	{
		converter(sinn[counter]);
		counter++;
		if (counter > 20) counter = 0;
	}
}

// Interrupts from Timer/Counter1 are keypad drivers
ISR(TIMER1_OVF_vect)
{
    // Keypad first row
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
		
    // Keypad second row
    GPIO_write_low(&PORTC, KEYPAD3);
    GPIO_write_high(&PORTC, KEYPAD4);
    GPIO_write_low(&PORTC, KEYPAD5);
    GPIO_write_low(&PORTC, KEYPAD6);
    if (GPIO_read(&PINC, KEYPAD0) == 1)
    {keypad = 4; counter=0;}
    if (GPIO_read(&PINC, KEYPAD1) == 1)
    {keypad = 5; counter=0;}
    if (GPIO_read(&PINC, KEYPAD2) == 1)
    {keypad = 6; counter=0;}
		
    // Keypad third row
    GPIO_write_low(&PORTC, KEYPAD3);
    GPIO_write_low(&PORTC, KEYPAD4);
    GPIO_write_high(&PORTC, KEYPAD5);
    GPIO_write_low(&PORTC, KEYPAD6);
    if (GPIO_read(&PINC, KEYPAD0) == 1)
    {keypad = 7; counter=0;}
    if (GPIO_read(&PINC, KEYPAD1) == 1)
    {keypad = 8; counter=0;}
    if (GPIO_read(&PINC, KEYPAD2) == 1)
    {keypad = 9; counter=0;}
		
	// Keypad third fourth
	GPIO_write_low(&PORTC, KEYPAD3);
	GPIO_write_low(&PORTC, KEYPAD4);
	GPIO_write_low(&PORTC, KEYPAD5);
	GPIO_write_high(&PORTC, KEYPAD6);
	if (GPIO_read(&PINC, KEYPAD0) == 1)
	{keypad = 10; counter=0;}
	if (GPIO_read(&PINC, KEYPAD1) == 1)
	{keypad = 11; counter=0;}
	if (GPIO_read(&PINC, KEYPAD2) == 1)
	{keypad = 12; counter=0;}	

    // Displaying information text by LCD and UART
	
	if (keypad == 0)
	{
		lcd_gotoxy(0, 1);
		lcd_puts("						");
		uart_puts("None input data... \r\n");
	}
	
	if (keypad == 1)                                                                                        // keypad value = 1, sine wave generation
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("SINE WAVE");
		uart_puts("DTMF low f = 697Hz and high f = 1209Hz. \r\n");
	}
	if (keypad == 2)                                                                                        // keypad value = 2, square wave generation
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("TRIANGLE WAVE");
		uart_puts("DTMF low f = 697Hz and high f = 1336Hz. \r\n");
	}
	if (keypad == 3)                                                                                        // keypad value = 3, rising sawtooth wave generation
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("EXPONENTIAL WAVE");
		uart_puts("DTMF low f = 697Hz and high f = 1477Hz. \r\n");
	}
	if (keypad == 4)                                                                                        // keypad value = 4, falling sawtooth wave generation
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("SQUARE WAVE");
		uart_puts("DTMF low f = 770Hz and high f = 1209Hz. \r\n");
	}
	if (keypad == 5)                                                                                        // keypad value = 5, triangle wave generation
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("DIRAC PULSES");
		uart_puts("DTMF low f = 770Hz and high f = 1336Hz. \r\n");
	}
	if (keypad == 6)                                                                                        // keypad value = 6, dirac pulses generation
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("NOISE SINUS WAVE");
		uart_puts("DTMF low f = 770Hz and high f = 1477Hz. \r\n");
	}
	
	if (keypad == 7)
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("RESET");
		uart_puts("DTMF low f = 852Hz and high f = 1209Hz. \r\n");
	}
	
	if (keypad == 8)
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("RESET");
		uart_puts("DTMF low f = 852Hz and high f = 1336Hz. \r\n");
	}
	
	if (keypad == 9)
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("RESET");
		uart_puts("DTMF low f = 852Hz and high f = 1477Hz. \r\n");
	}
	
	if (keypad == 10)
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("RESET");
		uart_puts("DTMF low f = 941Hz and high f = 1209Hz. \r\n");
	}
	
	if (keypad == 11)
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("RESET");
		uart_puts("DTMF low f = 941Hz and high f = 1336Hz. \r\n");
	}
	
	if (keypad == 12)
	{
		lcd_gotoxy(0, 1);
		lcd_puts("																");
		lcd_gotoxy(0, 1);
		lcd_puts("RESET");
		uart_puts("DTMF low f = 941Hz and high f = 1477Hz. \r\n");
	}
}
