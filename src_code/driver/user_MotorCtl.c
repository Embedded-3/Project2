// User Motor Control
#include "user_MotorCtl.h"
#include "Ifx_Types.h"
#include "IfxStdIf.h"

volatile Speed_t speed = {0, 0};

void getSpeed(int time) // int time : 측정시간 (ms)
{
    // 속도 (cm/s) = (duration × 바퀴 원주) / (PPR × 측정 시간(ms))
    speed.lspeed = left_duration * DIAMETER * 3.1416 / (PPR * time / 1000);
    speed.rspeed = right_duration * DIAMETER * 3.1416 / (PPR * time / 1000);

    print("%d | %d\n\r", left_duration, right_duration);
    print(CYAN"%.3lf [cm/s] | %.3lf [cm/s]\n\r"RESET, speed.lspeed, speed.rspeed);

    right_duration = 0;
    left_duration = 0;
}