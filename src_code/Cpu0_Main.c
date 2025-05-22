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

#include "IfxPort.h"
#include "IfxPort_PinMap.h"
#include "mp.h"

#define ON_OFF_SW_PIN         &MODULE_P33, 6
#define ADAS_LED_PIN          &MODULE_P22, 2

// d49 d51 d53
#define YELLOW_SPEED_SW_PIN   &MODULE_P21, 0
#define GREEN_SPEED_SW_PIN    &MODULE_P33, 12
#define BLUE_SPEED_SW_PIN     &MODULE_P33, 7

IfxCpu_syncEvent g_cpuSyncEvent = 0;

int flag_on_off_sw = 0;
switch_t flag_speed_sw = {0, 0, 0};


static void handleSpeedSwitch(int* cur, int* prev, Ifx_P *port, uint8 pin, SpeedType speed);

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
    //for(int i=0;i<4;i++) setPwm(i, MAX);   
    //setCurve(LEFT, 2000, MAX); // 왼쪽으로 회전 : 급격한 회전
    //setCurve(RIGHT, MAX, 3000); // 왼쪽으로 회전 : 급격한 회전
    //setCurve(RIGHT, 3500, 3000); // 깔끔한 회전??


    // init_I2C_module();
    // init_mpu9250_registers();


    IfxPort_setPinModeInput(ON_OFF_SW_PIN, IfxPort_InputMode_pullUp);
    IfxPort_setPinModeOutput(ADAS_LED_PIN, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(ADAS_LED_PIN); 

    IfxPort_setPinModeInput(YELLOW_SPEED_SW_PIN, IfxPort_InputMode_pullUp);
    IfxPort_setPinModeInput(GREEN_SPEED_SW_PIN, IfxPort_InputMode_pullUp);
    IfxPort_setPinModeInput(BLUE_SPEED_SW_PIN, IfxPort_InputMode_pullUp);


    while(1)
    {
        AppScheduling();

        // Speed switch
        static int cur_sw = 0, prev_sw = 0;
        static int cur_yellow = 0, prev_yellow = 0;
        static int cur_green = 0, prev_green = 0;
        static int cur_blue = 0, prev_blue = 0;

        handleSpeedSwitch(&cur_sw, &prev_sw, ON_OFF_SW_PIN, ON_OFF);
        handleSpeedSwitch(&cur_yellow, &prev_yellow, YELLOW_SPEED_SW_PIN, SPEED_YELLOW);
        handleSpeedSwitch(&cur_green, &prev_green, GREEN_SPEED_SW_PIN, SPEED_GREEN);
        handleSpeedSwitch(&cur_blue, &prev_blue, BLUE_SPEED_SW_PIN, SPEED_BLUE);
        //

    }
}

static void handleSpeedSwitch(int* cur, int* prev, Ifx_P *port, uint8 pin, SpeedType speed) {
    *cur = IfxPort_getPinState(port, pin);

    if (!(*cur) && *prev) {  // falling edge
        switch (speed) {
            case ON_OFF:
                flag_on_off_sw = !flag_on_off_sw;
                IfxPort_togglePin(ADAS_LED_PIN);
                print(RED"ON/OFF : %d\n\r"RESET, flag_on_off_sw);
                break;
            case SPEED_YELLOW:
                flag_speed_sw = (switch_t){flag_speed_sw.on_off, 1, 0, 0};
                print(YELLOW"SPEED : YELLOW\n\r"RESET);
                break;
            case SPEED_GREEN:
                flag_speed_sw = (switch_t){flag_speed_sw.on_off, 0, 1, 0};
                print(GREEN"SPEED : GREEN\n\r"RESET);
                break;
            case SPEED_BLUE:
                flag_speed_sw = (switch_t){flag_speed_sw.on_off, 0, 0, 1};
                print(BLUE"SPEED : BLUE\n\r"RESET);
                break;
        }
    }

    *prev = *cur;
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

    if(flag_on_off_sw) {
        for(int i=0;i<4;i++) setPwm(i, 3500);   
        getSpeed(1000); // 속도 측정
    }

    //print("%d %d %d\n\r", flag_speed_sw.y, flag_speed_sw.g, flag_speed_sw.b);

}
