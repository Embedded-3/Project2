#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include "Ifx_Types.h"
#include "uart.h"

extern volatile uint8 s_ledFlag;

extern volatile uint8 s_pcTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD];

extern volatile uint8 s_arduinoTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD];

extern volatile uint8 s_rpiTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD];

extern volatile uint8 s_tofTxBuf[UART_BUFFER_SIZE + FIFO_OVERHEAD];

typedef struct {
    volatile uint8 buffer[UART_BUFFER_SIZE];
    volatile uint16 head;   // 다음에 쓸 위치
    volatile uint16 tail;   // 다음에 읽을 위치
} RingBuffer;

// 각 UART별 링버퍼 예시
extern volatile RingBuffer s_arduinoRxRingBuffer;
extern volatile RingBuffer s_rpiRxRingBuffer;
extern volatile RingBuffer s_pcRxRingBuffer;
extern volatile RingBuffer s_tofRxRingBuffer;

void RingBufferInit(void);
void RingBufferPut(RingBuffer *rb, uint8 data);
int RingBufferGet(RingBuffer *rb, uint8 *data);
void RingBufferClear(RingBuffer *rb);

#endif
