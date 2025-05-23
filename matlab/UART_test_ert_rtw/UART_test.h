/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: UART_test.h
 *
 * Code generated for Simulink model 'UART_test'.
 *
 * Model version                  : 1.87
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri May 23 16:19:15 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef UART_test_h_
#define UART_test_h_
#ifndef UART_test_COMMON_INCLUDES_
#define UART_test_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_SerialRead.h"
#include "MW_SerialWrite.h"
#endif                                 /* UART_test_COMMON_INCLUDES_ */

#include "UART_test_types.h"
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
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
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals (default storage) */
typedef struct {
  real_T speed_L;                      /* '<Root>/Arduino Input2' */
  real_T speed_R;                      /* '<Root>/Arduino Input2' */
  uint8_T SerialReceive1_o1;           /* '<Root>/Serial Receive1' */
  uint8_T SerialReceive1_o2;           /* '<Root>/Serial Receive1' */
  uint8_T v_target;                    /* '<Root>/Arduino Input2' */
  uint8_T slope;                       /* '<Root>/Arduino Input2' */
  int8_T steer;                        /* '<Root>/Arduino Input2' */
  boolean_T valid;                     /* '<Root>/Arduino Input2' */
  boolean_T ready;                     /* '<Root>/Arduino Input1' */
} B_UART_test_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_int_h_T obj; /* '<S3>/Serial Transmit2' */
  codertarget_arduinobase_inter_T obj_d;/* '<Root>/Serial Receive1' */
  real_T p_speed_L;                    /* '<Root>/Arduino Input2' */
  real_T p_speed_R;                    /* '<Root>/Arduino Input2' */
  real_T count;                        /* '<Root>/Arduino Input1' */
  int8_T p_steer;                      /* '<Root>/Arduino Input2' */
  uint8_T p_v_target;                  /* '<Root>/Arduino Input2' */
  uint8_T p_slope;                     /* '<Root>/Arduino Input2' */
  uint8_T buffer[8];                   /* '<Root>/Arduino Input1' */
  boolean_T p_valid;                   /* '<Root>/Arduino Input2' */
  boolean_T collecting;                /* '<Root>/Arduino Input1' */
} DW_UART_test_T;

/* Parameters (default storage) */
struct P_UART_test_T_ {
  real_T Constant_Value;               /* Expression: 10
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 20
                                        * Referenced by: '<S3>/Constant1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_UART_test_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
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
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint8_T TID[2];
    } TaskCounters;

    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_UART_test_T UART_test_P;

/* Block signals (default storage) */
extern B_UART_test_T UART_test_B;

/* Block states (default storage) */
extern DW_UART_test_T UART_test_DW;

/* External function called from main */
extern void UART_test_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void UART_test_initialize(void);
extern void UART_test_step0(void);     /* Sample time: [0.01s, 0.0s] */
extern void UART_test_step1(void);     /* Sample time: [1.0s, 0.0s] */
extern void UART_test_terminate(void);

/* Real-time Model object */
extern RT_MODEL_UART_test_T *const UART_test_M;
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
 * '<Root>' : 'UART_test'
 * '<S1>'   : 'UART_test/Arduino Input1'
 * '<S2>'   : 'UART_test/Arduino Input2'
 * '<S3>'   : 'UART_test/Subsystem'
 * '<S4>'   : 'UART_test/Subsystem/Arduino output1'
 */
#endif                                 /* UART_test_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
