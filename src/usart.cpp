#include "../include/usart.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

// VARIABLES FOR USART
volatile char usart_buffer[USART_BUFFER_SIZE];
volatile uint8_t usart_index = 0;
volatile uint8_t usart_message_ready = 0;

void USART_Init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // Clean buffert of scrap-values
    memset((void*)usart_buffer, 0, USART_BUFFER_SIZE);
    USART_SendString("USART initialized\r\n");
}

/*Send data to terminal.*/
void USART_Transmit(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

/*Sends string to terminal. char* str*/
void USART_SendString(const char *str)
{
    while (*str)
    {
        USART_Transmit(*str++);
    }
}

/*Reads input from terminal using ISR*/
ISR(USART_RX_vect)
{
    char received_char = UDR0;

    if (received_char == '\n' || received_char == '\r')
    {
        usart_buffer[usart_index] = '\0';
        usart_message_ready = 1;
        usart_index = 0;
        USART_Transmit('\r');
        USART_Transmit('\n');
    }
    else if (usart_index < USART_BUFFER_SIZE - 1)
    {
        usart_buffer[usart_index++] = received_char;
        USART_Transmit(received_char);
    }
}