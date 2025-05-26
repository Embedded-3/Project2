// User Motor Control
#include "user_MotorCtl.h"
#include "Ifx_Types.h"
#include "parser.h"
#include "pwm.h"
#include "encoder.h"
#include "driver\parser\parser.h"


volatile Speed_t measured_speed = {0, 0};

void getSpeed(int time) // int time : 측정시간 (ms)
{
    // 속도 (cm/s) = (duration × 바퀴 원주) / (PPR × 측정 시간(ms))
    measured_speed.lspeed = left_duration * DIAMETER * 3.1416 / (PPR * time / 1000);
    measured_speed.rspeed = right_duration * DIAMETER * 3.1416 / (PPR * time / 1000);

    //tx_uart_pc_debug("%d | %d\n\r", left_duration, right_duration);
    static int cnt = 0;
    if (cnt++ % 10 == 0) { // 10번마다 출력
        tx_uart_pc_debug(RRED"%.3lf [cm/s] | %.3lf [cm/s]\n\r"RESET, measured_speed.lspeed, measured_speed.rspeed);
    }


    // duration 초기화
    right_duration = 0;
    left_duration = 0;
}


void setSpeed(SpeedType speedType)  // 스위치로 선택한 속도를 PWM으로 치환
{
    switch (speedType) {
        case STOP:
            s_targetSpeed = 1; // TODO
            setAllMotor(STOP);
            break;
        case SPEED_1:
            s_targetSpeed = 20; //10; // TODO
            //setAllMotor(DT_SPEED_1);
            break;
        case SPEED_2:
            s_targetSpeed = 30; //20; // TODO
            //setAllMotor(DT_SPEED_2);
            break;
        case SPEED_3:
            s_targetSpeed = 40; //30; // TODO
            //setAllMotor(DT_SPEED_3);
            break;
        default:    // 잘못된 속도 타입 -> 멈춤
            tx_uart_pc_debug(RRED"Invalid speed type\n\r"RESET);            
            setAllMotor(STOP);
            break;
    }
}






// float Kp = 1.2f, Ki = 0.005f, Kd = 0.02f;
// volatile float prev_error = 0.0, integral = 0.0;

// int pid_control(float set_speed, float measured_speed, float dt_ms) {
//     float dt = dt_ms / 1000.0f;  // ms → s 변환
//     float error = set_speed - measured_speed;

//     integral += error * dt;
//     if (integral > 100.0f) integral = 100.0f;
//     if (integral < -100.0f) integral = -100.0f;

//     float derivative = (error - prev_error) / dt;
//     prev_error = error;

//     float output = Kp * error; // + Ki * integral + Kd * derivative;

//     // 기준 2000, 출력에 따라 ± 조절
//     float duty = 2000.0f + output * 500.0f;
//     if (duty > 4000.0f) duty = 4000.0f;
//     if (duty < 0.0f)   duty = 0.0f;
    
//     tx_uart_pc_debug("set_speed: %.3f | measured_speed: %.3f\n\r", set_speed, measured_speed);
//     tx_uart_pc_debug("PID: %.3f | %.3f | %.3f | %.3f\n\r", Kp * error, Ki * integral, Kd * derivative, output);
//     tx_uart_pc_debug("output: %.3f\n\r", output);
//     tx_uart_pc_debug("duty: %.3f\n\r", duty);

//     return duty;
// }
