#include "ToF.h"
#include "Ifx_Types.h"
#include "IfxAsclin_Asc.h"
#include "Ifx_Shell.h"
#include "Ifx_Console.h"
#include "IfxPort.h"
#include "asclin.h"
#include "etc.h"

#define TOF_FRAME_SIZE 16

static unsigned char gBuf_tof[TOF_FRAME_SIZE] = {0};




static IfxStdIf_DPipe  g_ascStandardInterface0;
static IfxAsclin_Asc   g_asclin0;

static const unsigned char TOF_length = 16;
static unsigned int rxBufIdx = 0;

static uint8 g_uartTxBuffer0[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 g_uartRxBuffer0[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


static void initSerialInterface0(void);

IFX_INTERRUPT(asc0TxISR, 0, ISR_PRIORITY_ASCLIN0_TX);
void asc0TxISR(void)
{
    IfxStdIf_DPipe_onTransmit(&g_ascStandardInterface0);
}


IFX_INTERRUPT(asc0RxISR, 0, ISR_PRIORITY_ASCLIN0_RX);
void asc0RxISR(void)
{
    Ifx_SizeT count = IfxAsclin_getRxFifoFillLevel(&g_asclin0);

    if (count > 0)
    {
        unsigned char c;
        IfxAsclin_read8(&g_asclin0, &c, 1);

        gBuf_tof[rxBufIdx++] = c;

        if (rxBufIdx == TOF_FRAME_SIZE)
        {
            print("ToF Frame: ");
            for (int i = 0; i < TOF_FRAME_SIZE; i++)
                print("%02X ", gBuf_tof[i]);
            print("\n");
            rxBufIdx = 0;
        }
    }

    IfxStdIf_DPipe_onReceive(&g_ascStandardInterface0);
}


IFX_INTERRUPT(asc0ErrISR, 0, ISR_PRIORITY_ASCLIN0_ER);
void asc0ErrISR(void)
{
    print("ER\n\r");
    IfxStdIf_DPipe_onError(&g_ascStandardInterface0);
}


void ToF_Init(void)
{
    /* Initialize the hardware peripherals */
    initSerialInterface0();

    /* Initialize the Standard Interface */
    IfxAsclin_Asc_stdIfDPipeInit(&g_ascStandardInterface0, &g_asclin0);

}

void initSerialInterface0(void)
{
    IfxAsclin_Asc_Config ascConf0;

    /* Set default configurations */
    IfxAsclin_Asc_initModuleConfig(&ascConf0, &MODULE_ASCLIN0); /* Initialize the structure with default values      */

    /* Set the desired baud rate */
    ascConf0.baudrate.baudrate = 115200;                                   /* Set the baud rate in bit/s       */
    ascConf0.baudrate.oversampling = IfxAsclin_OversamplingFactor_16;            /* Set the oversampling factor      */

    /* Configure the sampling mode */
    ascConf0.bitTiming.medianFilter = IfxAsclin_SamplesPerBit_three;             /* Set the number of samples per bit*/
    ascConf0.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_8;    /* Set the first sample position    */

    /* ISR priorities and interrupt target */
    ascConf0.interrupt.txPriority = ISR_PRIORITY_ASCLIN0_TX;  /* Set the interrupt priority for TX events             */
    ascConf0.interrupt.rxPriority = ISR_PRIORITY_ASCLIN0_RX;  /* Set the interrupt priority for RX events             */
    ascConf0.interrupt.erPriority = ISR_PRIORITY_ASCLIN0_ER;  /* Set the interrupt priority for Error events          */
    ascConf0.interrupt.typeOfService = IfxSrc_Tos_cpu0;

    /* Pin configuration */
    const IfxAsclin_Asc_Pins pins = {
            .cts        = NULL_PTR,                         /* CTS pin not used                                     */
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rx         = &IfxAsclin0_RXB_P15_3_IN ,        /* Select the pin for RX connected to the USB port      */
            .rxMode     = IfxPort_InputMode_pullUp,         /* RX pin                                               */
            .rts        = NULL_PTR,                         /* RTS pin not used                                     */
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .tx         = &IfxAsclin0_TX_P15_2_OUT,         /* Select the pin for TX connected to the USB port      */
            .txMode     = IfxPort_OutputMode_pushPull,      /* TX pin                                               */
            .pinDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf0.pins = &pins;

    /* FIFO buffers configuration */
    ascConf0.txBuffer = g_uartTxBuffer0;                      /* Set the transmission buffer                          */
    ascConf0.txBufferSize = ASC_TX_BUFFER_SIZE;              /* Set the transmission buffer size                     */
    ascConf0.rxBuffer = g_uartRxBuffer0;                      /* Set the receiving buffer                             */
    ascConf0.rxBufferSize = ASC_RX_BUFFER_SIZE;              /* Set the receiving buffer size                        */

    /* Init ASCLIN module */
    IfxAsclin_Asc_initModule(&g_asclin0, &ascConf0);          /* Initialize the module with the given configuration   */
}

int data(void)
{
    #define DATA_LEN 16
    #define TIMEOUT_LIMIT 5000000

    uint8 response[DATA_LEN] = {0};
    Ifx_SizeT rxLength = DATA_LEN;

    IfxStdIf_DPipe_read(&g_ascStandardInterface0, response, &rxLength, TIMEOUT_LIMIT);
    // 헤더 검증 (0x57 0x00 0xFF 0x00)
    if (!(response[0] == 0x57 && response[1] == 0x00 && response[2] == 0xFF && response[3] == 0x00)) {
        return -1;
    }

    // 거리 유효성 확인
    unsigned long distance_mm = ((unsigned long)response[8]) |
                                ((unsigned long)response[9] << 8) |
                                ((unsigned long)response[10] << 16);

    unsigned char status = response[11];

    if (status != 0 || distance_mm == 0 || distance_mm == 0xFFFFF6) {
        return -1;
    }

    // mm → cm 변환 (소수점 버림)
    unsigned int distance_cm = distance_mm / 10;

    return (int)distance_cm;
}

