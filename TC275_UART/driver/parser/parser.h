#ifndef DRIVER_PARSER_PARSER_H_
#define DRIVER_PARSER_PARSER_H_

#include "Ifx_Types.h"
#include "uart.h"
#include "shared_memory.h"
#include "ring_buffer.h"
#include "stdarg.h"
#define MSG_MAX_LENGTH 256
#define LOCAL_TX_BUFFER_SIZE (UART_BUFFER_SIZE + 16) // 충분히 큰 크기
// parser

typedef enum {
    WAIT_START,
    RECEIVE_DATA
} ParserState;

typedef struct {
    ParserState state;
    uint8 buffer[MSG_MAX_LENGTH];
    uint8 index;
} ParserContext;

// 1) TC275 → ARDUINO 메시지 구조체
typedef struct {
    uint8  start;            // 0xAA
    uint8 speedL;           // 좌측 속도
    uint8 speedR;           // 우측 속도
    char  slope;            // 경사각 (signed)
    uint8  targetSpeed;      // 목표 속도
    char   steeringAngle;    // 조향각 (signed)
    uint8  crc;              // CRC: 256 - sum(필드)
    uint8  end;              // 0x55
} Tc275ToArduinoMsg_t;

// 2) ARDUINO → TC275 메시지 구조체
typedef struct {
    uint8  start;           // 0xAA
    uint8 targetSpeedL;
    uint8 targetSpeedR;
    uint8  crc;
    uint8  end;
} ArduinoToTc275Msg_t;

// 3) RASPBERRY PI → TC275 메시지 구조체
typedef struct {
    uint8 start;            // 0xAA
    char  followAngle;      // 추종점 각도 (signed)
    uint8 crc;              // CRC
    uint8 end;              // 0x55
} RpiToTc275Msg_t;

// 4) ToF sensor → TC275 메시지 구조체
typedef struct {
    uint8  frameHeader;       // 0x5A
    uint8  functionMark;      // 메시지 종류 (예: 0x01)
    uint32 nodeTimestamp;     // 타임스탬프 (uint32_t, 리틀엔디안)
    uint16 distance;          // 거리 (mm)
    uint8  distanceStatus;    // 거리 상태 코드
    uint16 signalStrength;    // 신호 세기
    uint8  sumCheck;          // 체크섬: 바이트 합(헤더~데이터) 하위 1바이트
} ToFSensorToTc275Msg_t;


uint8 calculateCRC(const uint8* data, uint8 len);
uint8 calculateToFSumCheck(const uint8* data, uint8 len);
int validateMessage(const uint8* data, uint8 len);
int validateToFMessage(const uint8* data, uint8 len);
void ProcessReceivedMessage(uint8* msg, int len, int sourceDevice);

void ParserInit(ParserContext* ctx);
void ParseRingBuffer(RingBuffer* rb, ParserContext* ctx);
uint8 calculateCRC(const uint8* data, uint8 len);
uint8 calculateToFSumCheck(const uint8* data, uint8 len);
void PrepareArduinoMessageAndSend(uint8 speedL, uint8 speedR, char slope,
                                  uint8 targetSpeed, char steeringAngle);

void tx_uart(int ch);
void tx_uart_pc_debug(const char *format, ...);
void tx_uart_debug(int ch, const char *format, ...);
void rx_uart_debug(int ch);
void rx_uart(int ch);
#endif /* DRIVER_PARSER_PARSER_H_ */
