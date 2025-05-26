/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: car_speed_control_uart_test.h
 *
 * Code generated for Simulink model 'car_speed_control_uart_test'.
 *
 * Model version                  : 1.44
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri May 23 13:24:51 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef car_speed_control_uart_test_h_
#define car_speed_control_uart_test_h_
#ifndef car_speed_control_uart_test_COMMON_INCLUDES_
#define car_speed_control_uart_test_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_SerialRead.h"
#include "MW_SerialWrite.h"
#endif                        /* car_speed_control_uart_test_COMMON_INCLUDES_ */

#include "car_speed_control_uart_test_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include <string.h>
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals (default storage) */
typedef struct {
  real_T TmpRTBAterrorInport1;         /* '<Root>/Gain2' */
  real_T TmpRTBAtSumInport1;           /* '<Root>/Kp' */
  real_T error;                        /* '<Root>/Add' */
  real_T error_g;                      /* '<Root>/Add' */
} B_car_speed_control_uart_test_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_int_e_T obj; /* '<Root>/Serial Transmit1' */
  codertarget_arduinobase_inter_T obj_b;/* '<Root>/Serial Receive' */
  real_T TmpRTBAterrorInport1_Buffer0; /* synthesized block */
  real_T TmpRTBAtSumInport1_Buffer0;   /* synthesized block */
  real_T TmpRTBAtDerivative1Inport1_Buff;/* synthesized block */
  real_T TimeStampA;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative1' */
  real_T TimeStampB;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative1' */
  real_T TmpRTBAtIntegratorInport1_Buffe;/* synthesized block */
} DW_car_speed_control_uart_tes_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
} X_car_speed_control_uart_test_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
} XDot_car_speed_control_uart_t_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
} XDis_car_speed_control_uart_t_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (default storage) */
struct P_car_speed_control_uart_test_T_ {
  real_T TmpRTBAterrorInport1_InitialCon;/* Expression: 0
                                          * Referenced by:
                                          */
  real_T TmpRTBAtSumInport1_InitialCondi;/* Expression: 0
                                          * Referenced by:
                                          */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<Root>/Integrator'
                                        */
  real_T Ki_Gain;                      /* Expression: 0
                                        * Referenced by: '<Root>/Ki'
                                        */
  real_T TmpRTBAtDerivative1Inport1_Init;/* Expression: 0
                                          * Referenced by:
                                          */
  real_T Kd_Gain;                      /* Expression: 0
                                        * Referenced by: '<Root>/Kd'
                                        */
  real_T Constant1_Value;              /* Expression: 2
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T TmpRTBAtIntegratorInport1_Initi;/* Expression: 0
                                          * Referenced by:
                                          */
  real_T Gain2_Gain;                   /* Expression: 0
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T Kp_Gain;                      /* Expression: 400
                                        * Referenced by: '<Root>/Kp'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_car_speed_control_uar_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_car_speed_control_uart_test_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_car_speed_control_uart_t_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[1];
  real_T odeF[3][1];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    struct {
      boolean_T TID1_2;
    } RateInteraction;

    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block parameters (default storage) */
extern P_car_speed_control_uart_test_T car_speed_control_uart_test_P;

/* Block signals (default storage) */
extern B_car_speed_control_uart_test_T car_speed_control_uart_test_B;

/* Continuous states (default storage) */
extern X_car_speed_control_uart_test_T car_speed_control_uart_test_X;

/* Disabled states (default storage) */
extern XDis_car_speed_control_uart_t_T car_speed_control_uart_tes_XDis;

/* Block states (default storage) */
extern DW_car_speed_control_uart_tes_T car_speed_control_uart_test_DW;

/* External function called from main */
extern void car_speed_control_uart_test_SetEventsForThisBaseStep(boolean_T
  *eventFlags);

/* Model entry point functions */
extern void car_speed_control_uart_test_initialize(void);
extern void car_speed_control_uart_test_step0(void);
extern void car_speed_control_uart_test_step2(void);/* Sample time: [1.0s, 0.0s] */
extern void car_speed_control_uart_test_terminate(void);

/* Real-time Model object */
extern RT_MODEL_car_speed_control_ua_T *const car_speed_control_uart_test_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Display1' : Unused code path elimination
 * Block '<Root>/Display2' : Unused code path elimination
 * Block '<Root>/Display3' : Unused code path elimination
 * Block '<Root>/Display4' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 */

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
 * '<Root>' : 'car_speed_control_uart_test'
 * '<S1>'   : 'car_speed_control_uart_test/Arduino Input'
 * '<S2>'   : 'car_speed_control_uart_test/Arduino output'
 * '<S3>'   : 'car_speed_control_uart_test/Chart'
 */
#endif                                 /* car_speed_control_uart_test_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
