/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model1.h
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

#ifndef model1_h_
#define model1_h_
#ifndef model1_COMMON_INCLUDES_
#define model1_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_mode.h"
#include "MW_SerialRead.h"
#include "MW_SerialWrite.h"
#endif                                 /* model1_COMMON_INCLUDES_ */

#include "model1_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include <string.h>
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

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
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

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
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

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
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

/* Block states (default storage) for system '<Root>/MATLAB Function1' */
typedef struct {
  int32_T sfEvent;                     /* '<Root>/MATLAB Function1' */
  boolean_T doneDoubleBufferReInit;    /* '<Root>/MATLAB Function1' */
} DW_MATLABFunction1_model1_T;

/* Block signals (default storage) */
typedef struct {
  real_T steer_gain;                   /* '<Root>/steer_gain' */
  real_T slope_gain;                   /* '<Root>/slope_gain' */
  real_T DotProduct;                   /* '<Root>/Dot Product' */
  real_T Kp;                           /* '<Root>/Kp' */
  real_T Sum;                          /* '<Root>/Sum' */
  real_T DotProduct1;                  /* '<Root>/Dot Product1' */
  real_T Kp1;                          /* '<Root>/Kp1' */
  real_T Sum1;                         /* '<Root>/Sum1' */
  real_T Kd1;                          /* '<Root>/Kd1' */
  real_T Kd;                           /* '<Root>/Kd' */
  real_T speed_L;                      /* '<Root>/Arduino Input2' */
  real_T speed_R;                      /* '<Root>/Arduino Input2' */
  real_T slope;                        /* '<Root>/Arduino Input2' */
  real_T steer;                        /* '<Root>/Arduino Input2' */
  uint16_T v_target;                   /* '<Root>/Arduino Input2' */
  int16_T byteL1;                      /* '<Root>/MATLAB Function' */
  int16_T byteL2;                      /* '<Root>/MATLAB Function' */
  int16_T byteR1;                      /* '<Root>/MATLAB Function' */
  int16_T byteR2;                      /* '<Root>/MATLAB Function' */
  uint8_T SerialReceive1_o1;           /* '<Root>/Serial Receive1' */
  uint8_T crc;                         /* '<Root>/Arduino Input2' */
  boolean_T valid;                     /* '<Root>/Arduino Input2' */
} B_model1_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_int_l_T obj; /* '<S6>/Serial Transmit2' */
  codertarget_arduinobase_inter_T obj_e;/* '<Root>/Serial Receive1' */
  real_T TimeStampA;                   /* '<Root>/Derivative2' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative2' */
  real_T TimeStampB;                   /* '<Root>/Derivative2' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative2' */
  real_T TimeStampA_i;                 /* '<Root>/Derivative1' */
  real_T LastUAtTimeA_e;               /* '<Root>/Derivative1' */
  real_T TimeStampB_a;                 /* '<Root>/Derivative1' */
  real_T LastUAtTimeB_c;               /* '<Root>/Derivative1' */
  real_T p_speed_L;                    /* '<Root>/Arduino Input2' */
  real_T p_speed_R;                    /* '<Root>/Arduino Input2' */
  real_T p_slope;                      /* '<Root>/Arduino Input2' */
  real_T p_steer;                      /* '<Root>/Arduino Input2' */
  real_T count;                        /* '<Root>/Arduino Input1' */
  int16_T byteL1_Buffer;               /* synthesized block */
  int16_T byteL2_Buffer;               /* synthesized block */
  uint16_T p_v_target;                 /* '<Root>/Arduino Input2' */
  uint8_T p_crc;                       /* '<Root>/Arduino Input2' */
  uint8_T buffer[10];                  /* '<Root>/Arduino Input1' */
  boolean_T p_valid;                   /* '<Root>/Arduino Input2' */
  boolean_T collecting;                /* '<Root>/Arduino Input1' */
  DW_MATLABFunction1_model1_T sf_MATLABFunction2;/* '<Root>/MATLAB Function2' */
  DW_MATLABFunction1_model1_T sf_MATLABFunction1;/* '<Root>/MATLAB Function1' */
} DW_model1_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T TransferFcn1_CSTATE;          /* '<Root>/Transfer Fcn1' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
} X_model1_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T TransferFcn1_CSTATE;          /* '<Root>/Transfer Fcn1' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
} XDot_model1_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T TransferFcn1_CSTATE;       /* '<Root>/Transfer Fcn1' */
  boolean_T Integrator1_CSTATE;        /* '<Root>/Integrator1' */
  boolean_T TransferFcn_CSTATE;        /* '<Root>/Transfer Fcn' */
} XDis_model1_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (default storage) */
struct P_model1_T_ {
  real_T steer_gain_Gain;              /* Expression: 0
                                        * Referenced by: '<Root>/steer_gain'
                                        */
  real_T slope_gain_Gain;              /* Expression: 5
                                        * Referenced by: '<Root>/slope_gain'
                                        */
  real_T Kp_Gain;                      /* Expression: 2
                                        * Referenced by: '<Root>/Kp'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<Root>/Integrator'
                                        */
  real_T Ki_Gain;                      /* Expression: 1
                                        * Referenced by: '<Root>/Ki'
                                        */
  real_T TransferFcn1_A;               /* Computed Parameter: TransferFcn1_A
                                        * Referenced by: '<Root>/Transfer Fcn1'
                                        */
  real_T TransferFcn1_C;               /* Computed Parameter: TransferFcn1_C
                                        * Referenced by: '<Root>/Transfer Fcn1'
                                        */
  real_T Kp1_Gain;                     /* Expression: 2
                                        * Referenced by: '<Root>/Kp1'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<Root>/Integrator1'
                                        */
  real_T Ki1_Gain;                     /* Expression: 1
                                        * Referenced by: '<Root>/Ki1'
                                        */
  real_T TransferFcn_A;                /* Computed Parameter: TransferFcn_A
                                        * Referenced by: '<Root>/Transfer Fcn'
                                        */
  real_T TransferFcn_C;                /* Computed Parameter: TransferFcn_C
                                        * Referenced by: '<Root>/Transfer Fcn'
                                        */
  real_T Constant_Value;               /* Expression: -500
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 500
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Kd1_Gain;                     /* Expression: 0
                                        * Referenced by: '<Root>/Kd1'
                                        */
  real_T Kd_Gain;                      /* Expression: 0
                                        * Referenced by: '<Root>/Kd'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_model1_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  X_model1_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_model1_T *contStateDisabled;
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
    uint32_T checksums[4];
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTick2;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    struct {
      boolean_T TID1_2;
    } RateInteraction;

    time_T tStart;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block parameters (default storage) */
extern P_model1_T model1_P;

/* Block signals (default storage) */
extern B_model1_T model1_B;

/* Continuous states (default storage) */
extern X_model1_T model1_X;

/* Disabled states (default storage) */
extern XDis_model1_T model1_XDis;

/* Block states (default storage) */
extern DW_model1_T model1_DW;

/* External function called from main */
extern void model1_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void model1_initialize(void);
extern void model1_step0(void);
extern void model1_step2(void);        /* Sample time: [0.05s, 0.0s] */
extern void model1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_model1_T *const model1_M;
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
 * '<Root>' : 'model1'
 * '<S1>'   : 'model1/Arduino Input1'
 * '<S2>'   : 'model1/Arduino Input2'
 * '<S3>'   : 'model1/MATLAB Function'
 * '<S4>'   : 'model1/MATLAB Function1'
 * '<S5>'   : 'model1/MATLAB Function2'
 * '<S6>'   : 'model1/Subsystem'
 * '<S7>'   : 'model1/Subsystem/Arduino output1'
 */
#endif                                 /* model1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
