// main.c

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "asclin.h"
#include "adc.h"
#include "driver/pwm/pwm.h"
#include "driver/encoder/encoder.h"
#include "driver/stm/stm.h"
#include "driver/user_MotorCtl.h"
#include "main.h"

// #include "IfxPort.h"
// #include "IfxPort_PinMap.h"
#include "mp.h"


IfxCpu_syncEvent g_cpuSyncEvent = 0;

void core0_main(void)
{
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
        
    initShellInterface();   // 디버깅
    Driver_Stm_Init();      // 스케줄링
    initEncoder();          // 엔코더 초기화

    initPwm();              // PWM 초기화
    startPwm();             // PWM 시작


    //for(int i=0;i<4;i++) setPwm(i, GO_AFTER_STOP);

    //for(int i=0;i<4;i++) setPwm(i, MIN);
    //for(int i=0;i<4;i++) setPwm(i, 1700);   
    //for(int i=0;i<4;i++) setPwm(i, 2000);   
    for(int i=0;i<4;i++) setPwm(i, 1600);   
    //setCurve(LEFT, 2000, MAX); // 왼쪽으로 회전 : 급격한 회전
    //setCurve(RIGHT, MAX, 3000); // 왼쪽으로 회전 : 급격한 회전
    //setCurve(RIGHT, 3500, 3000); // 깔끔한 회전??


    // init_I2C_module();
    // init_mpu9250_registers();

    while(1)
    {
        AppScheduling();



    }
}



void AppTask1ms(void)
{
    stTestCnt.u32nuCnt1ms++;
}

void AppTask10ms(void)
{
    stTestCnt.u32nuCnt10ms++;
}

void AppTask100ms(void)
{
    stTestCnt.u32nuCnt100ms++;
}

void AppTask1000ms(void)
{
    stTestCnt.u32nuCnt1000ms++;
// read_mpu9250_sensor_data();
// print_mpu9250_sensor_data();

    getSpeed(1000); // 속도 측정


}
