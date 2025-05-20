// pwm.h
#ifndef PWM_H
#define PWM_H

#include "Ifx_Types.h"
#include "IfxGtm_Tom_Pwm.h"
#include "IfxGtm_Cmu.h"
#include "IfxGtm_Atom_Pwm.h"
#include "asclin.h"

#define ISR_PRIORITY_TOM    20                                      /* Interrupt priority number                    */

// ATOM 모듈 0, 채널 0으로 통일
#define FrontRight          IfxGtm_ATOM0_0_TOUT0_P02_0_OUT // D2 pin
#define FrontLeft           IfxGtm_ATOM0_1_TOUT1_P02_1_OUT // D3 pin
#define RearRight           IfxGtm_ATOM0_3_TOUT3_P02_3_OUT // D5 pin
#define RearLeft            IfxGtm_ATOM0_4_TOUT4_P02_4_OUT // D6 pin


#define CLK_FREQ                     100000000.0f // 1000000.0f
#define PWM_PERIOD                   4000
#define DEFAULT_DUTY_FRONT_RIGHT     2500 //5000000 //20000 //12000 //10000
#define DEFAULT_DUTY_FRONT_LEFT      2300 // 2500 
#define DEFAULT_DUTY_REAR_RIGHT      2300 //00 //20000 //12000 //10000                   
#define DEFAULT_DUTY_REAR_LEFT       2300 //00 //3500 //5000 //10000                     

typedef enum WHEEL{
    FR = 0,
    FL = 1,
    RR = 2,
    RL = 3,
} e_Wheel_t;

typedef enum SPEED{
    STOP = 0,
    MIN = 2300,

    MAX = 4000,
} e_Speed_t;

void initPwm(void);
void startPwm(void);
void setPwm(const e_Wheel_t whichWheel, uint32 dutyCycle);


#endif
