/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: car_speed_control_uart_proto1.h
 *
 * Code generated for Simulink model 'car_speed_control_uart_proto1'.
 *
 * Model version                  : 1.51
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri May 23 17:59:32 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef car_speed_control_uart_proto1_h_
#define car_speed_control_uart_proto1_h_
#ifndef car_speed_control_uart_proto1_COMMON_INCLUDES_
#define car_speed_control_uart_proto1_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_mode.h"
#include "MW_SerialRead.h"
#include "MW_SerialWrite.h"
#endif                      /* car_speed_control_uart_proto1_COMMON_INCLUDES_ */

#include "car_speed_control_uart_proto1_types.h"
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

#define car_speed_control_uart_proto1_M (car_speed_control_uart_proto_M)

/* Block signals (default storage) */
typedef struct {
  real_T error;                        /* '<Root>/Add' */
  real_T error_j;                      /* '<Root>/Add1' */
  real_T speed_L;                      /* '<Root>/Arduino Input2' */
  real_T speed_R;                      /* '<Root>/Arduino Input2' */
  real_T v_target;                     /* '<Root>/Arduino Input2' */
  uint8_T SerialReceive1_o1;           /* '<Root>/Serial Receive1' */
  uint8_T SerialReceive1_o2;           /* '<Root>/Serial Receive1' */
  uint8_T slope;                       /* '<Root>/Arduino Input2' */
  int8_T steer;                        /* '<Root>/Arduino Input2' */
  boolean_T valid;                     /* '<Root>/Arduino Input2' */
  boolean_T ready;                     /* '<Root>/Arduino Input1' */
} B_car_speed_control_uart_prot_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_int_d_T obj; /* '<S3>/Serial Transmit2' */
  codertarget_arduinobase_inter_T obj_e;/* '<Root>/Serial Receive1' */
  real_T TimeStampA;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeA;                 /* '<Root>/Derivative1' */
  real_T TimeStampB;                   /* '<Root>/Derivative1' */
  real_T LastUAtTimeB;                 /* '<Root>/Derivative1' */
  real_T TmpRTBAtSubsystemInport1_Buffer;/* synthesized block */
  real_T TimeStampA_l;                 /* '<Root>/Derivative2' */
  real_T LastUAtTimeA_k;               /* '<Root>/Derivative2' */
  real_T TimeStampB_i;                 /* '<Root>/Derivative2' */
  real_T LastUAtTimeB_o;               /* '<Root>/Derivative2' */
  real_T TmpRTBAtSubsystemInport2_Buffer;/* synthesized block */
  real_T p_speed_L;                    /* '<Root>/Arduino Input2' */
  real_T p_speed_R;                    /* '<Root>/Arduino Input2' */
  real_T p_v_target;                   /* '<Root>/Arduino Input2' */
  real_T count;                        /* '<Root>/Arduino Input1' */
  int8_T p_steer;                      /* '<Root>/Arduino Input2' */
  uint8_T p_slope;                     /* '<Root>/Arduino Input2' */
  uint8_T buffer[10];                  /* '<Root>/Arduino Input1' */
  boolean_T p_valid;                   /* '<Root>/Arduino Input2' */
  boolean_T collecting;                /* '<Root>/Arduino Input1' */
} DW_car_speed_control_uart_pro_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
} X_car_speed_control_uart_prot_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
} XDot_car_speed_control_uart_p_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<Root>/Integrator1' */
} XDis_car_speed_control_uart_p_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (default storage) */
struct P_car_speed_control_uart_prot_T_ {
  real_T Kd_Gain;                      /* Expression: 0
                                        * Referenced by: '<Root>/Kd'
                                        */
  real_T Kp_Gain;                      /* Expression: 2
                                        * Referenced by: '<Root>/Kp'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<Root>/Integrator'
                                        */
  real_T Ki_Gain;                      /* Expression: 0
                                        * Referenced by: '<Root>/Ki'
                                        */
  real_T Gain_Gain;                    /* Expression: 0.1
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Kd1_Gain;                     /* Expression: 0
                                        * Referenced by: '<Root>/Kd1'
                                        */
  real_T Kp1_Gain;                     /* Expression: 2
                                        * Referenced by: '<Root>/Kp1'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<Root>/Integrator1'
                                        */
  real_T Ki1_Gain;                     /* Expression: 0
                                        * Referenced by: '<Root>/Ki1'
                                        */
  real_T Gain1_Gain;                   /* Expression: 0.1
                                        * Referenced by: '<Root>/Gain1'
                                        */
  int8_T V_gain_Gain;                  /* Computed Parameter: V_gain_Gain
                                        * Referenced by: '<Root>/V_gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_car_speed_control_uar_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  X_car_speed_control_uart_prot_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_car_speed_control_uart_p_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[3][2];
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
extern P_car_speed_control_uart_prot_T car_speed_control_uart_proto1_P;

/* Block signals (default storage) */
extern B_car_speed_control_uart_prot_T car_speed_control_uart_proto1_B;

/* Continuous states (default storage) */
extern X_car_speed_control_uart_prot_T car_speed_control_uart_proto1_X;

/* Disabled states (default storage) */
extern XDis_car_speed_control_uart_p_T car_speed_control_uart_pro_XDis;

/* Block states (default storage) */
extern DW_car_speed_control_uart_pro_T car_speed_control_uart_proto_DW;

/* External function called from main */
extern void car_speed_control_uart_proto1_SetEventsForThisBaseStep(boolean_T
  *eventFlags);

/* Model entry point functions */
extern void car_speed_control_uart_proto1_initialize(void);
extern void car_speed_control_uart_proto1_step0(void);
extern void car_speed_control_uart_proto1_step2(void);/* Sample time: [0.1s, 0.0s] */
extern void car_speed_control_uart_proto1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_car_speed_control_ua_T *const car_speed_control_uart_proto_M;
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
 * '<Root>' : 'car_speed_control_uart_proto1'
 * '<S1>'   : 'car_speed_control_uart_proto1/Arduino Input1'
 * '<S2>'   : 'car_speed_control_uart_proto1/Arduino Input2'
 * '<S3>'   : 'car_speed_control_uart_proto1/Subsystem'
 * '<S4>'   : 'car_speed_control_uart_proto1/Subsystem/Arduino output1'
 */
#endif                                 /* car_speed_control_uart_proto1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
