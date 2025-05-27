// pwm.h
#ifndef PWM_H
#define PWM_H

#include "Ifx_Types.h"
#include "IfxGtm_Tom_Pwm.h"
#include "IfxGtm_Cmu.h"
#include "IfxGtm_Atom_Pwm.h"

#define NUM_WHEELS 4

// ATOM 모듈 0
#define FrontRight          IfxGtm_ATOM0_0_TOUT0_P02_0_OUT // D2 pin
#define FrontLeft           IfxGtm_ATOM0_1_TOUT1_P02_1_OUT // D3 pin
#define RearRight           IfxGtm_ATOM0_3_TOUT3_P02_3_OUT // D5 pin
#define RearLeft            IfxGtm_ATOM0_4_TOUT4_P02_4_OUT // D6 pin


#define CLK_FREQ                     100000000.0f // 1000000.0f
#define PWM_PERIOD                   4000
#define DEFAULT_DUTY_FRONT_RIGHT     STOP
#define DEFAULT_DUTY_FRONT_LEFT      STOP
#define DEFAULT_DUTY_REAR_RIGHT      STOP                
#define DEFAULT_DUTY_REAR_LEFT       STOP             

typedef enum WHEEL{
    FR = 0,
    FL = 1,
    RR = 2,
    RL = 3,
} e_Wheel_t;


typedef enum DUTYCYCLE{
    DT_STOP = 0,


    DT_SPEED_1 = 1900,
    DT_SPEED_2 = 2000,
    DT_SPEED_3 = 2100,
} e_DutyCycle_t;



void initPwm(void);
void startPwm(void);
void setPwm(const e_Wheel_t whichWheel, uint32 dutyCycle);
void setAllMotor(uint32 dutyCycle);

#endif
/*
무부하 엔코더 값 기록

속도(듀티) | 엔코더 값
1700    680?    // 진짜 최저 속도 거북이임
MIN     1380
MAX     3100
3000    2400
2500    1760

*/