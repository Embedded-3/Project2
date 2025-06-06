/**********************************************************************************************************************
 * \file Cpu1_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxPort.h"
#include "IfxPort_PinMap.h"
#include "shared_memory.h"
#include "uart.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"
#include "IfxStm.h"
#include "parser.h"
#include "ring_buffer.h"
#include "safety.h"

extern IfxCpu_syncEvent g_cpuSyncEvent;

ParserContext arduinoParser, rpiParser, tofParser;



/* Arduino (ASCLIN0) */

IFX_INTERRUPT(arduinoTxISR, 1, ISR_PRIORITY_ARDUINO_TX);
void arduinoTxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_uart_arduino);
}

IFX_INTERRUPT(arduinoRxISR, 1, ISR_PRIORITY_ARDUINO_RX);
void arduinoRxISR(void)
{
    //tx_uart_pc_debug("Interrupt\r\n");
    uint8 receivedData[UART_BUFFER_SIZE];
    Ifx_SizeT length = UART_BUFFER_SIZE;
    boolean dataAvailable;

    // 먼저 ISR 내부 처리를 수행 (필수)
    IfxAsclin_Asc_isrReceive(&g_uart_arduino);

    // UART 수신 FIFO에서 최대 UART_BUFFER_SIZE 바이트 읽기 시도
    IfxAsclin_Asc_read(&g_uart_arduino, receivedData, &length, 0);  // Non-blocking read (timeout=0)

    // 읽은 데이터가 있으면 링버퍼에 넣기
    if (length > 0)
    {
        for (Ifx_SizeT i = 0; i < length; i++)
        {
            RingBufferPut(&s_arduinoRxRingBuffer, receivedData[i]);
        }
    }
}


IFX_INTERRUPT(arduinoErISR, 1, ISR_PRIORITY_ARDUINO_ER);
void arduinoErISR(void)
{
    IfxAsclin_Asc_isrError(&g_uart_arduino);
}

/* Raspberry Pi (ASCLIN1) */
IFX_INTERRUPT(rpiTxISR, 1, ISR_PRIORITY_RPI_TX);
void rpiTxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_uart_rpi);
}

IFX_INTERRUPT(rpiRxISR, 1, ISR_PRIORITY_RPI_RX);
void rpiRxISR(void)
{
    //tx_uart_pc_debug("Interrupt\r\n");
    uint8 receivedData[UART_BUFFER_SIZE];
    Ifx_SizeT length = UART_BUFFER_SIZE;
    boolean dataAvailable;

    // 먼저 ISR 내부 처리를 수행 (필수)
    IfxAsclin_Asc_isrReceive(&g_uart_rpi);

    // UART 수신 FIFO에서 최대 UART_BUFFER_SIZE 바이트 읽기 시도
    IfxAsclin_Asc_read(&g_uart_rpi, receivedData, &length, 0);  // Non-blocking read (timeout=0)

    // 읽은 데이터가 있으면 링버퍼에 넣기
    if (length > 0)
    {
        for (Ifx_SizeT i = 0; i < length; i++)
        {
            RingBufferPut(&s_rpiRxRingBuffer, receivedData[i]);
        }
    }
}

IFX_INTERRUPT(rpiErISR, 1, ISR_PRIORITY_RPI_ER);
void rpiErISR(void)
{
    IfxAsclin_Asc_isrError(&g_uart_rpi);
}

/* PC Serial Console (ASCLIN3) */
IFX_INTERRUPT(pcTxISR, 1, ISR_PRIORITY_PC_TX);
void pcTxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_uart_pc);
}

IFX_INTERRUPT(pcRxISR, 1, ISR_PRIORITY_PC_RX);
void pcRxISR(void)
{
    IfxAsclin_Asc_isrReceive(&g_uart_pc);
}

IFX_INTERRUPT(pcErISR, 1, ISR_PRIORITY_PC_ER);
void pcErISR(void)
{
    IfxAsclin_Asc_isrError(&g_uart_pc);
}


IFX_INTERRUPT(tofTxISR, 1, ISR_PRIORITY_TOF_TX);
void tof2TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_uart_tof);
}

IFX_INTERRUPT(tofRxISR, 1, ISR_PRIORITY_TOF_RX);
void tofRxISR(void)
{
    uint8 receivedData[UART_BUFFER_SIZE];
    Ifx_SizeT length = UART_BUFFER_SIZE;

    // 인터럽트 ACK
    IfxAsclin_Asc_isrReceive(&g_uart_tof);  // g_uart_tof는 TOF 채널의 IfxAsclin_Asc 인스턴스

    // FIFO에서 읽기 (timeout = 0 → 논블로킹)
    IfxAsclin_Asc_read(&g_uart_tof, receivedData, &length, 0);

    // 읽은 데이터를 RingBuffer로 복사
    if (length > 0)
    {
        for (Ifx_SizeT i = 0; i < length; i++)
        {
            RingBufferPut(&s_tofRxRingBuffer, receivedData[i]);
        }
    }
}


IFX_INTERRUPT(tofErISR, 1, ISR_PRIORITY_TOF_ER);
void tofErISR(void)
{
    IfxAsclin_Asc_isrError(&g_uart_tof);
}

void core1_main(void)
{
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG1 IS DISABLED HERE!!
     * Enable the watchdog and service it periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    
    initUART();
    RingBufferInit(&s_arduinoRxRingBuffer);
    RingBufferInit(&s_rpiRxRingBuffer);
    RingBufferInit(&s_tofRxRingBuffer);
    ParserInit(&arduinoParser);
    ParserInit(&rpiParser);
    ParserInit(&tofParser);

    tx_uart_pc_debug("hello TC275!\r\n");

    PrepareArduinoMessageAndSend(s_speedL_integer, s_speedL_decimal, s_speedR_integer, s_speedR_decimal, s_slope, s_targetSpeed, s_steeringAngle);  // TODO 자꾸떠서 주석해놨음
    
    
    
    while (1)
    {
        if(flag1 == 0){
            flag1 = 1;
        }
        else if(flag1 == 2){
            tx_uart_pc_debug("Core1 STOP\n\r");
            return;
        }

        /*
        // pc Transmit
        strcpy(s_pcTxBuf, "HELLO FROM PC!\r\n");
        //s_pcTxBuf[UART_BUFFER_SIZE - 1] = '\0';
        tx_uart_pc_debug("gogogo\r\n");
        tx_uart_pc_debug("sending shared : %s\r\n", s_pcTxBuf);
        tx_uart(PC);
        */

        // Arduino Transmit
        //strcpy(s_arduinoTxBuf, "HELLO FROM TC275!\r\n");
        //tx_uart_pc_debug("sending shared : %s\r\n", s_arduinoTxBuf);
        //tx_uart(ARDUINO);

        //tx_uart_pc_debug("RECEIVE STARTS\r\n");
        //tx_uart_debug(ARDUINO, "%c", 'a');
        /*
        tx_uart_debug(ARDUINO, "%c",0xaa);

        tx_uart_debug(ARDUINO, "%c%c", 0x03, 0x05);
        tx_uart_debug(ARDUINO, "%c%c", 0x03, 0x05);
        tx_uart_debug(ARDUINO, "%c", 0x06);
        tx_uart_debug(ARDUINO, "%c", 0x03);
        tx_uart_debug(ARDUINO, "%c", 0x03);
        tx_uart_debug(ARDUINO, "%c", 0x03);
        tx_uart_debug(ARDUINO, "%c", 0x55);
        tx_uart_debug(ARDUINO, "hello");
        tx_uart_pc_debug("arduino sent\r\n");
        */

        // Arduino Receive
        //rx_uart_debug(ARDUINO);

        rx_uart(ARDUINO);
        rx_uart(RPI);
        rx_uart(TOF);


        PrepareArduinoMessageAndSend(s_speedL_integer, s_speedL_decimal, s_speedR_integer, s_speedR_decimal, s_slope, s_targetSpeed, s_steeringAngle);  // TODO 자꾸떠서 주석해놨음

        RingBufferInit(&s_arduinoRxRingBuffer);
        RingBufferInit(&s_rpiRxRingBuffer);
        RingBufferInit(&s_tofRxRingBuffer);

        if(flag1 == 1){
            flag1 = 0;
        }

        for (volatile int i = 0; i < 5000000; i++); // 100ms
        //for (volatile int i = 0; i < 1000000 / 2 * 5; i++); //50ms
        //for (volatile int i = 0; i < 1000000; i++); // 20ms
        //for (volatile int i = 0; i < 50000000; i++); // 1 second
        //for (int i = 0; i < 1000000; i++); // 50 msec
    }
}
