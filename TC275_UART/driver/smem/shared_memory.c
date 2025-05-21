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


// 링 버퍼에 데이터 한 바이트 쓰기 (ISR에서 호출)
void RingBufferPut(RingBuffer *rb, uint8 data)
{
    uint16 nextHead = (rb->head + 1) % UART_BUFFER_SIZE;

    // 버퍼가 꽉 찼으면, 오래된 데이터 덮어쓰기 또는 무시 정책 선택 가능
    if (nextHead != rb->tail) {  // 여유 공간이 있을 때만 저장
        rb->buffer[rb->head] = data;
        rb->head = nextHead;
    } else {
        // overflow 시 처리 (무시하거나 tail 이동 가능)
        rb->tail = (rb->tail + 1) % UART_BUFFER_SIZE; // 덮어쓰기
    }
}

// 링 버퍼에서 데이터 한 바이트 읽기 (메인 루프에서 호출)
int RingBufferGet(RingBuffer *rb, uint8 *data)
{
    if (rb->head == rb->tail) {
        // 버퍼 비어 있음
        return 0;
    } else {
        *data = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % UART_BUFFER_SIZE;
        return 1;
    }
}

// 링 버퍼 비우기 (초기화 등)
void RingBufferClear(RingBuffer *rb)
{
    rb->head = 0;
    rb->tail = 0;
    memset((void*)rb->buffer, 0, UART_BUFFER_SIZE);
}

void RingBufferInit(void)
{
    RingBufferClear(&s_arduinoRxRingBuffer);
    RingBufferClear(&s_rpiRxRingBuffer);
    RingBufferClear(&s_pcRxRingBuffer);
    RingBufferClear(&s_tofRxRingBuffer);
}
