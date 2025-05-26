/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model1_private.h
 *
 * Code generated for Simulink model 'model1'.
 *
 * Model version                  : 1.148
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon May 26 18:17:13 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef model1_private_h_
#define model1_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "model1.h"
#include "model1_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T rt_roundd_snf(real_T u);
extern int16_T div_nde_s16_floor(int16_T numerator, int16_T denominator);
extern void model1_MATLABFunction1_Init(DW_MATLABFunction1_model1_T *localDW);
extern void model1_MATLABFunction1(uint16_T rtu_u, real_T *rty_y,
  DW_MATLABFunction1_model1_T *localDW);

/* private model entry point functions */
extern void model1_derivatives(void);

#endif                                 /* model1_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
