#define S_FUNCTION_NAME  sfun_uart
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define UART_RX_BUFFER_SIZE 64
volatile char uart_rx_buffer[UART_RX_BUFFER_SIZE];
volatile uint8_t uart_rx_head = 0;
volatile uint8_t uart_rx_tail = 0;

void uart_init(void) {
    uint16_t ubrr = 103; // 9600bps 16MHz
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    UCSR0B = (1 << RXEN0) | (1 << RXCIE0);  // 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8bit data
    sei();
}

ISR(USART_RX_vect) {
    char c = UDR0;
    uint8_t next = (uart_rx_head + 1) % UART_RX_BUFFER_SIZE;
    if (next != uart_rx_tail) {
        uart_rx_buffer[uart_rx_head] = c;
        uart_rx_head = next;
    }
}

int uart_available(void) {
    return (UART_RX_BUFFER_SIZE + uart_rx_head - uart_rx_tail) % UART_RX_BUFFER_SIZE;
}

char uart_read(void) {
    if (uart_rx_head == uart_rx_tail) return -1;
    char c = uart_rx_buffer[uart_rx_tail];
    uart_rx_tail = (uart_rx_tail + 1) % UART_RX_BUFFER_SIZE;
    return c;
}


static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumOutputPorts(S, 1);
    ssSetOutputPortWidth(S, 0, 8);              
    ssSetOutputPortDataType(S, 0, SS_UINT8);
    ssSetNumSampleTimes(S, 1);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, 0.01);  // 10ms
    ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_START
static void mdlStart(SimStruct *S)
{
    uart_init(); 
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    uint8_T *y = (uint8_T *)ssGetOutputPortSignal(S, 0);
    static uint8_T frame[10];
    static uint8_T frame_idx = 0;

    for (int i = 0; i < 8; i++) y[i] = 0;

    while (uart_available() > 0) {
        uint8_T byte = (uint8_T)uart_read();

        if (frame_idx == 0 && byte != 0xAA) {
            continue;
        }

        frame[frame_idx++] = byte;

        if (frame_idx == 10) {
            if (frame[0] == 0xAA && frame[9] == 0x55) {
 
                for (int i = 0; i < 8; i++) {
                    y[i] = frame[i + 1];
                }
            }
            frame_idx = 0;
        }
    }
}

static void mdlTerminate(SimStruct *S) {}

#include "simulink.c"
