#define S_FUNCTION_NAME  sfun_uart
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"
#include "uart_handler.h"

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumOutputPorts(S, 1);
    ssSetOutputPortWidth(S, 0, 1);
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
    uart_init();  // 인터럽트 초기화
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    uint8_T *y = (uint8_T *)ssGetOutputPortSignal(S, 0);

    if (uart_available() > 0) {
        *y = (uint8_T)uart_read();
    } else {
        *y = 0;
    }
}

static void mdlTerminate(SimStruct *S) {}

#include "simulink.c"