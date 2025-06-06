#ifndef DRIVER_RINGBUFFER_RING_BUFFER_H_
#define DRIVER_RINGBUFFER_RING_BUFFER_H_

#include "Ifx_Types.h"

#define RINGBUFFER_SIZE 256

typedef struct _RingBuffer {
    uint8 buffer[RINGBUFFER_SIZE];
    volatile uint16 head;
    volatile uint16 tail;
} RingBuffer;

void RingBufferInit(volatile RingBuffer* rb);
int RingBufferPut(volatile RingBuffer* rb, uint8 data);
int RingBufferGet(volatile RingBuffer* rb, uint8* data);


#endif /* DRIVER_RINGBUFFER_RING_BUFFER_H_ */
