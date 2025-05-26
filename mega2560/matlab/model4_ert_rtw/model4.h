/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model4.h
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

#ifndef model4_h_
#define model4_h_
#ifndef model4_COMMON_INCLUDES_
#define model4_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_SerialRead.h"
#include "MW_SerialWrite.h"
#endif                                 /* model4_COMMON_INCLUDES_ */

#include "model4_types.h"
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
  uint8_T u[10];
  real_T DotProduct;                   /* '<Root>/Dot Product' */
  real_T Kd;                           /* '<Root>/Kd' */
  real_T Kp;                           /* '<Root>/Kp' */
  real_T DotProduct1;                  /* '<Root>/Dot Product1' */
  real_T Kp1;                          /* '<Root>/Kp1' */
  real_T Kd1;                          /* '<Root>/Kd1' */
  real_T y;                            /* '<Root>/MATLAB Function3' */
  real_T y_j;                          /* '<Root>/MATLAB Function2' */
} B_model4_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_int_h_T obj; /* '<S6>/Serial Transmit2' */
  codertarget_arduinobase_inter_T obj_e;/* '<Root>/Serial Receive1' */
  real_T TimeStampA;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative1' */
  real_T TimeStampB;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative1' */
  real_T TimeStampA_l;                 /* '<Root>/Derivative2' */
  real_T LastUAtTimeA_k;               /* '<Root>/Derivative2' */
  real_T TimeStampB_i;                 /* '<Root>/Derivative2' */
  real_T LastUAtTimeB_o;               /* '<Root>/Derivative2' */
  real_T p_speed_L;                    /* '<Root>/Arduino Input2' */
  real_T p_speed_R;                    /* '<Root>/Arduino Input2' */
  real_T count;                        /* '<Root>/Arduino Input1' */
  uint16_T p_v_target;                 /* '<Root>/Arduino Input2' */
  int8_T p_slope;                      /* '<Root>/Arduino Input2' */
  int8_T p_steer;                      /* '<Root>/Arduino Input2' */
  uint8_T byteL1_Buffer;               /* synthesized block */
  uint8_T byteL2_Buffer;               /* synthesized block */
  uint8_T byteR1_Buffer;               /* synthesized block */
  uint8_T byteR2_Buffer;               /* synthesized block */
  uint8_T buffer[10];                  /* '<Root>/Arduino Input1' */
  boolean_T collecting;                /* '<Root>/Arduino Input1' */
} DW_model4_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T TransferFcn1_CSTATE;          /* '<Root>/Transfer Fcn1' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
} X_model4_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T TransferFcn1_CSTATE;          /* '<Root>/Transfer Fcn1' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
} XDot_model4_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T TransferFcn1_CSTATE;       /* '<Root>/Transfer Fcn1' */
  boolean_T Integrator1_CSTATE;        /* '<Root>/Integrator1' */
  boolean_T TransferFcn_CSTATE;        /* '<Root>/Transfer Fcn' */
} XDis_model4_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (default storage) */
struct P_model4_T_ {
  real_T steer_gain_Gain;              /* Expression: 6
                                        * Referenced by: '<Root>/steer_gain'
                                        */
  real_T Kd_Gain;                      /* Expression: 0
                                        * Referenced by: '<Root>/Kd'
                                        */
  real_T Kp_Gain;                      /* Expression: 2
                                        * Referenced by: '<Root>/Kp'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<Root>/Integrator'
                                        */
  real_T Ki_Gain;                      /* Expression: 0.5
                                        * Referenced by: '<Root>/Ki'
                                        */
  real_T TransferFcn1_A;               /* Computed Parameter: TransferFcn1_A
                                        * Referenced by: '<Root>/Transfer Fcn1'
                                        */
  real_T TransferFcn1_C;               /* Computed Parameter: TransferFcn1_C
                                        * Referenced by: '<Root>/Transfer Fcn1'
                                        */
  real_T Constant_Value;               /* Expression: -300
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 300
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Kp1_Gain;                     /* Expression: 2
                                        * Referenced by: '<Root>/Kp1'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<Root>/Integrator1'
                                        */
  real_T Ki1_Gain;                     /* Expression: 0.5
                                        * Referenced by: '<Root>/Ki1'
                                        */
  real_T TransferFcn_A;                /* Computed Parameter: TransferFcn_A
                                        * Referenced by: '<Root>/Transfer Fcn'
                                        */
  real_T TransferFcn_C;                /* Computed Parameter: TransferFcn_C
                                        * Referenced by: '<Root>/Transfer Fcn'
                                        */
  real_T Kd1_Gain;                     /* Expression: 0
                                        * Referenced by: '<Root>/Kd1'
                                        */
  int8_T slope_gain_Gain;              /* Computed Parameter: slope_gain_Gain
                                        * Referenced by: '<Root>/slope_gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_model4_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_model4_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_model4_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[4];
  real_T odeF[3][4];
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
extern P_model4_T model4_P;

/* Block signals (default storage) */
extern B_model4_T model4_B;

/* Continuous states (default storage) */
extern X_model4_T model4_X;

/* Disabled states (default storage) */
extern XDis_model4_T model4_XDis;

/* Block states (default storage) */
extern DW_model4_T model4_DW;

/* External function called from main */
extern void model4_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void model4_initialize(void);
extern void model4_step0(void);
extern void model4_step2(void);        /* Sample time: [0.1s, 0.0s] */
extern void model4_terminate(void);

/* Real-time Model object */
extern RT_MODEL_model4_T *const model4_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Display1' : Unused code path elimination
 * Block '<Root>/Display10' : Unused code path elimination
 * Block '<Root>/Display11' : Unused code path elimination
 * Block '<Root>/Display12' : Unused code path elimination
 * Block '<Root>/Display13' : Unused code path elimination
 * Block '<Root>/Display14' : Unused code path elimination
 * Block '<Root>/Display15' : Unused code path elimination
 * Block '<Root>/Display16' : Unused code path elimination
 * Block '<Root>/Display2' : Unused code path elimination
 * Block '<Root>/Display3' : Unused code path elimination
 * Block '<Root>/Display4' : Unused code path elimination
 * Block '<Root>/Display5' : Unused code path elimination
 * Block '<Root>/Display6' : Unused code path elimination
 * Block '<Root>/Display7' : Unused code path elimination
 * Block '<Root>/Display8' : Unused code path elimination
 * Block '<Root>/Display9' : Unused code path elimination
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
 * '<Root>' : 'model4'
 * '<S1>'   : 'model4/Arduino Input1'
 * '<S2>'   : 'model4/Arduino Input2'
 * '<S3>'   : 'model4/MATLAB Function1'
 * '<S4>'   : 'model4/MATLAB Function2'
 * '<S5>'   : 'model4/MATLAB Function3'
 * '<S6>'   : 'model4/Subsystem'
 * '<S7>'   : 'model4/Subsystem/Arduino output1'
 */
#endif                                 /* model4_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
