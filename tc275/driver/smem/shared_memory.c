#include <shared_memory.h>

volatile uint8 s_ledFlag __attribute__((section(".shared"))) = 0;

volatile uint8 s_pcTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD] __attribute__((section(".shared")));

volatile uint8 s_arduinoTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD] __attribute__((section(".shared")));

volatile uint8 s_rpiTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD] __attribute__((section(".shared")));

volatile uint8 s_tofTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD] __attribute__((section(".shared")));


volatile RingBuffer s_arduinoRxRingBuffer __attribute__((section(".shared")));
volatile RingBuffer s_rpiRxRingBuffer __attribute__((section(".shared")));
volatile RingBuffer s_pcRxRingBuffer __attribute__((section(".shared")));
volatile RingBuffer s_tofRxRingBuffer __attribute__((section(".shared")));

volatile uint8 s_targetSpeedL_integer __attribute__((section(".shared")));
volatile uint8 s_targetSpeedL_decimal __attribute__((section(".shared")));
volatile uint8 s_targetSpeedR_integer __attribute__((section(".shared")));
volatile uint8 s_targetSpeedR_decimal __attribute__((section(".shared")));

volatile char   s_followAngle __attribute__((section(".shared")));

volatile uint16 s_distance    __attribute__((section(".shared")));

volatile uint8 s_speedL_integer        __attribute__((section(".shared")));
volatile uint8 s_speedL_decimal        __attribute__((section(".shared")));
volatile uint8 s_speedR_integer        __attribute__((section(".shared")));
volatile uint8 s_speedR_decimal        __attribute__((section(".shared")));
volatile char  s_slope         __attribute__((section(".shared")));
volatile uint8 s_targetSpeed   __attribute__((section(".shared")));
volatile char  s_steeringAngle __attribute__((section(".shared")));


