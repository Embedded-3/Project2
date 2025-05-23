/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: UART_test.c
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

#include "UART_test.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <math.h>
#include "UART_test_private.h"
#include "rt_nonfinite.h"

/* Block signals (default storage) */
B_UART_test_T UART_test_B;

/* Block states (default storage) */
DW_UART_test_T UART_test_DW;

/* Real-time model */
static RT_MODEL_UART_test_T UART_test_M_;
RT_MODEL_UART_test_T *const UART_test_M = &UART_test_M_;

/* Forward declaration for local functions */
static real_T UART_test_mod(real_T x);
static real_T UART_test_mod_f(real_T x);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void UART_test_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(UART_test_M, 1));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (UART_test_M->Timing.TaskCounters.TID[1])++;
  if ((UART_test_M->Timing.TaskCounters.TID[1]) > 99) {/* Sample time: [1.0s, 0.0s] */
    UART_test_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Function for MATLAB Function: '<S3>/Arduino output1' */
static real_T UART_test_mod(real_T x)
{
  real_T r;
  if (rtIsNaN(x)) {
    r = (rtNaN);
  } else if (rtIsInf(x)) {
    r = (rtNaN);
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = fmod(x, 100.0);
    if (r == 0.0) {
      r = 0.0;
    } else if (r < 0.0) {
      r += 100.0;
    }
  }

  return r;
}

/* Function for MATLAB Function: '<S3>/Arduino output1' */
static real_T UART_test_mod_f(real_T x)
{
  real_T r;
  if (rtIsNaN(x)) {
    r = (rtNaN);
  } else if (rtIsInf(x)) {
    r = (rtNaN);
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = fmod(x, 256.0);
    if (r == 0.0) {
      r = 0.0;
    } else if (r < 0.0) {
      r += 256.0;
    }
  }

  return r;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function for TID0 */
void UART_test_step0(void)             /* Sample time: [0.01s, 0.0s] */
{
  int16_T i;
  uint8_T data_out[8];
  uint8_T tmp;

  {                                    /* Sample time: [0.01s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* MATLABSystem: '<Root>/Serial Receive1' */
  MW_Serial_read(1, 1U, &UART_test_B.SerialReceive1_o1,
                 &UART_test_B.SerialReceive1_o2, NULL, 0.0, NULL, 0.0);

  /* MATLAB Function: '<Root>/Arduino Input1' */
  UART_test_B.ready = false;
  for (i = 0; i < 8; i++) {
    data_out[i] = 0U;
  }

  if (UART_test_B.SerialReceive1_o2 == 1) {
    if (!UART_test_DW.collecting) {
      if (UART_test_B.SerialReceive1_o1 == 170) {
        UART_test_DW.buffer[0] = UART_test_B.SerialReceive1_o1;
        UART_test_DW.count = 1.0;
        UART_test_DW.collecting = true;
      }
    } else {
      UART_test_DW.count++;
      UART_test_DW.buffer[(int16_T)UART_test_DW.count - 1] =
        UART_test_B.SerialReceive1_o1;
      if (UART_test_DW.count == 8.0) {
        for (i = 0; i < 8; i++) {
          data_out[i] = UART_test_DW.buffer[i];
        }

        UART_test_B.ready = true;
        UART_test_DW.count = 0.0;
        UART_test_DW.collecting = false;
      }
    }
  }

  /* End of MATLAB Function: '<Root>/Arduino Input1' */

  /* MATLAB Function: '<Root>/Arduino Input2' */
  if (UART_test_B.ready) {
    UART_test_DW.p_valid = true;
    UART_test_DW.p_speed_L = data_out[1];
    UART_test_DW.p_speed_R = data_out[2];
    UART_test_DW.p_v_target = data_out[3];
    UART_test_DW.p_slope = data_out[4];
    tmp = data_out[5];
    if (data_out[5] > 127) {
      tmp = 127U;
    }

    UART_test_DW.p_steer = (int8_T)tmp;
  }

  UART_test_B.valid = UART_test_DW.p_valid;
  UART_test_B.speed_L = UART_test_DW.p_speed_L;
  UART_test_B.speed_R = UART_test_DW.p_speed_R;
  UART_test_B.v_target = UART_test_DW.p_v_target;
  UART_test_B.slope = UART_test_DW.p_slope;
  UART_test_B.steer = UART_test_DW.p_steer;

  /* End of MATLAB Function: '<Root>/Arduino Input2' */

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  UART_test_M->Timing.taskTime0 =
    ((time_T)(++UART_test_M->Timing.clockTick0)) * UART_test_M->Timing.stepSize0;
}

/* Model step function for TID1 */
void UART_test_step1(void)             /* Sample time: [1.0s, 0.0s] */
{
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  uint8_T frame[5];
  uint8_T varargin_10;
  uint8_T varargin_9;

  /* Outputs for Atomic SubSystem: '<Root>/Subsystem' */
  /* MATLAB Function: '<S3>/Arduino output1' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/Constant1'
   */
  tmp_1 = floor(UART_test_P.Constant_Value);
  if (tmp_1 < 256.0) {
    if (tmp_1 >= 0.0) {
      frame[0] = (uint8_T)tmp_1;
    } else {
      frame[0] = 0U;
    }
  } else {
    frame[0] = MAX_uint8_T;
  }

  tmp_0 = floor(UART_test_mod(UART_test_P.Constant_Value * 100.0));
  if (tmp_0 < 256.0) {
    if (tmp_0 >= 0.0) {
      frame[1] = (uint8_T)tmp_0;
    } else {
      frame[1] = 0U;
    }
  } else {
    frame[1] = MAX_uint8_T;
  }

  tmp_0 = floor(UART_test_P.Constant1_Value);
  if (tmp_0 < 256.0) {
    if (tmp_0 >= 0.0) {
      frame[2] = (uint8_T)tmp_0;
    } else {
      frame[2] = 0U;
    }
  } else {
    frame[2] = MAX_uint8_T;
  }

  tmp = floor(UART_test_mod(UART_test_P.Constant1_Value * 100.0));
  if (tmp < 256.0) {
    if (tmp >= 0.0) {
      frame[3] = (uint8_T)tmp;
    } else {
      frame[3] = 0U;
    }
  } else {
    frame[3] = MAX_uint8_T;
  }

  if (tmp_1 < 256.0) {
    if (tmp_1 >= 0.0) {
      varargin_9 = (uint8_T)tmp_1;
    } else {
      varargin_9 = 0U;
    }
  } else {
    varargin_9 = MAX_uint8_T;
  }

  if (tmp_0 < 256.0) {
    if (tmp_0 >= 0.0) {
      varargin_10 = (uint8_T)tmp_0;
    } else {
      varargin_10 = 0U;
    }
  } else {
    varargin_10 = MAX_uint8_T;
  }

  tmp_1 = rt_roundd_snf(UART_test_mod_f(256.0 - UART_test_mod_f((real_T)
    (((varargin_9 + frame[1]) + varargin_10) + frame[3]))));
  if (tmp_1 < 256.0) {
    if (tmp_1 >= 0.0) {
      frame[4] = (uint8_T)tmp_1;
    } else {
      frame[4] = 0U;
    }
  } else {
    frame[4] = MAX_uint8_T;
  }

  /* End of MATLAB Function: '<S3>/Arduino output1' */

  /* MATLABSystem: '<S3>/Serial Transmit2' */
  varargin_9 = 85U;
  varargin_10 = 170U;
  MW_Serial_write(UART_test_DW.obj.port, &frame[0], 5.0,
                  UART_test_DW.obj.dataSizeInBytes,
                  UART_test_DW.obj.sendModeEnum, UART_test_DW.obj.dataType,
                  UART_test_DW.obj.sendFormatEnum, 2.0, '\x00', &varargin_9, 1.0,
                  &varargin_10, 1.0);

  /* End of Outputs for SubSystem: '<Root>/Subsystem' */

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 1.0, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   */
  UART_test_M->Timing.clockTick1++;
}

/* Model initialize function */
void UART_test_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(UART_test_M, 300.0);
  UART_test_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  UART_test_M->Sizes.checksums[0] = (1261836293U);
  UART_test_M->Sizes.checksums[1] = (2820300700U);
  UART_test_M->Sizes.checksums[2] = (3086344084U);
  UART_test_M->Sizes.checksums[3] = (3310252160U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    UART_test_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(UART_test_M->extModeInfo,
      &UART_test_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(UART_test_M->extModeInfo, UART_test_M->Sizes.checksums);
    rteiSetTFinalTicks(UART_test_M->extModeInfo, 30000);
  }

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subsystem' */
  /* Start for MATLABSystem: '<S3>/Serial Transmit2' */
  UART_test_DW.obj.matlabCodegenIsDeleted = false;
  UART_test_DW.obj.isInitialized = 1L;
  UART_test_DW.obj.port = 1.0;
  UART_test_DW.obj.dataSizeInBytes = 1.0;
  UART_test_DW.obj.dataType = 0.0;
  UART_test_DW.obj.sendModeEnum = 0.0;
  UART_test_DW.obj.sendFormatEnum = 0.0;
  MW_SCI_Open(1);
  UART_test_DW.obj.isSetupComplete = true;

  /* End of SystemInitialize for SubSystem: '<Root>/Subsystem' */

  /* Start for MATLABSystem: '<Root>/Serial Receive1' */
  UART_test_DW.obj_d.matlabCodegenIsDeleted = false;
  UART_test_DW.obj_d.isInitialized = 1L;
  MW_SCI_Open(1);
  UART_test_DW.obj_d.isSetupComplete = true;
}

/* Model terminate function */
void UART_test_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Receive1' */
  if (!UART_test_DW.obj_d.matlabCodegenIsDeleted) {
    UART_test_DW.obj_d.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Receive1' */
  /* Terminate for Atomic SubSystem: '<Root>/Subsystem' */
  /* Terminate for MATLABSystem: '<S3>/Serial Transmit2' */
  if (!UART_test_DW.obj.matlabCodegenIsDeleted) {
    UART_test_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S3>/Serial Transmit2' */
  /* End of Terminate for SubSystem: '<Root>/Subsystem' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
