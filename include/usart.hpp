#ifndef MY_USART_HPP
#define MY_USART_HPP

#define F_CPU 16000000UL
#define USART_BAUD 115200
#define MYUBRR F_CPU/16/USART_BAUD-1

#define USART_BUFFER_SIZE 50

#include <stdint.h>

extern volatile char usart_buffer[USART_BUFFER_SIZE]; 
extern volatile uint8_t usart_message_ready;

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
void USART_SendString(const char *str);

#endif