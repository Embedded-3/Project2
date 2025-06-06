/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
#include "parser.h"
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/


void ParserInit(ParserContext* ctx) {
    ctx->state = WAIT_START;
    ctx->index = 0;
}

int validateMessage(const uint8* data, uint8 len) {
    if (data[0] != 0xAA) return 0;         // Start byte 확인
    if (data[len-1] != 0x55) return 0;     // End byte 확인
    uint8 crc = calculateCRC(data, len);
    if (crc != data[len-2]) return 0;      // CRC 확인
    return 1;
}


uint8 calculateCRC(const uint8* data, uint8 len) {
    // data[0] = start, data[len-1] = end, data[len-2] = crc 위치
    uint16 sum = 0;
    for (uint8 i = 1; i < len - 2; i++) {
        sum += data[i];
    }
    return (uint8)(256 - (sum & 0xFF));
}


void ProcessReceivedMessage(uint8* msg, int len, int sourceDevice)
{
    switch(sourceDevice) {
        case ARDUINO:
            s_targetSpeedL_integer = msg[1];
            s_targetSpeedL_decimal = msg[2];
            s_targetLeftPWM = ((uint16)msg[1] << 8) | ((uint16)msg[2]);
            s_targetSpeedR_integer = msg[3];
            s_targetSpeedR_decimal = msg[4];
            s_targetRightPWM = ((uint16)msg[3] << 8) | ((uint16)msg[4]);
            //tx_uart_pc_debug("ARDUINO → targetSpeedL=%u.%u, targetSpeedR=%u.%u\r\n", s_targetSpeedL_integer, s_targetSpeedL_decimal, s_targetSpeedR_integer, s_targetSpeedR_decimal);
            tx_uart_pc_debug("ARDUINO -> targetLeftPWM = %d, targetRightPWM = %d\r\n", (sint16)s_targetLeftPWM, (sint16)s_targetRightPWM);
            break;

        case RPI:
            s_steeringAngle = (char)msg[1];  // signed 처리
            tx_uart_pc_debug("RPI → steeringAngle=%d\r\n", s_steeringAngle);
            break;

        case TOF:
            s_distance       = ((uint16)msg[6] << 8) | msg[5];
            tx_uart_pc_debug("TOF → dist=%u\r\n", s_distance);
            break;

        default:
            tx_uart_pc_debug("Unknown source device: %d\r\n", sourceDevice);
            break;
    }
}

// for debug
void rx_uart_debug(int ch)
{
    uint8 byte;
    volatile RingBuffer *rb = NULL;

    switch (ch)
    {
        case ARDUINO:
            rb = &s_arduinoRxRingBuffer;
            break;
        case RPI:
            rb = &s_rpiRxRingBuffer;
            break;
        case PC:
            rb = &s_pcRxRingBuffer;
            break;
        case TOF:
            rb = &s_tofRxRingBuffer;
            break;
        default:
            return;
    }

    if (rb == NULL)
        return;

    uint8 start_flag = 0;
    while (RingBufferGet(rb, &byte)) {
        if (byte == 0xAA)
        {
            start_flag = 1;
            continue;
        }
        if (byte == 0x55)
        {
            break;
        }

        if (start_flag)
        {
            tx_uart_debug(PC, "0x%02x\r\n", byte);
        }
    }
}

extern ParserContext arduinoParser, rpiParser, tofParser;

void rx_uart(int ch) {
    volatile RingBuffer* rb = NULL;
    ParserContext* ctx = NULL;

    switch (ch) {
        case ARDUINO: rb = &s_arduinoRxRingBuffer; ctx = &arduinoParser; break;
        case RPI:     rb = &s_rpiRxRingBuffer;     ctx = &rpiParser;     break;
        case TOF:     rb = &s_tofRxRingBuffer;     ctx = &tofParser;     break;
        default: return;
    }

    if (ch == TOF)
    {
        rx_uart_tof();
        return;
    }

    uint8 byte;
    while (RingBufferGet(rb, &byte)) {
        switch (ctx->state) {
            case WAIT_START:
                if (byte == 0xAA) {
                    ctx->index = 0;
                    ctx->buffer[ctx->index++] = byte;
                    ctx->state = RECEIVE_DATA;
                }
                break;

            case RECEIVE_DATA:
                if (ctx->index < sizeof(ctx->buffer)) {
                    ctx->buffer[ctx->index++] = byte;

                    if (byte == 0x55) {
                        // end 도달 → 파싱 시도
                        if (validateMessage(ctx->buffer, ctx->index)) {
                            ProcessReceivedMessage(ctx->buffer, ctx->index, ch);
                        } else {
                            tx_uart_pc_debug("Invalid message (ch=%d)\r\n", ch);
                        }

                        ctx->state = WAIT_START;
                        ctx->index = 0;
                        return; // 다 받았다고 가정
                    }
                } else {
                    // overflow → 리셋
                    ctx->state = WAIT_START;
                    ctx->index = 0;
                }
                break;
        }
    }
}

#define TOF_FRAME_SIZE      16
#define TOF_HEADER_0        0x57
#define TOF_HEADER_1        0x00
#define TOF_HEADER_2        0xFF
#define TOF_HEADER_3        0x00
#define TOF_INVALID_DIST_MM 0xFFFFF6

void rx_uart_tof(void)
{
    volatile RingBuffer* rb = &s_tofRxRingBuffer;
    ParserContext* ctx = &tofParser;
    uint8 byte;
    static uint16 prev_distance = 0;

    while (RingBufferGet(rb, &byte)) {
        switch (ctx->state) {
            case WAIT_START:
                if (byte == TOF_HEADER_0) {
                    ctx->index = 0;
                    ctx->buffer[ctx->index++] = byte;
                    ctx->state = RECEIVE_DATA;
                }
                break;

            case RECEIVE_DATA:
                ctx->buffer[ctx->index++] = byte;

                // 프레임 길이 도달 시 파싱 시도
                if (ctx->index == TOF_FRAME_SIZE) {
                    // 헤더 확인
                    if (ctx->buffer[0] == TOF_HEADER_0 &&
                        ctx->buffer[1] == TOF_HEADER_1 &&
                        ctx->buffer[2] == TOF_HEADER_2 &&
                        ctx->buffer[3] == TOF_HEADER_3)
                    {
                        unsigned int dist_mm = ((unsigned int)ctx->buffer[8]) |
                                               ((unsigned int)ctx->buffer[9] << 8) |
                                               ((unsigned int)ctx->buffer[10] << 16);

                        unsigned char status = ctx->buffer[11];

                        if (status == 0 && dist_mm != 0 && dist_mm != TOF_INVALID_DIST_MM) {
                            s_distance = dist_mm / 10; // mm → cm
                            //tx_uart_pc_debug("TOF → Valid dist: %u cm\r\n", s_distance);
                            prev_distance = s_distance;
                        } else {
                            s_distance = prev_distance;
                            //tx_uart_pc_debug("TOF → Invalid dist: %u cm\r\n", s_distance);
                        }
                    } else {
                        tx_uart_pc_debug("TOF → Header mismatch: %02X %02X %02X %02X\r\n",
                                         ctx->buffer[0], ctx->buffer[1], ctx->buffer[2], ctx->buffer[3]);
                    }

                    // reset FSM
                    ctx->state = WAIT_START;
                    ctx->index = 0;
                    return;
                }

                // overflow 보호
                if (ctx->index >= sizeof(ctx->buffer)) {
                    ctx->state = WAIT_START;
                    ctx->index = 0;
                }
                break;
        }
    }
}

void tx_uart(int ch)
{
    if (ch < 0 || ch > 3 || g_uartInstances[ch] == NULL)
        return;

    const uint8 *sharedBuf = NULL;
    Ifx_SizeT len = 0;
    char localBuf[LOCAL_TX_BUFFER_SIZE] = {0};

    switch (ch)
    {
        case ARDUINO:
            sharedBuf = (const uint8 *)s_arduinoTxBuf;
            len = (Ifx_SizeT)strlen((const char *)s_arduinoTxBuf);
            break;
        case RPI:
            sharedBuf = (const uint8 *)s_rpiTxBuf;
            len = (Ifx_SizeT)strlen((const char *)s_rpiTxBuf);
            break;
        case PC:
            sharedBuf = (const uint8 *)s_pcTxBuf;
            len = (Ifx_SizeT)strlen((const char *)s_pcTxBuf);
            break;
        case TOF:
            sharedBuf = (const uint8 *)s_tofTxBuf;
            len = (Ifx_SizeT)strlen((const char *)s_tofTxBuf);
            break;
        default:
            return;
    }

    if (sharedBuf != NULL && len > 0 && len < LOCAL_TX_BUFFER_SIZE)
    {
        memcpy(localBuf, sharedBuf, len);
        localBuf[len] = '\0'; // 안전한 문자열 종료

        // // debug 1
        // tx_uart_pc_debug("Copied data: %s, len : %d \r\n", localBuf, (int)len);

        // // debug 2
        // tx_uart_pc_debug("tx_uart[%d] sending: %s\r\n", ch, localBuf);

        IfxAsclin_Asc_write(g_uartInstances[ch], (const void *)localBuf, &len, TIMEOUT);

        //tx_uart_pc_debug("TX DONE\r\n");

        // shared buffer 비우기 (동기화 플래그가 있으면 여기서 처리)
        ((uint8 *)sharedBuf)[0] = '\0';

        // 간단한 딜레이 (필요시 조절)
        for (volatile int i = 0; i < 100000; i++);
    }
    //tx_uart_pc_debug("TX DONE\r\n");
}

// for debug
void tx_uart_pc_debug(const char *format, ...)
{
    char debugBuf[UART_BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(debugBuf, sizeof(debugBuf), format, args);
    va_end(args);
    Ifx_SizeT len = (Ifx_SizeT)strlen(debugBuf);
    //debugBuf[len] = 0;
    IfxAsclin_Asc_write(g_uartInstances[PC], (const void *)debugBuf, &len, TIMEOUT);
    for (volatile int i = 0; i < 100000; i++);
}

// for debug
void tx_uart_debug(int ch, const char *format, ...)
{
    char debugBuf[UART_BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(debugBuf, sizeof(debugBuf), format, args);
    va_end(args);
    Ifx_SizeT len = (Ifx_SizeT)strlen(debugBuf);
    //debugBuf[len] = 0;
    IfxAsclin_Asc_write(g_uartInstances[ch], (const void *)debugBuf, &len, TIMEOUT);
    for (volatile int i = 0; i < 100000; i++);
}

void PrepareArduinoMessageAndSend(uint8 speedL_integer, uint8 speedL_decimal, uint8 speedR_integer, uint8 speedR_decimal,
                                    uint8 slope, uint8 targetSpeed, uint8 steeringAngle)
{
    uint8 idx = 0;
    s_arduinoTxBuf[idx++] = 0xAA;
    s_arduinoTxBuf[idx++] = speedL_integer;
    s_arduinoTxBuf[idx++] = speedL_decimal;
    s_arduinoTxBuf[idx++] = speedR_integer;
    s_arduinoTxBuf[idx++] = speedR_decimal;
    s_arduinoTxBuf[idx++] = (uint8)slope;         // signed char to byte
    s_arduinoTxBuf[idx++] = targetSpeed;
    if(steeringAngle == 0) steeringAngle = 1; // steeringAngle이 0이면 1로 설정
    s_arduinoTxBuf[idx++] = (uint8)steeringAngle;

    // CRC 계산: start 제외, end 제외
    uint16 sum = 0;
    for (uint8 i = 1; i < idx; i++) sum += s_arduinoTxBuf[i];
    s_arduinoTxBuf[idx++] = (uint8)(256 - (sum & 0xFF)); // CRC

    s_arduinoTxBuf[idx++] = 0x55; // End

    // 버퍼는 전역 8바이트 내에서 작성됨
    // 전송 호출
    tx_uart(ARDUINO);
}


/*********************************************************************************************************************/
