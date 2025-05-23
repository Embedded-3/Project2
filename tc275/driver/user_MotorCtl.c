// User Motor Control
#include "user_MotorCtl.h"
#include "Ifx_Types.h"
#include "parser.h"
#include "pwm.h"
#include "encoder.h"
#include "driver\parser\parser.h"


volatile Speed_t speed = {0, 0};

void getSpeed(int time) // int time : 측정시간 (ms)
{
    // 속도 (cm/s) = (duration × 바퀴 원주) / (PPR × 측정 시간(ms))
    speed.lspeed = left_duration * DIAMETER * 3.1416 / (PPR * time / 1000);
    speed.rspeed = right_duration * DIAMETER * 3.1416 / (PPR * time / 1000);

    tx_uart_pc_debug("%d | %d\n\r", left_duration, right_duration);
    tx_uart_pc_debug(CYAN"%.3lf [cm/s] | %.3lf [cm/s]\n\r"RESET, speed.lspeed, speed.rspeed);

    right_duration = 0;
    left_duration = 0;
}

// void setAllMotor(uint32 dutyCycle){
//     if(dutyCycle == 0) 
// }
void setSpeed(SpeedType speedType)  // 스위치로 선택한 속도를 PWM으로 치환
{
    switch (speedType) {
        case STOP:
            IfxPort_setPinHigh(BRAKE_PIN);
            for (int i = 0; i < NUM_WHEELS; i++) {
                setPwm(i, STOP);
            }
            break;
        case SPEED_1:
            s_targetSpeed = 10; // TODO
            IfxPort_setPinLow(BRAKE_PIN);
            for (int i = 0; i < NUM_WHEELS; i++) {
                setPwm(i, DT_SPEED_1);
            }
            break;
        case SPEED_2:
            s_targetSpeed = 20; // TODO
            IfxPort_setPinLow(BRAKE_PIN);
            for (int i = 0; i < NUM_WHEELS; i++) {
                setPwm(i, DT_SPEED_2);
            }
            break;
        case SPEED_3:
            s_targetSpeed = 30; // TODO
            IfxPort_setPinLow(BRAKE_PIN);
            for (int i = 0; i < NUM_WHEELS; i++) {
                setPwm(i, DT_SPEED_3);
            }
            break;
        default:    // 잘못된 속도 타입 -> 멈춤
            tx_uart_pc_debug(RRED"Invalid speed type\n\r"RESET);            
            IfxPort_setPinHigh(BRAKE_PIN);
            for (int i = 0; i < NUM_WHEELS; i++) {
                setPwm(i, STOP);
            }
            break;
    }
}
