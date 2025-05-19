// pwm.c
#include "pwm.h"

#define CLK_FREQ           1000000.0f // 1000000.0f

//Front Right
IfxGtm_Atom_Pwm_Config g_FrontRightConfig;
IfxGtm_Atom_Pwm_Driver g_FrontRightDriver;

//Front Left
IfxGtm_Atom_Pwm_Config g_FrontLeftConfig;
IfxGtm_Atom_Pwm_Driver g_FrontLeftDriver;

//Rear Right
IfxGtm_Atom_Pwm_Config g_RearRightConfig;
IfxGtm_Atom_Pwm_Driver g_RearRightDriver;

//Rear Left
IfxGtm_Atom_Pwm_Config g_RearLeftConfig;
IfxGtm_Atom_Pwm_Driver g_RearLeftDriver;

void initPwm(void){
    IfxGtm_enable(&MODULE_GTM); /* Enable GTM */
    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, CLK_FREQ);            /* Set the CMU clock 0 frequency    */
    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK0);                    /* Enable the CMU clock 0           */

    initFrontRightPwm();
    initFrontLeftPwm();
    initRearRightPwm();
    initRearLeftPwm();

}
void initFrontRightPwm(void){
    IfxGtm_Atom_Pwm_initConfig(&g_FrontRightConfig, &MODULE_GTM);                   /* Initialize default parameters    */

    g_FrontRightConfig.atom = FrontRight.atom;                                      /* Select the TOM                   */
    g_FrontRightConfig.atomChannel = FrontRight.channel;                            /* Select the channel               */
    g_FrontRightConfig.period = PWM_PERIOD;
    g_FrontRightConfig.dutyCycle = DUTY_FRONT_RIGHT;
    g_FrontRightConfig.pin.outputPin = &FrontRight;                                 /* Set the pin as output            */
    g_FrontRightConfig.synchronousUpdateEnabled = TRUE;                             /* Enable synchronous update        */

    IfxGtm_Atom_Pwm_init(&g_FrontRightDriver, &g_FrontRightConfig);                 /* Initialize the GTM TOM           */
}
void initFrontLeftPwm(void){
    IfxGtm_Atom_Pwm_initConfig(&g_FrontLeftConfig, &MODULE_GTM);                    /* Initialize default parameters    */

    g_FrontLeftConfig.atom = FrontLeft.atom;                                        /* Select the TOM                   */
    g_FrontLeftConfig.atomChannel = FrontLeft.channel;                              /* Select the channel               */
    g_FrontLeftConfig.period = PWM_PERIOD;
    g_FrontLeftConfig.dutyCycle = DUTY_FRONT_LEFT;
    g_FrontLeftConfig.pin.outputPin = &FrontLeft;                                   /* Set the pin as output            */
    g_FrontLeftConfig.synchronousUpdateEnabled = TRUE;                              /* Enable synchronous update        */

    IfxGtm_Atom_Pwm_init(&g_FrontLeftDriver, &g_FrontLeftConfig);                   /* Initialize the GTM TOM           */
}
void initRearRightPwm(void){
    IfxGtm_Atom_Pwm_initConfig(&g_RearRightConfig, &MODULE_GTM);                    /* Initialize default parameters    */

    g_RearRightConfig.atom = RearRight.atom;                                        /* Select the TOM                   */
    g_RearRightConfig.atomChannel = RearRight.channel;                              /* Select the channel               */
    g_RearRightConfig.period = PWM_PERIOD;
    g_RearRightConfig.dutyCycle = DUTY_REAR_RIGHT;
    g_RearRightConfig.pin.outputPin = &RearRight;                                   /* Set the pin as output            */
    g_RearRightConfig.synchronousUpdateEnabled = TRUE;                              /* Enable synchronous update        */

    IfxGtm_Atom_Pwm_init(&g_RearRightDriver, &g_RearRightConfig);                   /* Initialize the GTM TOM           */
}
void initRearLeftPwm(void){
    IfxGtm_Atom_Pwm_initConfig(&g_RearLeftConfig, &MODULE_GTM);                     /* Initialize default parameters    */

    g_RearLeftConfig.atom = RearLeft.atom;                                          /* Select the TOM                   */
    g_RearLeftConfig.atomChannel = RearLeft.channel;                                /* Select the channel               */
    g_RearLeftConfig.period = PWM_PERIOD;
    g_RearLeftConfig.dutyCycle = DUTY_REAR_LEFT;
    g_RearLeftConfig.pin.outputPin = &RearLeft;                                     /* Set the pin as output            */
    g_RearLeftConfig.synchronousUpdateEnabled = TRUE;                               /* Enable synchronous update        */

    IfxGtm_Atom_Pwm_init(&g_RearLeftDriver, &g_RearLeftConfig);                     /* Initialize the GTM TOM           */
}
void startPwm(void){
    IfxGtm_Atom_Pwm_start(&g_FrontLeftDriver, TRUE);                                /* Start the PWM                    */
    IfxGtm_Atom_Pwm_start(&g_FrontRightDriver, TRUE);                               /* Start the PWM                    */
    IfxGtm_Atom_Pwm_start(&g_RearLeftDriver, TRUE);                                 /* Start the PWM                    */
    IfxGtm_Atom_Pwm_start(&g_RearRightDriver, TRUE);                                /* Start the PWM                    */
}




