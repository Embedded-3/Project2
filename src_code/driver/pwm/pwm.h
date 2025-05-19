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
#define FrontRight          IfxGtm_ATOM0_0_TOUT0_P02_0_OUT // d2      // D2
#define FrontLeft           IfxGtm_ATOM0_1_TOUT1_P02_1_OUT //d3 //IfxGtm_ATOM1_1_TOUT1_P02_1_OUT //IfxGtm_ATOM0_0_TOUT9_P00_0_OUT      // D25
#define RearRight           IfxGtm_ATOM0_3_TOUT3_P02_3_OUT //d5 //IfxGtm_ATOM0_0_TOUT53_P21_2_OUT     // D50
#define RearLeft            IfxGtm_ATOM0_4_TOUT4_P02_4_OUT //d6 //IfxGtm_ATOM0_0_TOUT8_P02_8_OUT      // D51

/*
IfxGtm_ATOM0_0_TOUT0_P02_0_OUT      // D2
IfxGtm_ATOM0_0_TOUT9_P00_0_OUT      // D25
IfxGtm_ATOM0_0_TOUT53_P21_2_OUT     // D50
IfxGtm_ATOM0_0_TOUT8_P02_8_OUT      // D51
*/

#define PWM_PERIOD           20000                                   /* PWM period for the TOM                       */
#define DUTY_FRONT_RIGHT     20000 //12000 //10000                                   /* PWM duty cycle for the TOM                    */
#define DUTY_FRONT_LEFT      3500 //5000 //                                   /* PWM duty cycle for the TOM                    */
#define DUTY_REAR_RIGHT      20000 //12000 //10000                                   /* PWM duty cycle for the TOM                    */
#define DUTY_REAR_LEFT       3500 //5000 //10000                                   /* PWM duty cycle for the TOM                    */

typedef enum WHEEL{
    FR = 0,
    FL = 1,
    RR = 2,
    RL = 3,
} e_wheel_t;

/*
IfxGtm_ATOM0_0_TOUT0_P02_0_OUT // D2
IfxGtm_ATOM0_0_TOUT48_P22_1_OUT SPI connector 1
IfxGtm_ATOM0_0_TOUT53_P21_2_OUT // D50
IfxGtm_ATOM0_0_TOUT85_P14_5_OUT // 없
IfxGtm_ATOM0_0_TOUT8_P02_8_OUT // d51
IfxGtm_ATOM0_0_TOUT9_P00_0_OUT // d25
*/


void initPwm(void);
void initFrontRightPwm(void);
void initFrontLeftPwm(void);
void initRearRightPwm(void);
void initRearLeftPwm(void);
void startPwm(void);



#endif
