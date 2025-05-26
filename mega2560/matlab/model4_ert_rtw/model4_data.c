/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model4_data.c
 *
 * Code generated for Simulink model 'model4'.
 *
 * Model version                  : 1.173
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon May 26 21:13:55 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "model4.h"

/* Block parameters (default storage) */
P_model4_T model4_P = {
  /* Expression: 6
   * Referenced by: '<Root>/steer_gain'
   */
  6.0,

  /* Expression: 0
   * Referenced by: '<Root>/Kd'
   */
  0.0,

  /* Expression: 2
   * Referenced by: '<Root>/Kp'
   */
  2.0,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator'
   */
  0.0,

  /* Expression: 0.5
   * Referenced by: '<Root>/Ki'
   */
  0.5,

  /* Computed Parameter: TransferFcn1_A
   * Referenced by: '<Root>/Transfer Fcn1'
   */
  -1.0,

  /* Computed Parameter: TransferFcn1_C
   * Referenced by: '<Root>/Transfer Fcn1'
   */
  1.0,

  /* Expression: -300
   * Referenced by: '<Root>/Constant'
   */
  -300.0,

  /* Expression: 300
   * Referenced by: '<Root>/Constant1'
   */
  300.0,

  /* Expression: 2
   * Referenced by: '<Root>/Kp1'
   */
  2.0,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator1'
   */
  0.0,

  /* Expression: 0.5
   * Referenced by: '<Root>/Ki1'
   */
  0.5,

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<Root>/Transfer Fcn'
   */
  -1.0,

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<Root>/Transfer Fcn'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Kd1'
   */
  0.0,

  /* Computed Parameter: slope_gain_Gain
   * Referenced by: '<Root>/slope_gain'
   */
  80
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
