/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model1.c
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

#include "model1.h"
#include "rtwtypes.h"
#include "model1_private.h"
#include <stddef.h>
#include "rt_nonfinite.h"
#include <math.h>

/* Named constants for MATLAB Function: '<Root>/MATLAB Function1' */
#define model1_CALL_EVENT              (-1L)

/* Block signals (default storage) */
B_model1_T model1_B;

/* Continuous states */
X_model1_T model1_X;

/* Disabled State Vector */
XDis_model1_T model1_XDis;

/* Block states (default storage) */
DW_model1_T model1_DW;

/* Real-time model */
static RT_MODEL_model1_T model1_M_;
RT_MODEL_model1_T *const model1_M = &model1_M_;

/* Forward declaration for local functions */
static real_T model1_mod(real_T x);
static void rate_monotonic_scheduler(void);
int16_T div_nde_s16_floor(int16_T numerator, int16_T denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void model1_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[2] = ((boolean_T)rtmStepTask(model1_M, 2));
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

  /* tid 1 shares data with slower tid rate: 2 */
  if (model1_M->Timing.TaskCounters.TID[1] == 0) {
    model1_M->Timing.RateInteraction.TID1_2 = (model1_M->
      Timing.TaskCounters.TID[2] == 0);
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (model1_M->Timing.TaskCounters.TID[2])++;
  if ((model1_M->Timing.TaskCounters.TID[2]) > 49) {/* Sample time: [0.05s, 0.0s] */
    model1_M->Timing.TaskCounters.TID[2] = 0;
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
  model1_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  model1_step0();
  model1_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  model1_step0();
  model1_derivatives();

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

/*
 * System initialize for atomic system:
 *    '<Root>/MATLAB Function1'
 *    '<Root>/MATLAB Function2'
 */
void model1_MATLABFunction1_Init(DW_MATLABFunction1_model1_T *localDW)
{
  localDW->sfEvent = model1_CALL_EVENT;
}

/*
 * Output and update for atomic system:
 *    '<Root>/MATLAB Function1'
 *    '<Root>/MATLAB Function2'
 */
void model1_MATLABFunction1(uint16_T rtu_u, real_T *rty_y,
  DW_MATLABFunction1_model1_T *localDW)
{
  localDW->sfEvent = model1_CALL_EVENT;
  *rty_y = (rtu_u >= 1U);
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

/* Function for MATLAB Function: '<S6>/Arduino output1' */
static real_T model1_mod(real_T x)
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
void model1_step0(void)                /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(model1_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&model1_M->solverInfo,((model1_M->Timing.clockTick0+1)*
      model1_M->Timing.stepSize0));

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(model1_M)) {
    model1_M->Timing.t[0] = rtsiGetT(&model1_M->solverInfo);
  }

  {
    real_T rtb_Derivative1;
    real_T y_o;
    real_T *lastU;
    int16_T i;
    int16_T tmp_0;
    uint16_T qY;
    uint16_T qY_0;
    uint8_T data_out[10];
    uint8_T b_status;
    boolean_T tmp;
    tmp = rtmIsMajorTimeStep(model1_M);
    if (tmp) {
      /* MATLABSystem: '<Root>/Serial Receive1' */
      MW_Serial_read(1, 1U, &model1_B.SerialReceive1_o1, &b_status, NULL, 0.0,
                     NULL, 0.0);

      /* MATLAB Function: '<Root>/Arduino Input1' incorporates:
       *  MATLABSystem: '<Root>/Serial Receive1'
       * */
      if (b_status == 1) {
        if (!model1_DW.collecting) {
          if (model1_B.SerialReceive1_o1 == 170) {
            model1_DW.buffer[0] = model1_B.SerialReceive1_o1;
            model1_DW.count = 1.0;
            model1_DW.collecting = true;
          }
        } else {
          model1_DW.count++;
          model1_DW.buffer[(int16_T)model1_DW.count - 1] =
            model1_B.SerialReceive1_o1;
          if (model1_DW.count == 10.0) {
            for (i = 0; i < 10; i++) {
              data_out[i] = model1_DW.buffer[i];
            }

            model1_DW.count = 0.0;
            model1_DW.collecting = false;

            /* MATLAB Function: '<Root>/Arduino Input2' */
            model1_DW.p_valid = true;
            qY = data_out[1] - 1U;
            if (data_out[1] - 1U > data_out[1]) {
              qY = 0U;
            }

            qY_0 = data_out[2] - 1U;
            if (data_out[2] - 1U > data_out[2]) {
              qY_0 = 0U;
            }

            model1_DW.p_speed_L = ((real_T)(int16_T)qY_0 / 100.0 + (real_T)
              (int16_T)qY) * 10.0;
            qY = data_out[3] - 1U;
            if (data_out[3] - 1U > data_out[3]) {
              qY = 0U;
            }

            qY_0 = data_out[4] - 1U;
            if (data_out[4] - 1U > data_out[4]) {
              qY_0 = 0U;
            }

            model1_DW.p_speed_R = ((real_T)(int16_T)qY_0 / 100.0 + (real_T)
              (int16_T)qY) * 10.0;
            if (data_out[6] == 1) {
              data_out[6] = 0U;
            }

            qY = data_out[6] - 1U;
            if (data_out[6] - 1U > data_out[6]) {
              qY = 0U;
            }

            model1_DW.p_v_target = qY * 10U;
            if (data_out[5] <= 30) {
              model1_DW.p_slope = data_out[5];
            }

            if (data_out[7] <= 30) {
              model1_DW.p_steer = data_out[7];
            }

            model1_DW.p_crc = data_out[8];
          }
        }
      }

      /* End of MATLAB Function: '<Root>/Arduino Input1' */

      /* MATLAB Function: '<Root>/Arduino Input2' */
      model1_B.valid = model1_DW.p_valid;
      model1_B.speed_L = model1_DW.p_speed_L;
      model1_B.speed_R = model1_DW.p_speed_R;
      model1_B.v_target = model1_DW.p_v_target;
      model1_B.slope = model1_DW.p_slope;
      model1_B.steer = model1_DW.p_steer;
      model1_B.crc = model1_DW.p_crc;

      /* MATLAB Function: '<Root>/MATLAB Function1' */
      model1_MATLABFunction1(model1_B.v_target, &y_o,
        &model1_DW.sf_MATLABFunction1);

      /* Gain: '<Root>/steer_gain' */
      model1_B.steer_gain = model1_P.steer_gain_Gain * model1_B.steer;

      /* Gain: '<Root>/slope_gain' */
      model1_B.slope_gain = model1_P.slope_gain_Gain * model1_B.slope;

      /* DotProduct: '<Root>/Dot Product' incorporates:
       *  Sum: '<Root>/Add'
       *  Sum: '<Root>/Sum2'
       */
      model1_B.DotProduct = ((((real_T)model1_B.v_target + model1_B.steer_gain)
        + model1_B.slope_gain) - model1_B.speed_L) * y_o;

      /* Gain: '<Root>/Kp' */
      model1_B.Kp = model1_P.Kp_Gain * model1_B.DotProduct;
    }

    /* Sum: '<Root>/Sum' incorporates:
     *  Gain: '<Root>/Ki'
     *  Integrator: '<Root>/Integrator'
     *  TransferFcn: '<Root>/Transfer Fcn1'
     */
    model1_B.Sum = (model1_P.Ki_Gain * model1_X.Integrator_CSTATE + model1_B.Kp)
      + model1_P.TransferFcn1_C * model1_X.TransferFcn1_CSTATE;
    if (tmp) {
      /* MATLAB Function: '<Root>/MATLAB Function2' */
      model1_MATLABFunction1(model1_B.v_target, &y_o,
        &model1_DW.sf_MATLABFunction2);

      /* DotProduct: '<Root>/Dot Product1' incorporates:
       *  Sum: '<Root>/Add1'
       *  Sum: '<Root>/Sum3'
       */
      model1_B.DotProduct1 = ((((real_T)model1_B.v_target - model1_B.steer_gain)
        + model1_B.slope_gain) - model1_B.speed_R) * y_o;

      /* Gain: '<Root>/Kp1' */
      model1_B.Kp1 = model1_P.Kp1_Gain * model1_B.DotProduct1;
    }

    /* Sum: '<Root>/Sum1' incorporates:
     *  Gain: '<Root>/Ki1'
     *  Integrator: '<Root>/Integrator1'
     *  TransferFcn: '<Root>/Transfer Fcn'
     */
    model1_B.Sum1 = (model1_P.Ki1_Gain * model1_X.Integrator1_CSTATE +
                     model1_B.Kp1) + model1_P.TransferFcn_C *
      model1_X.TransferFcn_CSTATE;

    /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
     *  Constant: '<Root>/Constant'
     *  Constant: '<Root>/Constant1'
     */
    rtb_Derivative1 = model1_P.Constant1_Value - model1_P.Constant_Value;
    y_o = rt_roundd_snf((model1_B.Sum - model1_P.Constant_Value) /
                        rtb_Derivative1 * 2000.0 - 1000.0);
    if (y_o < 32768.0) {
      if (y_o >= -32768.0) {
        tmp_0 = (int16_T)y_o;
      } else {
        tmp_0 = MIN_int16_T;
      }
    } else {
      tmp_0 = MAX_int16_T;
    }

    y_o = rt_roundd_snf((model1_B.Sum1 - model1_P.Constant_Value) /
                        rtb_Derivative1 * 2000.0 - 1000.0);
    if (y_o < 32768.0) {
      if (y_o >= -32768.0) {
        i = (int16_T)y_o;
      } else {
        i = MIN_int16_T;
      }
    } else {
      i = MAX_int16_T;
    }

    model1_B.byteL2 = (int16_T)((uint16_T)tmp_0 & 255U);
    model1_B.byteL1 = tmp_0 >> 8;
    model1_B.byteR2 = (int16_T)((uint16_T)i & 255U);
    model1_B.byteR1 = i >> 8;

    /* End of MATLAB Function: '<Root>/MATLAB Function' */
    if (tmp) {
      /* RateTransition generated from: '<Root>/Subsystem' */
      if (model1_M->Timing.RateInteraction.TID1_2) {
        model1_DW.byteL1_Buffer = model1_B.byteL1;

        /* RateTransition generated from: '<Root>/Subsystem' */
        model1_DW.byteL2_Buffer = model1_B.byteL2;
      }

      /* End of RateTransition generated from: '<Root>/Subsystem' */
    }

    /* Derivative: '<Root>/Derivative2' incorporates:
     *  Derivative: '<Root>/Derivative1'
     */
    y_o = model1_M->Timing.t[0];
    if ((model1_DW.TimeStampA >= y_o) && (model1_DW.TimeStampB >= y_o)) {
      rtb_Derivative1 = 0.0;
    } else {
      rtb_Derivative1 = model1_DW.TimeStampA;
      lastU = &model1_DW.LastUAtTimeA;
      if (model1_DW.TimeStampA < model1_DW.TimeStampB) {
        if (model1_DW.TimeStampB < y_o) {
          rtb_Derivative1 = model1_DW.TimeStampB;
          lastU = &model1_DW.LastUAtTimeB;
        }
      } else if (model1_DW.TimeStampA >= y_o) {
        rtb_Derivative1 = model1_DW.TimeStampB;
        lastU = &model1_DW.LastUAtTimeB;
      }

      rtb_Derivative1 = (model1_B.DotProduct1 - *lastU) / (y_o - rtb_Derivative1);
    }

    /* End of Derivative: '<Root>/Derivative2' */

    /* Gain: '<Root>/Kd1' */
    model1_B.Kd1 = model1_P.Kd1_Gain * rtb_Derivative1;
    if (tmp) {
    }

    /* Derivative: '<Root>/Derivative1' */
    if ((model1_DW.TimeStampA_i >= y_o) && (model1_DW.TimeStampB_a >= y_o)) {
      rtb_Derivative1 = 0.0;
    } else {
      rtb_Derivative1 = model1_DW.TimeStampA_i;
      lastU = &model1_DW.LastUAtTimeA_e;
      if (model1_DW.TimeStampA_i < model1_DW.TimeStampB_a) {
        if (model1_DW.TimeStampB_a < y_o) {
          rtb_Derivative1 = model1_DW.TimeStampB_a;
          lastU = &model1_DW.LastUAtTimeB_c;
        }
      } else if (model1_DW.TimeStampA_i >= y_o) {
        rtb_Derivative1 = model1_DW.TimeStampB_a;
        lastU = &model1_DW.LastUAtTimeB_c;
      }

      rtb_Derivative1 = (model1_B.DotProduct - *lastU) / (y_o - rtb_Derivative1);
    }

    /* Gain: '<Root>/Kd' */
    model1_B.Kd = model1_P.Kd_Gain * rtb_Derivative1;
    if (tmp) {
    }
  }

  if (rtmIsMajorTimeStep(model1_M)) {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative2' */
    if (model1_DW.TimeStampA == (rtInf)) {
      model1_DW.TimeStampA = model1_M->Timing.t[0];
      lastU = &model1_DW.LastUAtTimeA;
    } else if (model1_DW.TimeStampB == (rtInf)) {
      model1_DW.TimeStampB = model1_M->Timing.t[0];
      lastU = &model1_DW.LastUAtTimeB;
    } else if (model1_DW.TimeStampA < model1_DW.TimeStampB) {
      model1_DW.TimeStampA = model1_M->Timing.t[0];
      lastU = &model1_DW.LastUAtTimeA;
    } else {
      model1_DW.TimeStampB = model1_M->Timing.t[0];
      lastU = &model1_DW.LastUAtTimeB;
    }

    *lastU = model1_B.DotProduct1;

    /* End of Update for Derivative: '<Root>/Derivative2' */

    /* Update for Derivative: '<Root>/Derivative1' */
    if (model1_DW.TimeStampA_i == (rtInf)) {
      model1_DW.TimeStampA_i = model1_M->Timing.t[0];
      lastU = &model1_DW.LastUAtTimeA_e;
    } else if (model1_DW.TimeStampB_a == (rtInf)) {
      model1_DW.TimeStampB_a = model1_M->Timing.t[0];
      lastU = &model1_DW.LastUAtTimeB_c;
    } else if (model1_DW.TimeStampA_i < model1_DW.TimeStampB_a) {
      model1_DW.TimeStampA_i = model1_M->Timing.t[0];
      lastU = &model1_DW.LastUAtTimeA_e;
    } else {
      model1_DW.TimeStampB_a = model1_M->Timing.t[0];
      lastU = &model1_DW.LastUAtTimeB_c;
    }

    *lastU = model1_B.DotProduct;

    /* End of Update for Derivative: '<Root>/Derivative1' */
    {
      extmodeErrorCode_T returnCode = EXTMODE_SUCCESS;
      extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
        ((model1_M->Timing.clockTick1 * 1) + 0);

      /* Trigger External Mode event */
      returnCode = extmodeEvent(1, extmodeTime);
      if (returnCode != EXTMODE_SUCCESS) {
        /* Code to handle External Mode event errors
           may be added here */
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(model1_M)) {
    rt_ertODEUpdateContinuousStates(&model1_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++model1_M->Timing.clockTick0;
    model1_M->Timing.t[0] = rtsiGetSolverStopTime(&model1_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    model1_M->Timing.clockTick1++;
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void model1_derivatives(void)
{
  XDot_model1_T *_rtXdot;
  _rtXdot = ((XDot_model1_T *) model1_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = model1_B.DotProduct;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = model1_P.TransferFcn1_A *
    model1_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += model1_B.Kd;

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = model1_B.DotProduct1;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = model1_P.TransferFcn_A *
    model1_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += model1_B.Kd1;
}

/* Model step function for TID2 */
void model1_step2(void)                /* Sample time: [0.05s, 0.0s] */
{
  real_T tmp;
  int32_T tmp_3;
  int16_T tmp_0;
  int16_T tmp_1;
  int16_T tmp_2;
  int16_T tmp_4;
  uint8_T frame[5];
  uint8_T varargin_10;
  uint8_T varargin_9;

  /* Outputs for Atomic SubSystem: '<Root>/Subsystem' */
  /* MATLAB Function: '<S6>/Arduino output1' incorporates:
   *  RateTransition generated from: '<Root>/Subsystem'
   * */
  tmp_4 = model1_DW.byteL1_Buffer;
  if (model1_DW.byteL1_Buffer < 0) {
    tmp_4 = 0;
  } else if (model1_DW.byteL1_Buffer > 255) {
    tmp_4 = 255;
  }

  frame[0] = (uint8_T)tmp_4;
  tmp_3 = model1_DW.byteL1_Buffer * 100L;
  if (tmp_3 > 32767L) {
    tmp_3 = 32767L;
  } else if (tmp_3 < -32768L) {
    tmp_3 = -32768L;
  }

  tmp_2 = (int16_T)tmp_3 - div_nde_s16_floor((int16_T)tmp_3, 100) * 100;
  if (tmp_2 < 0) {
    tmp_2 = 0;
  } else if (tmp_2 > 255) {
    tmp_2 = 255;
  }

  frame[1] = (uint8_T)tmp_2;
  tmp_1 = model1_DW.byteL2_Buffer;
  if (model1_DW.byteL2_Buffer < 0) {
    tmp_1 = 0;
  } else if (model1_DW.byteL2_Buffer > 255) {
    tmp_1 = 255;
  }

  frame[2] = (uint8_T)tmp_1;
  tmp_3 = model1_DW.byteL2_Buffer * 100L;
  if (tmp_3 > 32767L) {
    tmp_3 = 32767L;
  } else if (tmp_3 < -32768L) {
    tmp_3 = -32768L;
  }

  tmp_0 = (int16_T)tmp_3 - div_nde_s16_floor((int16_T)tmp_3, 100) * 100;
  if (tmp_0 < 0) {
    tmp_0 = 0;
  } else if (tmp_0 > 255) {
    tmp_0 = 255;
  }

  frame[3] = (uint8_T)tmp_0;
  tmp = rt_roundd_snf(model1_mod(256.0 - model1_mod((real_T)((((uint8_T)tmp_4 +
    tmp_2) + (uint8_T)tmp_1) + tmp_0))));
  if (tmp < 256.0) {
    if (tmp >= 0.0) {
      frame[4] = (uint8_T)tmp;
    } else {
      frame[4] = 0U;
    }
  } else {
    frame[4] = MAX_uint8_T;
  }

  /* End of MATLAB Function: '<S6>/Arduino output1' */

  /* MATLABSystem: '<S6>/Serial Transmit2' */
  varargin_9 = 85U;
  varargin_10 = 170U;
  MW_Serial_write(model1_DW.obj.port, &frame[0], 5.0,
                  model1_DW.obj.dataSizeInBytes, model1_DW.obj.sendModeEnum,
                  model1_DW.obj.dataType, model1_DW.obj.sendFormatEnum, 2.0,
                  '\x00', &varargin_9, 1.0, &varargin_10, 1.0);

  /* End of Outputs for SubSystem: '<Root>/Subsystem' */

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.05, which is the step size
   * of the task. Size of "clockTick2" ensures timer will not overflow during the
   * application lifespan selected.
   */
  model1_M->Timing.clockTick2++;
}

/* Model initialize function */
void model1_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&model1_M->solverInfo, &model1_M->Timing.simTimeStep);
    rtsiSetTPtr(&model1_M->solverInfo, &rtmGetTPtr(model1_M));
    rtsiSetStepSizePtr(&model1_M->solverInfo, &model1_M->Timing.stepSize0);
    rtsiSetdXPtr(&model1_M->solverInfo, &model1_M->derivs);
    rtsiSetContStatesPtr(&model1_M->solverInfo, (real_T **)
                         &model1_M->contStates);
    rtsiSetNumContStatesPtr(&model1_M->solverInfo,
      &model1_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&model1_M->solverInfo,
      &model1_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&model1_M->solverInfo,
      &model1_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&model1_M->solverInfo,
      &model1_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&model1_M->solverInfo, (boolean_T**)
      &model1_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&model1_M->solverInfo, (&rtmGetErrorStatus(model1_M)));
    rtsiSetRTModelPtr(&model1_M->solverInfo, model1_M);
  }

  rtsiSetSimTimeStep(&model1_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&model1_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&model1_M->solverInfo, false);
  model1_M->intgData.y = model1_M->odeY;
  model1_M->intgData.f[0] = model1_M->odeF[0];
  model1_M->intgData.f[1] = model1_M->odeF[1];
  model1_M->intgData.f[2] = model1_M->odeF[2];
  model1_M->contStates = ((X_model1_T *) &model1_X);
  model1_M->contStateDisabled = ((XDis_model1_T *) &model1_XDis);
  model1_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&model1_M->solverInfo, (void *)&model1_M->intgData);
  rtsiSetSolverName(&model1_M->solverInfo,"ode3");
  rtmSetTPtr(model1_M, &model1_M->Timing.tArray[0]);
  rtmSetTFinal(model1_M, 500.0);
  model1_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  model1_M->Sizes.checksums[0] = (4243904495U);
  model1_M->Sizes.checksums[1] = (4110769637U);
  model1_M->Sizes.checksums[2] = (363275819U);
  model1_M->Sizes.checksums[3] = (4014609116U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[10];
    model1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(model1_M->extModeInfo,
      &model1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(model1_M->extModeInfo, model1_M->Sizes.checksums);
    rteiSetTFinalTicks(model1_M->extModeInfo, 500000);
  }

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  model1_X.Integrator_CSTATE = model1_P.Integrator_IC;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn1' */
  model1_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  model1_X.Integrator1_CSTATE = model1_P.Integrator1_IC;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  model1_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative2' */
  model1_DW.TimeStampA = (rtInf);
  model1_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  model1_DW.TimeStampA_i = (rtInf);
  model1_DW.TimeStampB_a = (rtInf);

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subsystem' */
  /* Start for MATLABSystem: '<S6>/Serial Transmit2' */
  model1_DW.obj.matlabCodegenIsDeleted = false;
  model1_DW.obj.isInitialized = 1L;
  model1_DW.obj.port = 1.0;
  model1_DW.obj.dataSizeInBytes = 1.0;
  model1_DW.obj.dataType = 0.0;
  model1_DW.obj.sendModeEnum = 0.0;
  model1_DW.obj.sendFormatEnum = 0.0;
  MW_SCI_Open(1);
  model1_DW.obj.isSetupComplete = true;

  /* End of SystemInitialize for SubSystem: '<Root>/Subsystem' */

  /* SystemInitialize for MATLAB Function: '<Root>/MATLAB Function1' */
  model1_MATLABFunction1_Init(&model1_DW.sf_MATLABFunction1);

  /* SystemInitialize for MATLAB Function: '<Root>/MATLAB Function2' */
  model1_MATLABFunction1_Init(&model1_DW.sf_MATLABFunction2);

  /* Start for MATLABSystem: '<Root>/Serial Receive1' */
  model1_DW.obj_e.matlabCodegenIsDeleted = false;
  model1_DW.obj_e.isInitialized = 1L;
  MW_SCI_Open(1);
  model1_DW.obj_e.isSetupComplete = true;
}

/* Model terminate function */
void model1_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Receive1' */
  if (!model1_DW.obj_e.matlabCodegenIsDeleted) {
    model1_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Receive1' */
  /* Terminate for Atomic SubSystem: '<Root>/Subsystem' */
  /* Terminate for MATLABSystem: '<S6>/Serial Transmit2' */
  if (!model1_DW.obj.matlabCodegenIsDeleted) {
    model1_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S6>/Serial Transmit2' */
  /* End of Terminate for SubSystem: '<Root>/Subsystem' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
