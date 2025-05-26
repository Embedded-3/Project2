// main.c

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "driver/pwm/pwm.h"
#include "driver/encoder/encoder.h"
#include "driver/stm/stm.h"
#include "driver/user_MotorCtl/user_MotorCtl.h"
#include "parser.h"

#include "shared_memory.h"
#include "string.h"

#include "main.h"

#include "IfxPort.h"
#include "IfxPort_PinMap.h"

#include "driver/imu/imu.h"
#include "etc.h"
#include "safety.h"
#include "Bsp.h"
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define REL_VAL     0xE000
#define WAIT_TIME   1000            // 1000ms (1초) 대기 

float ax, ay, az;
float gx, gy, gz;
sint16 mx, my, mz;


IfxCpu_syncEvent g_cpuSyncEvent = 0;

switch_t flag_sw = {0};

uint32 stop_distance = 0; // 브레이크 거리
volatile sint16 sum_left_pwm = 0, sum_right_pwm = 0;

volatile int left_pwm = 0, right_pwm = 0; // 수동

static void handleSpeedSwitch(int* cur, int* prev, Ifx_P *port, uint8 pin, SwitchType speed);


void core0_main(void)
{
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    // //
    // IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    // IfxScuWdt_changeCpuWatchdogReload(IfxScuWdt_getCpuWatchdogPassword(), REL_VAL); /* Set CPU0WD timer to ~1.3 sec */
    // IfxScuWdt_serviceCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());               /* Service the CPU0WDT          */
    // // //

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

    // 초기화
    s_targetSpeed = 1;
    s_slope = 1;
    s_steeringAngle =1;
    s_speedL_integer = 1;
    s_speedL_decimal = 1;
    s_speedR_integer = 1;
    s_speedR_decimal = 1;
    s_distance = 1;

    //setPwm(FR, 0); // 초기화
    //Ifx_TickTime ticksFor1s = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME); // CPU0의 Watchdog 갱신

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
                sum_left_pwm = 0;
                sum_right_pwm = 0;
                            tx_uart_pc_debug(GREEN"STOP\n\r"RESET);
                break;

            case SPEED_BLUE:
                if(!flag_sw.on_off) break;
                flag_sw = (switch_t){flag_sw.on_off, 1, 0, 0};
                tx_uart_pc_debug(BLUE"SPEED : BLUE\n\r"RESET);
                setSpeed(SPEED_1);
                //s_targetSpeed = 20;
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


            //if(!flag_sw.on_off) return;
            //getSpeed(1); // 속도 측정1
            // if(measured_speed.lspeed > s_targetSpeed){
            //     left_pwm -= 10; // 왼쪽 바퀴 속도가 목표 속도보다 크면 속도 감소
            // }
            // else if(measured_speed.lspeed < s_targetSpeed){
            //     left_pwm += 10; // 왼쪽 바퀴 속도가 목표 속도보다 작으면 속도 증가
            // }
            // if(measured_speed.rspeed > s_targetSpeed){
            //     right_pwm -= 10; // 오른쪽 바퀴 속도가 목표 속도보다 크면 속도 감소
            // }
            // else if(measured_speed.rspeed < s_targetSpeed){
            //     right_pwm += 10; // 오른쪽 바퀴 속도가 목표 속도보다 작으면 속도 증가
            // }
            // setPwm(FR, right_pwm);
            // setPwm(FL, left_pwm);
            // setPwm(RR, right_pwm);
            // setPwm(RL, left_pwm);
}

void AppTask10ms(void)
{
    stTestCnt.u32nuCnt10ms++;

    if(stTestCnt.u32nuCnt10ms % 2 == 0) {   // Period : 20ms
        if(flag0 == 0){
            flag0 = 1;
        }
        else if(flag0 == 2){
            tx_uart_pc_debug("Core0 STOP\n\r");
            //return;
        }
    }

    // Priority 1 : ToF
    static uint32 prev_distance = 0;
    if(stTestCnt.u32nuCnt10ms % 5 == 0) {   // Period : 50ms
        uint16 avg_speed = (s_speedL_integer + s_speedR_integer) / 2;
        stop_distance = (avg_speed / 5) * 5 + 17;    //ex) 0이면 25cm, 30이면 55cm, 20이면 45cm
        //tx_uart_pc_debug("s_distance %d\n\r", s_distance);
        uint32 diff = MAX(s_distance, prev_distance) - MIN(s_distance, prev_distance);
        static int tofCnt = 0;
        if(diff <= 10 && s_distance <= stop_distance) {
            if(tofCnt++ % 20  == 0){
                tx_uart_pc_debug(BLUE"STOP! distance\r\n"RESET);
                ;
            }
            //    tx_uart_pc_debug("STOP! distance\n");
 
            //setSpeed(STOP);
        }
        else{
            IfxPort_setPinLow(BRAKE_PIN);
        }
        prev_distance = s_distance;
    }

    // Priority 2 : IMU
    if(stTestCnt.u32nuCnt10ms % 5 == 0) {   // Period : 50ms
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
            if(s_slope == 0) s_slope = 1;
        }
    }
    
    if(stTestCnt.u32nuCnt10ms % 10 == 0) {   // Period : 50ms
        getSpeed(100); // 속도 측정4

        // 소수점 두자리만 보냄
        s_speedL_integer = (uint8)measured_speed.lspeed;
        s_speedL_decimal = (uint8)((measured_speed.lspeed - (double)s_speedL_integer) * 100);
        s_speedR_integer = (uint8)measured_speed.rspeed;
        s_speedR_decimal = (uint8)((measured_speed.rspeed - (double)s_speedR_integer) * 100);

        s_speedL_decimal = MAX(s_speedL_decimal, 1);
        s_speedR_decimal = MAX(s_speedR_decimal, 1);
        s_speedL_integer = MAX(s_speedL_integer, 1);
        s_speedR_integer = MAX(s_speedR_integer, 1);

        if(flag_sw.on_off) {    // on/off 스위치 켜져있을 때만 바퀴 제어


            // 바퀴 제어
            if (s_targetLeftPWM != 0 && s_targetRightPWM != 0) {
                //tx_uart_pc_debug("%d %d\r\n",)
                IfxPort_setPinLow(BRAKE_PIN);
                sum_left_pwm += (sint16)s_targetLeftPWM;
                sum_right_pwm += (sint16)s_targetRightPWM;
                
                if(sum_left_pwm > 4000) sum_left_pwm = 4000;
                else if(sum_left_pwm < 0) sum_left_pwm = 0;
                if(sum_right_pwm > 4000) sum_right_pwm = 4000;
                else if(sum_right_pwm < 0) sum_right_pwm = 0;
                setPwm(FR, sum_right_pwm);
                setPwm(FL, sum_left_pwm);
                setPwm(RR, sum_right_pwm);
                setPwm(RL, sum_left_pwm);


                // setPwm(FR, s_targetRightPWM);
                // setPwm(FL, s_targetLeftPWM);
                // setPwm(RR, s_targetRightPWM);
                // setPwm(RL, s_targetLeftPWM);
            }


        }
    }

    // 빨강 스위치 off면 속도 0
    if(!flag_sw.on_off) {
        setSpeed(STOP);
    }

    if(stTestCnt.u32nuCnt10ms % 2 == 0) {   // Period : 20ms
        if(flag0 == 1){
            flag0 = 0;
        }
    }

}

void AppTask100ms(void)
{
    stTestCnt.u32nuCnt100ms++;
}

void AppTask1000ms(void)
{
    stTestCnt.u32nuCnt1000ms++;

    //IfxScuWdt_serviceCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());

    tx_uart_pc_debug("\r\n--------------------------\r\n");
    tx_uart_pc_debug(GREEN"target speed : %d\r\n"RESET, s_targetSpeed);
    tx_uart_pc_debug(CYAN"PID 받은 속도 : %d[cm/s]  %d[cm/s]      |||| %d %d\r\n"RESET, s_speedL_integer, s_speedR_integer, s_speedL_decimal, s_speedR_decimal);
    tx_uart_pc_debug(CYAN"sum PWM : %d | %d\r\n"RESET, sum_left_pwm, sum_right_pwm);
    tx_uart_pc_debug(MAGENTA"tof : %d\r\n"RESET, s_distance);
    //tx_uart_pc_debug(RRED"1s stop_distance : %d\r\n"RESET, stop_distance);
    tx_uart_pc_debug(YELLOW"steeringangle : %d, slope : %d\r\n"RESET, s_steeringAngle, s_slope);


}
