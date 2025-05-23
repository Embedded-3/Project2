/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: control_wiht_motor_data.c
 *
 * Code generated for Simulink model 'control_wiht_motor'.
 *
 * Model version                  : 1.44
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu May 22 18:17:01 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "control_wiht_motor.h"

/* Block parameters (default storage) */
P_control_wiht_motor_T control_wiht_motor_P = {
  /* Mask Parameter: DetectFallNegative_vinit
   * Referenced by: '<S2>/Delay Input1'
   */
  false,

  /* Mask Parameter: DetectRisePositive_vinit
   * Referenced by: '<S3>/Delay Input1'
   */
  false,

  /* Expression: 3
   * Referenced by: '<Root>/v_target(cm//s)'
   */
  3.0,

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<Root>/Transfer Fcn'
   */
  -1.0,

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<Root>/Transfer Fcn'
   */
  1.0,

  /* Expression: 10
   * Referenced by: '<Root>/Unit Delay'
   */
  10.0,

  /* Expression: 0.106359
   * Referenced by: '<Root>/Gain1'
   */
  0.106359,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator'
   */
  0.0,

  /* Expression: 100
   * Referenced by: '<Root>/Constant'
   */
  100.0,

  /* Computed Parameter: Constant_Value_o
   * Referenced by: '<S5>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_m
   * Referenced by: '<S6>/Constant'
   */
  false
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
