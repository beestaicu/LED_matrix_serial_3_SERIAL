/*
 * LED_matrix_serial_3_SERIAL.c
 *
 * Created: 28/05/2020 13:11:07
 * Author : bee
 */ 


#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "USART_M328P.h"
#include <string.h>
#define delay _delay_ms(1);

char buffer[8];
uint8_t RX_flag = 0;
uint8_t index1 = 0;
char col[] = {0xFE,0xFD,0xFB,0xf7,0xEF};
char raw[] = {0x0,0x0,0x0,0x0,0x0};

ISR(USART_RX_vect){
	buffer[index1] = UDR0; // Read USART data register
	index1++;
	if (index1 ==5){
		strncpy(raw, buffer,5); //copy buffer
		index1 =0;
		} 
}// end ISR USART

int main(void)
{
	DDRB = 0x3F;
	DDRC = 0xFF;
	USART0Init();
	sei();
	   
    while (1) 
    {
	for (int i=0;i<6;i++){
		PORTC=col[i];
		PORTB=buffer[i];
		delay;
		PORTB=0x00;
		PORTC=0xFF;
		}
	}
}

