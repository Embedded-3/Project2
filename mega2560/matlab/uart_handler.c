#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_handler.h"

#define UART_BUFFER_SIZE 64

volatile char uart_buffer[UART_BUFFER_SIZE];
volatile uint8_t uart_head = 0;
volatile uint8_t uart_tail = 0;

void uart_init(void) {
    uint16_t ubrr = 103; // 9600 bps
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    UCSR0B = (1 << RXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8bit 
    sei(); 
}

ISR(USART_RX_vect) {
    char c = UDR0;
    uint8_t next = (uart_head + 1) % UART_BUFFER_SIZE;
    if (next != uart_tail) {
        uart_buffer[uart_head] = c;
        uart_head = next;
    }
}

int uart_available(void) {
    return (UART_BUFFER_SIZE + uart_head - uart_tail) % UART_BUFFER_SIZE;
}

char uart_read(void) {
    if (uart_head == uart_tail) return -1;
    char c = uart_buffer[uart_tail];
    uart_tail = (uart_tail + 1) % UART_BUFFER_SIZE;
    return c;
}