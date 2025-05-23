// main.c

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "driver/pwm/pwm.h"
#include "driver/encoder/encoder.h"
#include "driver/stm/stm.h"
#include "driver/user_MotorCtl.h"
#include "parser.h"

#include "shared_memory.h"
#include "string.h"

#include "main.h"

#include "IfxPort.h"
#include "IfxPort_PinMap.h"

#include "driver/imu/imu.h"
#include "etc.h"
float ax, ay, az;
float gx, gy, gz;
sint16 mx, my, mz;


IfxCpu_syncEvent g_cpuSyncEvent = 0;

switch_t flag_sw = {0};

int distance = 0;
int prev_distance = -1;


static void handleSpeedSwitch(int* cur, int* prev, Ifx_P *port, uint8 pin, SwitchType speed);

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
        
    //initShellInterface();   // 디버깅
    Driver_Stm_Init();      // 스케줄링
    initEncoder();          // 엔코더 초기화

    initPwm();              // PWM 초기화
    startPwm();             // PWM 시작
    
    init_I2C_module();                      //I2C_init
    resetMPU9250();
    calibrate_mpu9250();
    init_mpu9250_registers();               //mpu92500_registers_init
    init_ak8963_registers();                //ak8963_registers_init
    delay_ms(500);


    //for(int i=0;i<4;i++) setPwm(i, GO_AFTER_STOP);

    //for(int i=0;i<4;i++) setPwm(i, MIN);
    //for(int i=0;i<4;i++) setPwm(i, 1700);   
    //for(int i=0;i<4;i++) setPwm(i, 2000);   
    //for(int i=0;i<4;i++) setPwm(i, MAX);   
    //setCurve(LEFT, 2000, MAX); // 왼쪽으로 회전 : 급격한 회전
    //setCurve(RIGHT, MAX, 3000); // 왼쪽으로 회전 : 급격한 회전
    //setCurve(RIGHT, 3500, 3000); // 깔끔한 회전??


    // 스위치
    IfxPort_setPinModeInput(ON_OFF_SW_PIN, IfxPort_InputMode_pullUp);
    IfxPort_setPinModeInput(YELLOW_SPEED_SW_PIN, IfxPort_InputMode_pullUp);
    IfxPort_setPinModeInput(GREEN_SPEED_SW_PIN, IfxPort_InputMode_pullUp);
    IfxPort_setPinModeInput(BLUE_SPEED_SW_PIN, IfxPort_InputMode_pullUp);

    // LED
    IfxPort_setPinModeOutput(ADAS_LED_PIN, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(ADAS_LED_PIN); 

    // 브레이크
    IfxPort_setPinModeOutput(BRAKE_PIN, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(BRAKE_PIN); 

    tx_uart_pc_debug("\r\n");
    tx_uart_pc_debug("***********************CPU0************************\r\n");
    tx_uart_pc_debug("***********************CPU0************************\r\n");

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

static void handleSpeedSwitch(int* cur, int* prev, Ifx_P *port, uint8 pin, SwitchType whichSwitch) {
    *cur = IfxPort_getPinState(port, pin);

    if (!(*cur) && *prev) {  // falling edge
        switch (whichSwitch) {
            case ON_OFF:
                flag_sw.on_off = !flag_sw.on_off;               // on/off 토글
                flag_sw = (switch_t){flag_sw.on_off, 0, 0, 0};  // 속도 초기화
                IfxPort_togglePin(ADAS_LED_PIN);
                tx_uart_pc_debug(RRED"ON/OFF : %d\n\r"RESET, flag_sw.on_off);
                
                setSpeed(STOP); // 브레이크
                break;

            case SPEED_BLUE:
                if(!flag_sw.on_off) break;
                flag_sw = (switch_t){flag_sw.on_off, 1, 0, 0};
                tx_uart_pc_debug(BLUE"SPEED : BLUE\n\r"RESET);

                setSpeed(SPEED_1);
                break;

            case SPEED_GREEN:
                if(!flag_sw.on_off) break;
                flag_sw = (switch_t){flag_sw.on_off, 0, 1, 0};
                tx_uart_pc_debug(GREEN"SPEED : GREEN\n\r"RESET);

                setSpeed(SPEED_2);
                break;

            case SPEED_YELLOW:
                if(!flag_sw.on_off) break;
                flag_sw = (switch_t){flag_sw.on_off, 0, 0, 1};
                tx_uart_pc_debug(YELLOW"SPEED : YELLOW\n\r"RESET);

                setSpeed(SPEED_3);
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

    if(!flag_sw.on_off) return; // TOOD 임시

    // Priority 1 : ToF
    if(stTestCnt.u32nuCnt10ms % 5== 0) {   // Period : 50ms
        if(s_distance <= 40) {
            ; //setSpeed(STOP);
        }
        else {
            ;
        }
    }

    // Priority 2 : IMU
    if(stTestCnt.u32nuCnt10ms % 5 == 0) {   // Period : 50ms
        // imu
        read_accel_g(&ax, &ay, &az);
        read_gyro_dps(&gx, &gy, &gz);
        read_magnetometer_raw(&mx, &my, &mz);
        float mx_ut = mx * 0.15f;
        float my_ut = my * 0.15f;
        float mz_ut = mz * 0.15f;
        MadgwickQuaternionUpdate(ax, ay, az, gx , gy, gz, mx_ut, my_ut, mz_ut);
        quaternionToEuler();
        //if(offset_calibrated) print("Yaw=%d, Pitch=%d, Roll=%d\n\r", (int)yaw, (int)pitch, (int)roll);
        if(offset_calibrated) {
            //tx_uart_pc_debug("Madgwick = %d\n\r",(int)pitch);
            s_slope = (int)pitch;
        }
        //






        // if(flag_sw.on_off) {
        //     getSpeed(50); // 속도 측정
        //     tx_uart_pc_debug(MAGENTA"set %.3lf \n\r"RESET, pid_control(s_targetSpeed, measured_speed.lspeed, 50));
        // }
        
        if(s_distance <= 30){ // 속도가 빠르면 tof가 읽기전에 이미 가 있음 조절 필요
            //IfxPort_setPinHigh(BRAKE_PIN);
            //for(int i=0;i<4;i++) setPwm(i, 0);   
            ;
            //print("BRAKE\n\r");

        }
        else{ ;
            //IfxPort_setPinLow(BRAKE_PIN);
            //for(int i=0;i<4;i++) setPwm(i, 3500);   
            //print("GO\n\r");
        }



    }



}

void AppTask100ms(void)
{
    stTestCnt.u32nuCnt100ms++;
    distance = s_distance;



}

void AppTask1000ms(void)
{
    stTestCnt.u32nuCnt1000ms++;

    if(flag_sw.on_off) {
        getSpeed(1000); // 속도 측정
        //setSpeed(SPEED_3);
    }

    //pid_control(s_targetSpeed, measured_speed.rspeed, 1000);
    //tx_uart_pc_debug(MAGENTA"set %d \n\r"RESET, pid_control(s_targetSpeed, measured_speed.rspeed, 1000));
    if(flag_sw.on_off) {
        //for(int i=0;i<4;i++) setPwm(i, 3500);   
        //getSpeed(1000); // 속도 측정
        //tx_uart_pc_debug(MAGENTA"set %.3lf \n\r"RESET, pid_control(s_targetSpeed, measured_speed.lspeed, 1));

        // 소수점 두자리만 보내도록 고치기
        s_speedL_integer = (uint8)measured_speed.lspeed;
        s_speedL_decimal = (uint8)(measured_speed.lspeed - (double)s_speedL_integer);
        s_speedR_integer = (uint8)measured_speed.rspeed;
        s_speedR_decimal = (uint8)(measured_speed.rspeed - (double)s_speedR_integer);
    }
    else{
        for(int i=0;i<4;i++) setPwm(i, 0);   
    }

    //print("%d %d %d\n\r", flag_sw.y, flag_sw.g, flag_sw.b);

    
}
