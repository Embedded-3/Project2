#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include "Ifx_Types.h"
#include "ring_buffer.h"
#include "uart.h"

#define UART_BUFFER_SIZE 256
#define FIFO_OVERHEAD    (sizeof(Ifx_Fifo) + 8)

extern volatile uint8 s_ledFlag;

extern volatile uint8 s_pcTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD];

extern volatile uint8 s_arduinoTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD];

extern volatile uint8 s_rpiTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD];

extern volatile uint8 s_tofTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD];

// 각 UART별 링버퍼 예시
extern volatile RingBuffer s_arduinoRxRingBuffer;
extern volatile RingBuffer s_rpiRxRingBuffer;
extern volatile RingBuffer s_pcRxRingBuffer;
extern volatile RingBuffer s_tofRxRingBuffer;

// 아두이노 받는 변수
extern volatile uint8 s_targetSpeedL_integer;
extern volatile uint8 s_targetSpeedL_decimal;
extern volatile uint8 s_targetSpeedR_integer;
extern volatile uint8 s_targetSpeedR_decimal;

// 라베파 받는 변수
extern volatile char   s_followAngle;

// tof 받는 변수
extern volatile uint16 s_distance;

// 아두이노 보낼 변수
extern volatile uint8 s_speedL_integer;
extern volatile uint8 s_speedL_decimal;
extern volatile uint8 s_speedR_integer;
extern volatile uint8 s_speedR_decimal;
extern volatile char  s_slope;
extern volatile uint8 s_targetSpeed;
extern volatile char  s_steeringAngle;
#endif
