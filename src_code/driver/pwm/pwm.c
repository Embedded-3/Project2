// pwm.c
#include "pwm.h"

#define NUM_WHEELS 4

typedef struct {
    IfxGtm_Atom_Pwm_Config config;
    IfxGtm_Atom_Pwm_Driver driver;
    IfxGtm_Atom_ToutMap* pwmOut;
    uint32 dutyCycle;
} PwmWheel_t;

// Static function Definition
static void initWheelPwm(PwmWheel_t* wheel);
static void setDutyCycle(PwmWheel_t* wheel, const uint32 dutyCycle);

// Wheel instance declarations
PwmWheel_t pwmWheels[4] = {
    [FR] = { .pwmOut = &FrontRight, .dutyCycle = DEFAULT_DUTY_FRONT_RIGHT },
    [FL] = { .pwmOut = &FrontLeft,  .dutyCycle = DEFAULT_DUTY_FRONT_LEFT },
    [RR] = { .pwmOut = &RearRight,  .dutyCycle = DEFAULT_DUTY_REAR_RIGHT },
    [RL] = { .pwmOut = &RearLeft,   .dutyCycle = DEFAULT_DUTY_REAR_LEFT }
};

// User Func : PWM 초기화
void initPwm(void){
    IfxGtm_enable(&MODULE_GTM); /* Enable GTM */
    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, CLK_FREQ);            /* Set the CMU clock 0 frequency    */
    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK0);                    /* Enable the CMU clock 0           */

    for(int i = 0; i < NUM_WHEELS; i++){
        initWheelPwm(&pwmWheels[i]);
    }
}

// 휠마다 초기화
static void initWheelPwm(PwmWheel_t* wheel) {
    IfxGtm_Atom_Pwm_initConfig(&(wheel->config), &MODULE_GTM);
    wheel->config.atom = wheel->pwmOut->atom;
    wheel->config.atomChannel = wheel->pwmOut->channel;
    wheel->config.period = PWM_PERIOD;
    wheel->config.dutyCycle = wheel->dutyCycle;
    wheel->config.pin.outputPin = wheel->pwmOut;
    wheel->config.synchronousUpdateEnabled = TRUE;

    IfxGtm_Atom_Pwm_init(&(wheel->driver), &(wheel->config));
}

// User Func : PWM 시작
void startPwm(void){
    for (int i = 0; i < NUM_WHEELS; i++) {
        IfxGtm_Atom_Pwm_start(&(pwmWheels[i].driver), TRUE);
    }
}

// User Func : Duty조정
void setPwm(const e_Wheel_t whichWheel, uint32 dutyCycle) {
    if (whichWheel >= NUM_WHEELS) return;   // 4 바퀴 초과의 값

    if(dutyCycle >= PWM_PERIOD)  dutyCycle = PWM_PERIOD;
    else if(dutyCycle <= 0)      dutyCycle = 0;
    
    setDutyCycle(&pwmWheels[whichWheel], dutyCycle);
}

// 실제 Duty 조정
static void setDutyCycle(PwmWheel_t* wheel, const uint32 dutyCycle) {
    wheel->config.dutyCycle = dutyCycle;
    IfxGtm_Atom_Pwm_init(&(wheel->driver), &(wheel->config));
}
