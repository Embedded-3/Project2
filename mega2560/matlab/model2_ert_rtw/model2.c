/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model2.c
 *
 * Code generated for Simulink model 'model2'.
 *
 * Model version                  : 1.152
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Mon May 26 16:45:28 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "model2.h"
#include "rtwtypes.h"
#include "model2_private.h"
#include <stddef.h>
#include "rt_nonfinite.h"
#include <math.h>

/* Block signals (default storage) */
B_model2_T model2_B;

/* Continuous states */
X_model2_T model2_X;

/* Disabled State Vector */
XDis_model2_T model2_XDis;

/* Block states (default storage) */
DW_model2_T model2_DW;

/* Real-time model */
static RT_MODEL_model2_T model2_M_;
RT_MODEL_model2_T *const model2_M = &model2_M_;

/* Forward declaration for local functions */
static real_T model2_mod(real_T x);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void model2_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[2] = ((boolean_T)rtmStepTask(model2_M, 2));
  eventFlags[3] = ((boolean_T)rtmStepTask(model2_M, 3));
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
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rates: 2, 3 */
  if (model2_M->Timing.TaskCounters.TID[1] == 0) {
    model2_M->Timing.RateInteraction.TID1_2 = (model2_M->
      Timing.TaskCounters.TID[2] == 0);
    model2_M->Timing.RateInteraction.TID1_3 = (model2_M->
      Timing.TaskCounters.TID[3] == 0);
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (model2_M->Timing.TaskCounters.TID[2])++;
  if ((model2_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.0005s, 0.0s] */
    model2_M->Timing.TaskCounters.TID[2] = 0;
  }

  (model2_M->Timing.TaskCounters.TID[3])++;
  if ((model2_M->Timing.TaskCounters.TID[3]) > 499) {/* Sample time: [0.05s, 0.0s] */
    model2_M->Timing.TaskCounters.TID[3] = 0;
  }
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  model2_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  model2_step0();
  model2_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  model2_step0();
  model2_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
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

/* Function for MATLAB Function: '<S4>/Arduino output1' */
static real_T model2_mod(real_T x)
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

/* Model step function for TID0 */
void model2_step0(void)                /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(model2_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&model2_M->solverInfo,((model2_M->Timing.clockTick0+1)*
      model2_M->Timing.stepSize0));

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(model2_M)) {
    model2_M->Timing.t[0] = rtsiGetT(&model2_M->solverInfo);
  }

  {
    real_T rtb_Derivative2;
    real_T u0;
    real_T *lastU;
    uint16_T dutyL;
    boolean_T tmp;

    /* RateTransition generated from: '<Root>/Sum1' incorporates:
     *  RateTransition generated from: '<Root>/Derivative2'
     *  RateTransition generated from: '<Root>/Integrator1'
     *  RateTransition generated from: '<Root>/Sum'
     */
    tmp = rtmIsMajorTimeStep(model2_M);
    if (tmp && model2_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition generated from: '<Root>/Sum1' */
      model2_B.TmpRTBAtSum1Inport1 = model2_DW.TmpRTBAtSum1Inport1_Buffer0;

      /* RateTransition generated from: '<Root>/Sum' */
      model2_B.TmpRTBAtSumInport1 = model2_DW.TmpRTBAtSumInport1_Buffer0;
    }

    /* End of RateTransition generated from: '<Root>/Sum1' */

    /* Sum: '<Root>/Sum1' incorporates:
     *  Gain: '<Root>/Ki1'
     *  Integrator: '<Root>/Integrator1'
     *  TransferFcn: '<Root>/Transfer Fcn'
     */
    model2_B.Sum1 = (model2_P.Ki1_Gain * model2_X.Integrator1_CSTATE +
                     model2_B.TmpRTBAtSum1Inport1) + model2_P.TransferFcn_C *
      model2_X.TransferFcn_CSTATE;

    /* Sum: '<Root>/Sum' incorporates:
     *  Gain: '<Root>/Ki'
     *  Integrator: '<Root>/Integrator'
     *  TransferFcn: '<Root>/Transfer Fcn1'
     */
    u0 = (model2_P.Ki_Gain * model2_X.Integrator_CSTATE +
          model2_B.TmpRTBAtSumInport1) + model2_P.TransferFcn1_C *
      model2_X.TransferFcn1_CSTATE;

    /* MATLAB Function: '<Root>/MATLAB Function' */
    if (!(u0 >= 0.0)) {
      u0 = 0.0;
    }

    if (!(u0 <= 400.0)) {
      u0 = 400.0;
    }

    dutyL = (uint16_T)rt_roundd_snf(u0 / 400.0 * 2000.0 + 2000.0);
    model2_B.byteL2 = (uint8_T)(dutyL & 255U);
    model2_B.byteL1 = (uint8_T)(dutyL >> 8);
    if (model2_B.Sum1 >= 0.0) {
      u0 = model2_B.Sum1;
    } else {
      u0 = 0.0;
    }

    if (!(u0 <= 400.0)) {
      u0 = 400.0;
    }

    dutyL = (uint16_T)rt_roundd_snf(u0 / 400.0 * 2000.0 + 2000.0);
    model2_B.byteR2 = (uint8_T)(dutyL & 255U);
    model2_B.byteR1 = (uint8_T)(dutyL >> 8);

    /* End of MATLAB Function: '<Root>/MATLAB Function' */
    if (tmp) {
      /* RateTransition generated from: '<Root>/Subsystem' */
      if (model2_M->Timing.RateInteraction.TID1_3) {
        model2_DW.byteL1_Buffer = model2_B.byteL1;

        /* RateTransition generated from: '<Root>/Subsystem' */
        model2_DW.byteL2_Buffer = model2_B.byteL2;

        /* RateTransition generated from: '<Root>/Subsystem' */
        model2_DW.byteR1_Buffer = model2_B.byteR1;

        /* RateTransition generated from: '<Root>/Subsystem' */
        model2_DW.byteR2_Buffer = model2_B.byteR2;
      }

      /* End of RateTransition generated from: '<Root>/Subsystem' */
      /* RateTransition generated from: '<Root>/Derivative1' */
      if (model2_M->Timing.RateInteraction.TID1_2) {
        /* RateTransition generated from: '<Root>/Derivative1' */
        model2_B.error = model2_DW.error_Buffer0;
      }

      /* End of RateTransition generated from: '<Root>/Derivative1' */
    }

    /* Derivative: '<Root>/Derivative1' incorporates:
     *  Derivative: '<Root>/Derivative2'
     */
    u0 = model2_M->Timing.t[0];
    if ((model2_DW.TimeStampA >= u0) && (model2_DW.TimeStampB >= u0)) {
      rtb_Derivative2 = 0.0;
    } else {
      rtb_Derivative2 = model2_DW.TimeStampA;
      lastU = &model2_DW.LastUAtTimeA;
      if (model2_DW.TimeStampA < model2_DW.TimeStampB) {
        if (model2_DW.TimeStampB < u0) {
          rtb_Derivative2 = model2_DW.TimeStampB;
          lastU = &model2_DW.LastUAtTimeB;
        }
      } else if (model2_DW.TimeStampA >= u0) {
        rtb_Derivative2 = model2_DW.TimeStampB;
        lastU = &model2_DW.LastUAtTimeB;
      }

      rtb_Derivative2 = (model2_B.error - *lastU) / (u0 - rtb_Derivative2);
    }

    /* End of Derivative: '<Root>/Derivative1' */

    /* Gain: '<Root>/Kd' */
    model2_B.Kd = model2_P.Kd_Gain * rtb_Derivative2;

    /* RateTransition generated from: '<Root>/Derivative2' */
    if (tmp && model2_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition generated from: '<Root>/Derivative2' */
      model2_B.TmpRTBAtDerivative2Inport1 =
        model2_DW.TmpRTBAtDerivative2Inport1_Buff;
    }

    /* Derivative: '<Root>/Derivative2' */
    if ((model2_DW.TimeStampA_l >= u0) && (model2_DW.TimeStampB_i >= u0)) {
      rtb_Derivative2 = 0.0;
    } else {
      rtb_Derivative2 = model2_DW.TimeStampA_l;
      lastU = &model2_DW.LastUAtTimeA_k;
      if (model2_DW.TimeStampA_l < model2_DW.TimeStampB_i) {
        if (model2_DW.TimeStampB_i < u0) {
          rtb_Derivative2 = model2_DW.TimeStampB_i;
          lastU = &model2_DW.LastUAtTimeB_o;
        }
      } else if (model2_DW.TimeStampA_l >= u0) {
        rtb_Derivative2 = model2_DW.TimeStampB_i;
        lastU = &model2_DW.LastUAtTimeB_o;
      }

      rtb_Derivative2 = (model2_B.TmpRTBAtDerivative2Inport1 - *lastU) / (u0 -
        rtb_Derivative2);
    }

    /* Gain: '<Root>/Kd1' */
    model2_B.Kd1 = model2_P.Kd1_Gain * rtb_Derivative2;

    /* RateTransition generated from: '<Root>/Integrator1' */
    if (tmp && model2_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition generated from: '<Root>/Integrator1' */
      model2_B.TmpRTBAtIntegrator1Inport1 =
        model2_DW.TmpRTBAtIntegrator1Inport1_Buff;

      /* RateTransition generated from: '<Root>/Integrator' */
      model2_B.error_g = model2_DW.TmpRTBAtIntegratorInport1_Buffe;
    }
  }

  if (rtmIsMajorTimeStep(model2_M)) {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative1' */
    if (model2_DW.TimeStampA == (rtInf)) {
      model2_DW.TimeStampA = model2_M->Timing.t[0];
      lastU = &model2_DW.LastUAtTimeA;
    } else if (model2_DW.TimeStampB == (rtInf)) {
      model2_DW.TimeStampB = model2_M->Timing.t[0];
      lastU = &model2_DW.LastUAtTimeB;
    } else if (model2_DW.TimeStampA < model2_DW.TimeStampB) {
      model2_DW.TimeStampA = model2_M->Timing.t[0];
      lastU = &model2_DW.LastUAtTimeA;
    } else {
      model2_DW.TimeStampB = model2_M->Timing.t[0];
      lastU = &model2_DW.LastUAtTimeB;
    }

    *lastU = model2_B.error;

    /* End of Update for Derivative: '<Root>/Derivative1' */

    /* Update for Derivative: '<Root>/Derivative2' */
    if (model2_DW.TimeStampA_l == (rtInf)) {
      model2_DW.TimeStampA_l = model2_M->Timing.t[0];
      lastU = &model2_DW.LastUAtTimeA_k;
    } else if (model2_DW.TimeStampB_i == (rtInf)) {
      model2_DW.TimeStampB_i = model2_M->Timing.t[0];
      lastU = &model2_DW.LastUAtTimeB_o;
    } else if (model2_DW.TimeStampA_l < model2_DW.TimeStampB_i) {
      model2_DW.TimeStampA_l = model2_M->Timing.t[0];
      lastU = &model2_DW.LastUAtTimeA_k;
    } else {
      model2_DW.TimeStampB_i = model2_M->Timing.t[0];
      lastU = &model2_DW.LastUAtTimeB_o;
    }

    *lastU = model2_B.TmpRTBAtDerivative2Inport1;

    /* End of Update for Derivative: '<Root>/Derivative2' */
    {
      extmodeErrorCode_T returnCode = EXTMODE_SUCCESS;
      extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
        ((model2_M->Timing.clockTick1 * 1) + 0);

      /* Trigger External Mode event */
      returnCode = extmodeEvent(1, extmodeTime);
      if (returnCode != EXTMODE_SUCCESS) {
        /* Code to handle External Mode event errors
           may be added here */
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(model2_M)) {
    rt_ertODEUpdateContinuousStates(&model2_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++model2_M->Timing.clockTick0;
    model2_M->Timing.t[0] = rtsiGetSolverStopTime(&model2_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.0001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    model2_M->Timing.clockTick1++;
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void model2_derivatives(void)
{
  XDot_model2_T *_rtXdot;
  _rtXdot = ((XDot_model2_T *) model2_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = model2_B.TmpRTBAtIntegrator1Inport1;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = model2_P.TransferFcn_A *
    model2_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += model2_B.Kd1;

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = model2_B.error_g;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = model2_P.TransferFcn1_A *
    model2_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += model2_B.Kd;
}

/* Model step function for TID2 */
void model2_step2(void)                /* Sample time: [0.0005s, 0.0s] */
{
  real_T rtb_Kp;
  real_T rtb_error;
  int16_T i;
  uint16_T qY;
  uint16_T qY_0;
  uint8_T data_out[10];
  uint8_T b_status;

  /* MATLABSystem: '<Root>/Serial Receive1' */
  MW_Serial_read(1, 1U, &model2_B.SerialReceive1_o1, &b_status, NULL, 0.0, NULL,
                 0.0);

  /* MATLAB Function: '<Root>/Arduino Input1' incorporates:
   *  MATLABSystem: '<Root>/Serial Receive1'
   * */
  if (b_status == 1) {
    if (!model2_DW.collecting) {
      if (model2_B.SerialReceive1_o1 == 170) {
        model2_DW.buffer[0] = model2_B.SerialReceive1_o1;
        model2_DW.count = 1.0;
        model2_DW.collecting = true;
      }
    } else {
      if (model2_B.SerialReceive1_o1 == 170) {
        model2_DW.count = 1.0;
      }

      model2_DW.count++;
      model2_DW.buffer[(int16_T)model2_DW.count - 1] =
        model2_B.SerialReceive1_o1;
      if (model2_DW.count == 10.0) {
        for (i = 0; i < 10; i++) {
          data_out[i] = model2_DW.buffer[i];
        }

        model2_DW.count = 0.0;
        model2_DW.collecting = false;

        /* MATLAB Function: '<Root>/Arduino Input2' */
        model2_DW.p_valid = true;
        qY = data_out[1] - 1U;
        if (data_out[1] - 1U > data_out[1]) {
          qY = 0U;
        }

        qY_0 = data_out[2] - 1U;
        if (data_out[2] - 1U > data_out[2]) {
          qY_0 = 0U;
        }

        model2_DW.p_speed_L = ((real_T)(int16_T)qY_0 / 100.0 + (real_T)(int16_T)
          qY) * 10.0;
        qY = data_out[3] - 1U;
        if (data_out[3] - 1U > data_out[3]) {
          qY = 0U;
        }

        qY_0 = data_out[4] - 1U;
        if (data_out[4] - 1U > data_out[4]) {
          qY_0 = 0U;
        }

        model2_DW.p_speed_R = ((real_T)(int16_T)qY_0 / 100.0 + (real_T)(int16_T)
          qY) * 10.0;
        if (data_out[6] == 1) {
          data_out[6] = 0U;
        }

        model2_DW.p_v_target = data_out[6] * 10U;
        if (data_out[5] <= 30) {
          model2_DW.p_slope = data_out[5];
        }

        if (data_out[7] <= 30) {
          model2_DW.p_steer = data_out[7];
        }
      }
    }
  } else {
    for (i = 0; i < 10; i++) {
      model2_DW.buffer[i] = 0U;
    }

    model2_DW.count = 0.0;
    model2_DW.collecting = false;
  }

  /* End of MATLAB Function: '<Root>/Arduino Input1' */

  /* MATLAB Function: '<Root>/Arduino Input2' */
  model2_B.valid = model2_DW.p_valid;
  model2_B.speed_L = model2_DW.p_speed_L;
  model2_B.speed_R = model2_DW.p_speed_R;
  model2_B.v_target = model2_DW.p_v_target;
  model2_B.slope = model2_DW.p_slope;
  model2_B.steer = model2_DW.p_steer;

  /* Gain: '<Root>/slope_gain' */
  model2_B.slope_gain = model2_P.slope_gain_Gain * model2_B.slope;

  /* Gain: '<Root>/steer_gain' */
  model2_B.steer_gain = model2_P.steer_gain_Gain * model2_B.steer;

  /* Sum: '<Root>/Add' incorporates:
   *  Sum: '<Root>/Sum2'
   */
  rtb_error = (((real_T)model2_B.v_target + model2_B.steer_gain) +
               model2_B.slope_gain) - model2_B.speed_L;

  /* Gain: '<Root>/Kp' */
  rtb_Kp = model2_P.Kp_Gain * rtb_error;

  /* RateTransition generated from: '<Root>/Sum' */
  model2_DW.TmpRTBAtSumInport1_Buffer0 = rtb_Kp;

  /* RateTransition generated from: '<Root>/Integrator' */
  model2_DW.TmpRTBAtIntegratorInport1_Buffe = rtb_error;

  /* RateTransition generated from: '<Root>/Derivative1' */
  model2_DW.error_Buffer0 = rtb_error;

  /* Sum: '<Root>/Add1' incorporates:
   *  Sum: '<Root>/Sum3'
   */
  rtb_error = (((real_T)model2_B.v_target - model2_B.steer_gain) +
               model2_B.slope_gain) - model2_B.speed_R;

  /* Gain: '<Root>/Kp1' */
  rtb_Kp = model2_P.Kp1_Gain * rtb_error;

  /* RateTransition generated from: '<Root>/Sum1' */
  model2_DW.TmpRTBAtSum1Inport1_Buffer0 = rtb_Kp;

  /* RateTransition generated from: '<Root>/Derivative2' */
  model2_DW.TmpRTBAtDerivative2Inport1_Buff = rtb_error;

  /* RateTransition generated from: '<Root>/Integrator1' */
  model2_DW.TmpRTBAtIntegrator1Inport1_Buff = rtb_error;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.0005, which is the step size
   * of the task. Size of "clockTick2" ensures timer will not overflow during the
   * application lifespan selected.
   */
  model2_M->Timing.clockTick2++;
}

/* Model step function for TID3 */
void model2_step3(void)                /* Sample time: [0.05s, 0.0s] */
{
  real_T tmp;
  uint8_T dataIn[5];
  uint8_T varargin_10;
  uint8_T varargin_9;

  /* Outputs for Atomic SubSystem: '<Root>/Subsystem' */
  /* MATLABSystem: '<S4>/Serial Transmit2' incorporates:
   *  RateTransition generated from: '<Root>/Subsystem'
   * */
  varargin_9 = 85U;
  varargin_10 = 170U;
  dataIn[0] = model2_DW.byteL1_Buffer;
  dataIn[1] = model2_DW.byteL2_Buffer;
  dataIn[2] = model2_DW.byteR1_Buffer;
  dataIn[3] = model2_DW.byteR2_Buffer;

  /* MATLAB Function: '<S4>/Arduino output1' incorporates:
   *  RateTransition generated from: '<Root>/Subsystem'
   * */
  tmp = rt_roundd_snf(model2_mod(256.0 - model2_mod((real_T)
    (((model2_DW.byteL1_Buffer + model2_DW.byteL2_Buffer) +
      model2_DW.byteR1_Buffer) + model2_DW.byteR2_Buffer))));
  if (tmp < 256.0) {
    if (tmp >= 0.0) {
      /* MATLABSystem: '<S4>/Serial Transmit2' */
      dataIn[4] = (uint8_T)tmp;
    } else {
      /* MATLABSystem: '<S4>/Serial Transmit2' */
      dataIn[4] = 0U;
    }
  } else {
    /* MATLABSystem: '<S4>/Serial Transmit2' */
    dataIn[4] = MAX_uint8_T;
  }

  /* End of MATLAB Function: '<S4>/Arduino output1' */

  /* MATLABSystem: '<S4>/Serial Transmit2' */
  MW_Serial_write(model2_DW.obj.port, &dataIn[0], 5.0,
                  model2_DW.obj.dataSizeInBytes, model2_DW.obj.sendModeEnum,
                  model2_DW.obj.dataType, model2_DW.obj.sendFormatEnum, 2.0,
                  '\x00', &varargin_9, 1.0, &varargin_10, 1.0);

  /* End of Outputs for SubSystem: '<Root>/Subsystem' */

  /* Update absolute time */
  /* The "clockTick3" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.05, which is the step size
   * of the task. Size of "clockTick3" ensures timer will not overflow during the
   * application lifespan selected.
   */
  model2_M->Timing.clockTick3++;
}

/* Model initialize function */
void model2_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&model2_M->solverInfo, &model2_M->Timing.simTimeStep);
    rtsiSetTPtr(&model2_M->solverInfo, &rtmGetTPtr(model2_M));
    rtsiSetStepSizePtr(&model2_M->solverInfo, &model2_M->Timing.stepSize0);
    rtsiSetdXPtr(&model2_M->solverInfo, &model2_M->derivs);
    rtsiSetContStatesPtr(&model2_M->solverInfo, (real_T **)
                         &model2_M->contStates);
    rtsiSetNumContStatesPtr(&model2_M->solverInfo,
      &model2_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&model2_M->solverInfo,
      &model2_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&model2_M->solverInfo,
      &model2_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&model2_M->solverInfo,
      &model2_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&model2_M->solverInfo, (boolean_T**)
      &model2_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&model2_M->solverInfo, (&rtmGetErrorStatus(model2_M)));
    rtsiSetRTModelPtr(&model2_M->solverInfo, model2_M);
  }

  rtsiSetSimTimeStep(&model2_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&model2_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&model2_M->solverInfo, false);
  model2_M->intgData.y = model2_M->odeY;
  model2_M->intgData.f[0] = model2_M->odeF[0];
  model2_M->intgData.f[1] = model2_M->odeF[1];
  model2_M->intgData.f[2] = model2_M->odeF[2];
  model2_M->contStates = ((X_model2_T *) &model2_X);
  model2_M->contStateDisabled = ((XDis_model2_T *) &model2_XDis);
  model2_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&model2_M->solverInfo, (void *)&model2_M->intgData);
  rtsiSetSolverName(&model2_M->solverInfo,"ode3");
  rtmSetTPtr(model2_M, &model2_M->Timing.tArray[0]);
  rtmSetTFinal(model2_M, 500.0);
  model2_M->Timing.stepSize0 = 0.0001;

  /* External mode info */
  model2_M->Sizes.checksums[0] = (626640335U);
  model2_M->Sizes.checksums[1] = (3251649431U);
  model2_M->Sizes.checksums[2] = (1210479108U);
  model2_M->Sizes.checksums[3] = (1303302662U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[8];
    model2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(model2_M->extModeInfo,
      &model2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(model2_M->extModeInfo, model2_M->Sizes.checksums);
    rteiSetTFinalTicks(model2_M->extModeInfo, 5000000);
  }

  /* Start for RateTransition generated from: '<Root>/Sum1' */
  model2_B.TmpRTBAtSum1Inport1 = model2_P.TmpRTBAtSum1Inport1_InitialCond;

  /* Start for RateTransition generated from: '<Root>/Sum' */
  model2_B.TmpRTBAtSumInport1 = model2_P.TmpRTBAtSumInport1_InitialCondi;

  /* Start for RateTransition generated from: '<Root>/Derivative1' */
  model2_B.error = model2_P.error_InitialCondition;

  /* Start for RateTransition generated from: '<Root>/Derivative2' */
  model2_B.TmpRTBAtDerivative2Inport1 = model2_P.TmpRTBAtDerivative2Inport1_Init;

  /* Start for RateTransition generated from: '<Root>/Integrator1' */
  model2_B.TmpRTBAtIntegrator1Inport1 = model2_P.TmpRTBAtIntegrator1Inport1_Init;

  /* Start for RateTransition generated from: '<Root>/Integrator' */
  model2_B.error_g = model2_P.TmpRTBAtIntegratorInport1_Initi;

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  model2_X.Integrator1_CSTATE = model2_P.Integrator1_IC;

  /* InitializeConditions for RateTransition generated from: '<Root>/Sum1' */
  model2_DW.TmpRTBAtSum1Inport1_Buffer0 =
    model2_P.TmpRTBAtSum1Inport1_InitialCond;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  model2_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for RateTransition generated from: '<Root>/Sum' */
  model2_DW.TmpRTBAtSumInport1_Buffer0 =
    model2_P.TmpRTBAtSumInport1_InitialCondi;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  model2_X.Integrator_CSTATE = model2_P.Integrator_IC;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn1' */
  model2_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for RateTransition generated from: '<Root>/Derivative1' */
  model2_DW.error_Buffer0 = model2_P.error_InitialCondition;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  model2_DW.TimeStampA = (rtInf);
  model2_DW.TimeStampB = (rtInf);

  /* InitializeConditions for RateTransition generated from: '<Root>/Derivative2' */
  model2_DW.TmpRTBAtDerivative2Inport1_Buff =
    model2_P.TmpRTBAtDerivative2Inport1_Init;

  /* InitializeConditions for Derivative: '<Root>/Derivative2' */
  model2_DW.TimeStampA_l = (rtInf);
  model2_DW.TimeStampB_i = (rtInf);

  /* InitializeConditions for RateTransition generated from: '<Root>/Integrator1' */
  model2_DW.TmpRTBAtIntegrator1Inport1_Buff =
    model2_P.TmpRTBAtIntegrator1Inport1_Init;

  /* InitializeConditions for RateTransition generated from: '<Root>/Integrator' */
  model2_DW.TmpRTBAtIntegratorInport1_Buffe =
    model2_P.TmpRTBAtIntegratorInport1_Initi;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subsystem' */
  /* Start for MATLABSystem: '<S4>/Serial Transmit2' */
  model2_DW.obj.matlabCodegenIsDeleted = false;
  model2_DW.obj.isInitialized = 1L;
  model2_DW.obj.port = 1.0;
  model2_DW.obj.dataSizeInBytes = 1.0;
  model2_DW.obj.dataType = 0.0;
  model2_DW.obj.sendModeEnum = 0.0;
  model2_DW.obj.sendFormatEnum = 0.0;
  MW_SCI_Open(1);
  model2_DW.obj.isSetupComplete = true;

  /* End of SystemInitialize for SubSystem: '<Root>/Subsystem' */

  /* Start for MATLABSystem: '<Root>/Serial Receive1' */
  model2_DW.obj_e.matlabCodegenIsDeleted = false;
  model2_DW.obj_e.isInitialized = 1L;
  MW_SCI_Open(1);
  model2_DW.obj_e.isSetupComplete = true;
}

/* Model terminate function */
void model2_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Receive1' */
  if (!model2_DW.obj_e.matlabCodegenIsDeleted) {
    model2_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Receive1' */
  /* Terminate for Atomic SubSystem: '<Root>/Subsystem' */
  /* Terminate for MATLABSystem: '<S4>/Serial Transmit2' */
  if (!model2_DW.obj.matlabCodegenIsDeleted) {
    model2_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S4>/Serial Transmit2' */
  /* End of Terminate for SubSystem: '<Root>/Subsystem' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
