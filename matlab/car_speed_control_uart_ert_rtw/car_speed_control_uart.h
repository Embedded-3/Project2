/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: car_speed_control_uart.h
 *
 * Code generated for Simulink model 'car_speed_control_uart'.
 *
 * Model version                  : 1.29
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu May 22 19:48:34 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef car_speed_control_uart_h_
#define car_speed_control_uart_h_
#ifndef car_speed_control_uart_COMMON_INCLUDES_
#define car_speed_control_uart_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_SerialRead.h"
#include "MW_SerialWrite.h"
#endif                             /* car_speed_control_uart_COMMON_INCLUDES_ */

#include "car_speed_control_uart_types.h"
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_inter_T obj; /* '<Root>/Serial Transmit1' */
} DW_car_speed_control_uart_T;

/* Parameters (default storage) */
struct P_car_speed_control_uart_T_ {
  real_T Constant2_Value;              /* Expression: 4
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T Constant1_Value;              /* Expression: 2
                                        * Referenced by: '<Root>/Constant1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_car_speed_control_uar_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P_car_speed_control_uart_T car_speed_control_uart_P;

/* Block states (default storage) */
extern DW_car_speed_control_uart_T car_speed_control_uart_DW;

/* Model entry point functions */
extern void car_speed_control_uart_initialize(void);
extern void car_speed_control_uart_step(void);
extern void car_speed_control_uart_terminate(void);

/* Real-time Model object */
extern RT_MODEL_car_speed_control_ua_T *const car_speed_control_uart_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'car_speed_control_uart'
 * '<S1>'   : 'car_speed_control_uart/Arduino output'
 */
#endif                                 /* car_speed_control_uart_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
