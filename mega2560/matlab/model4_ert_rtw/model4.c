/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model4.c
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
#include "rtwtypes.h"
#include "model4_private.h"
#include <math.h>
#include "rt_nonfinite.h"
#include <string.h>
#include <stddef.h>

/* Block signals (default storage) */
B_model4_T model4_B;

/* Continuous states */
X_model4_T model4_X;

/* Disabled State Vector */
XDis_model4_T model4_XDis;

/* Block states (default storage) */
DW_model4_T model4_DW;

/* Real-time model */
static RT_MODEL_model4_T model4_M_;
RT_MODEL_model4_T *const model4_M = &model4_M_;

/* Forward declaration for local functions */
static real_T model4_mod(real_T x);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void model4_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[2] = ((boolean_T)rtmStepTask(model4_M, 2));
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
  if (model4_M->Timing.TaskCounters.TID[1] == 0) {
    model4_M->Timing.RateInteraction.TID1_2 = (model4_M->
      Timing.TaskCounters.TID[2] == 0);
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (model4_M->Timing.TaskCounters.TID[2])++;
  if ((model4_M->Timing.TaskCounters.TID[2]) > 99) {/* Sample time: [0.1s, 0.0s] */
    model4_M->Timing.TaskCounters.TID[2] = 0;
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
  model4_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  model4_step0();
  model4_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  model4_step0();
  model4_derivatives();

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
 * Output and update for atomic system:
 *    '<Root>/MATLAB Function2'
 *    '<Root>/MATLAB Function3'
 */
void model4_MATLABFunction2(uint16_T rtu_u, real_T *rty_y)
{
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
static real_T model4_mod(real_T x)
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
void model4_step0(void)                /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  uint16_T rtb_v_target;
  if (rtmIsMajorTimeStep(model4_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&model4_M->solverInfo,((model4_M->Timing.clockTick0+1)*
      model4_M->Timing.stepSize0));

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(model4_M)) {
    model4_M->Timing.t[0] = rtsiGetT(&model4_M->solverInfo);
  }

  {
    real_T rtb_Derivative2;
    real_T rtb_steer_gain;
    real_T tmp_0;
    real_T *lastU;
    int16_T i;
    int16_T qY;
    uint16_T dutyL_u;
    uint16_T dutyR_u;
    int8_T tmp;
    uint8_T rtb_data_out[10];
    uint8_T b_dataOut;
    uint8_T b_status;
    boolean_T rtb_ready;
    boolean_T tmp_1;

    /* RateTransition generated from: '<Root>/Subsystem' */
    tmp_1 = rtmIsMajorTimeStep(model4_M);
    if (tmp_1) {
      /* MATLABSystem: '<Root>/Serial Receive1' */
      MW_Serial_read(1, 1U, &b_dataOut, &b_status, NULL, 0.0, NULL, 0.0);

      /* MATLAB Function: '<Root>/Arduino Input1' incorporates:
       *  MATLABSystem: '<Root>/Serial Receive1'
       * */
      rtb_ready = false;
      for (i = 0; i < 10; i++) {
        rtb_data_out[i] = 0U;
      }

      if (b_status == 1) {
        if (!model4_DW.collecting) {
          if (b_dataOut == 170) {
            model4_DW.buffer[0] = 170U;
            model4_DW.count = 1.0;
            model4_DW.collecting = true;
          }
        } else {
          if (b_dataOut == 170) {
            model4_DW.count = 1.0;
          }

          model4_DW.count++;
          model4_DW.buffer[(int16_T)model4_DW.count - 1] = b_dataOut;
          if (model4_DW.count == 10.0) {
            for (i = 0; i < 10; i++) {
              rtb_data_out[i] = model4_DW.buffer[i];
            }

            rtb_ready = true;
            model4_DW.count = 0.0;
            model4_DW.collecting = false;
          }
        }
      } else {
        for (i = 0; i < 10; i++) {
          model4_DW.buffer[i] = 0U;
        }

        model4_DW.count = 0.0;
        model4_DW.collecting = false;
      }

      /* End of MATLAB Function: '<Root>/Arduino Input1' */

      /* MATLAB Function: '<Root>/Arduino Input2' */
      for (i = 0; i < 10; i++) {
        model4_B.u[i] = rtb_data_out[i];
      }

      if (rtb_ready) {
        dutyL_u = rtb_data_out[1] - 1U;
        if (rtb_data_out[1] - 1U > rtb_data_out[1]) {
          dutyL_u = 0U;
        }

        dutyR_u = rtb_data_out[2] - 1U;
        if (rtb_data_out[2] - 1U > rtb_data_out[2]) {
          dutyR_u = 0U;
        }

        model4_DW.p_speed_L = ((real_T)(int16_T)dutyR_u / 100.0 + (real_T)
          (int16_T)dutyL_u) * 10.0;
        dutyL_u = rtb_data_out[3] - 1U;
        if (rtb_data_out[3] - 1U > rtb_data_out[3]) {
          dutyL_u = 0U;
        }

        dutyR_u = rtb_data_out[4] - 1U;
        if (rtb_data_out[4] - 1U > rtb_data_out[4]) {
          dutyR_u = 0U;
        }

        model4_DW.p_speed_R = ((real_T)(int16_T)dutyR_u / 100.0 + (real_T)
          (int16_T)dutyL_u) * 10.0;
        if (rtb_data_out[6] == 1) {
          model4_B.u[6] = 0U;
        }

        dutyL_u = model4_B.u[6] - 1U;
        if (model4_B.u[6] - 1U > model4_B.u[6]) {
          dutyL_u = 0U;
        }

        model4_DW.p_v_target = dutyL_u * 10U;
        memcpy((void *)&tmp, (void *)&rtb_data_out[5], (size_t)1 * sizeof(int8_T));
        if ((tmp <= 30) && (tmp >= -30)) {
          model4_DW.p_slope = tmp;
        }

        memcpy((void *)&tmp, (void *)&rtb_data_out[7], (size_t)1 * sizeof(int8_T));
        if ((tmp <= 30) && (tmp >= -30)) {
          model4_DW.p_steer = tmp;
        }
      }

      rtb_v_target = model4_DW.p_v_target;

      /* Gain: '<Root>/steer_gain' incorporates:
       *  MATLAB Function: '<Root>/Arduino Input2'
       */
      rtb_steer_gain = model4_P.steer_gain_Gain * (real_T)model4_DW.p_steer;

      /* Gain: '<Root>/slope_gain' incorporates:
       *  MATLAB Function: '<Root>/Arduino Input2'
       */
      i = model4_P.slope_gain_Gain * model4_DW.p_slope;

      /* MATLAB Function: '<Root>/MATLAB Function2' */
      model4_MATLABFunction2(rtb_v_target, &model4_B.y_j);

      /* DotProduct: '<Root>/Dot Product' incorporates:
       *  Gain: '<Root>/slope_gain'
       *  MATLAB Function: '<Root>/Arduino Input2'
       *  Sum: '<Root>/Add'
       *  Sum: '<Root>/Sum2'
       */
      model4_B.DotProduct = ((((real_T)rtb_v_target + rtb_steer_gain) + (real_T)
        i * 0.0625) - model4_DW.p_speed_L) * model4_B.y_j;
    }

    /* Derivative: '<Root>/Derivative1' incorporates:
     *  Derivative: '<Root>/Derivative2'
     */
    tmp_0 = model4_M->Timing.t[0];
    if ((model4_DW.TimeStampA >= tmp_0) && (model4_DW.TimeStampB >= tmp_0)) {
      rtb_Derivative2 = 0.0;
    } else {
      rtb_Derivative2 = model4_DW.TimeStampA;
      lastU = &model4_DW.LastUAtTimeA;
      if (model4_DW.TimeStampA < model4_DW.TimeStampB) {
        if (model4_DW.TimeStampB < tmp_0) {
          rtb_Derivative2 = model4_DW.TimeStampB;
          lastU = &model4_DW.LastUAtTimeB;
        }
      } else if (model4_DW.TimeStampA >= tmp_0) {
        rtb_Derivative2 = model4_DW.TimeStampB;
        lastU = &model4_DW.LastUAtTimeB;
      }

      rtb_Derivative2 = (model4_B.DotProduct - *lastU) / (tmp_0 -
        rtb_Derivative2);
    }

    /* End of Derivative: '<Root>/Derivative1' */

    /* Gain: '<Root>/Kd' */
    model4_B.Kd = model4_P.Kd_Gain * rtb_Derivative2;
    if (tmp_1) {
      /* Gain: '<Root>/Kp' */
      model4_B.Kp = model4_P.Kp_Gain * model4_B.DotProduct;

      /* MATLAB Function: '<Root>/MATLAB Function3' */
      model4_MATLABFunction2(rtb_v_target, &model4_B.y);

      /* DotProduct: '<Root>/Dot Product1' incorporates:
       *  Gain: '<Root>/slope_gain'
       *  Sum: '<Root>/Add1'
       *  Sum: '<Root>/Sum3'
       */
      model4_B.DotProduct1 = ((((real_T)rtb_v_target - rtb_steer_gain) + (real_T)
        i * 0.0625) - model4_DW.p_speed_R) * model4_B.y;

      /* Gain: '<Root>/Kp1' */
      model4_B.Kp1 = model4_P.Kp1_Gain * model4_B.DotProduct1;
    }

    /* MATLAB Function: '<Root>/MATLAB Function1' incorporates:
     *  Constant: '<Root>/Constant'
     *  Constant: '<Root>/Constant1'
     */
    rtb_steer_gain = 1000.0 / (model4_P.Constant1_Value -
      model4_P.Constant_Value);

    /* DotProduct: '<Root>/Dot Product2' incorporates:
     *  Gain: '<Root>/Ki'
     *  Integrator: '<Root>/Integrator'
     *  Sum: '<Root>/Sum'
     *  TransferFcn: '<Root>/Transfer Fcn1'
     */
    rtb_Derivative2 = floor(((model4_P.Ki_Gain * model4_X.Integrator_CSTATE +
      model4_B.Kp) + model4_P.TransferFcn1_C * model4_X.TransferFcn1_CSTATE) *
      model4_B.y_j);
    if (rtIsNaN(rtb_Derivative2) || rtIsInf(rtb_Derivative2)) {
      rtb_Derivative2 = 0.0;
    } else {
      rtb_Derivative2 = fmod(rtb_Derivative2, 65536.0);
    }

    /* MATLAB Function: '<Root>/MATLAB Function1' incorporates:
     *  Constant: '<Root>/Constant'
     *  DotProduct: '<Root>/Dot Product2'
     */
    rtb_Derivative2 = rt_roundd_snf((real_T)(rtb_Derivative2 < 0.0 ? -(int16_T)
      (uint16_T)-rtb_Derivative2 : (int16_T)(uint16_T)rtb_Derivative2) -
      model4_P.Constant_Value);
    if (rtb_Derivative2 < 32768.0) {
      if (rtb_Derivative2 >= -32768.0) {
        i = (int16_T)rtb_Derivative2;
      } else {
        i = MIN_int16_T;
      }
    } else {
      i = MAX_int16_T;
    }

    rtb_Derivative2 = rt_roundd_snf((real_T)i * rtb_steer_gain);
    if (rtb_Derivative2 < 32768.0) {
      if (rtb_Derivative2 >= -32768.0) {
        i = (int16_T)rtb_Derivative2;
      } else {
        i = MIN_int16_T;
      }
    } else {
      i = MAX_int16_T;
    }

    if (i < -32268) {
      qY = MIN_int16_T;
    } else {
      qY = i - 500;
    }

    /* DotProduct: '<Root>/Dot Product3' incorporates:
     *  Gain: '<Root>/Ki1'
     *  Integrator: '<Root>/Integrator1'
     *  Sum: '<Root>/Sum1'
     *  TransferFcn: '<Root>/Transfer Fcn'
     */
    rtb_Derivative2 = floor(((model4_P.Ki1_Gain * model4_X.Integrator1_CSTATE +
      model4_B.Kp1) + model4_P.TransferFcn_C * model4_X.TransferFcn_CSTATE) *
      model4_B.y);
    if (rtIsNaN(rtb_Derivative2) || rtIsInf(rtb_Derivative2)) {
      rtb_Derivative2 = 0.0;
    } else {
      rtb_Derivative2 = fmod(rtb_Derivative2, 65536.0);
    }

    /* MATLAB Function: '<Root>/MATLAB Function1' incorporates:
     *  Constant: '<Root>/Constant'
     *  DotProduct: '<Root>/Dot Product3'
     */
    rtb_Derivative2 = rt_roundd_snf((real_T)(rtb_Derivative2 < 0.0 ? -(int16_T)
      (uint16_T)-rtb_Derivative2 : (int16_T)(uint16_T)rtb_Derivative2) -
      model4_P.Constant_Value);
    if (rtb_Derivative2 < 32768.0) {
      if (rtb_Derivative2 >= -32768.0) {
        i = (int16_T)rtb_Derivative2;
      } else {
        i = MIN_int16_T;
      }
    } else {
      i = MAX_int16_T;
    }

    rtb_Derivative2 = rt_roundd_snf((real_T)i * rtb_steer_gain);
    if (rtb_Derivative2 < 32768.0) {
      if (rtb_Derivative2 >= -32768.0) {
        i = (int16_T)rtb_Derivative2;
      } else {
        i = MIN_int16_T;
      }
    } else {
      i = MAX_int16_T;
    }

    if (i < -32268) {
      i = MIN_int16_T;
    } else {
      i -= 500;
    }

    memcpy((void *)&dutyL_u, (void *)&qY, (size_t)1 * sizeof(uint16_T));
    memcpy((void *)&dutyR_u, (void *)&i, (size_t)1 * sizeof(uint16_T));

    /* RateTransition generated from: '<Root>/Subsystem' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    if (tmp_1 && model4_M->Timing.RateInteraction.TID1_2) {
      model4_DW.byteL1_Buffer = (uint8_T)(dutyL_u >> 8);

      /* RateTransition generated from: '<Root>/Subsystem' incorporates:
       *  MATLAB Function: '<Root>/MATLAB Function1'
       */
      model4_DW.byteL2_Buffer = (uint8_T)(dutyL_u & 255U);

      /* RateTransition generated from: '<Root>/Subsystem' incorporates:
       *  MATLAB Function: '<Root>/MATLAB Function1'
       */
      model4_DW.byteR1_Buffer = (uint8_T)(dutyR_u >> 8);

      /* RateTransition generated from: '<Root>/Subsystem' incorporates:
       *  MATLAB Function: '<Root>/MATLAB Function1'
       */
      model4_DW.byteR2_Buffer = (uint8_T)(dutyR_u & 255U);
    }

    /* Derivative: '<Root>/Derivative2' */
    if ((model4_DW.TimeStampA_l >= tmp_0) && (model4_DW.TimeStampB_i >= tmp_0))
    {
      rtb_Derivative2 = 0.0;
    } else {
      rtb_Derivative2 = model4_DW.TimeStampA_l;
      lastU = &model4_DW.LastUAtTimeA_k;
      if (model4_DW.TimeStampA_l < model4_DW.TimeStampB_i) {
        if (model4_DW.TimeStampB_i < tmp_0) {
          rtb_Derivative2 = model4_DW.TimeStampB_i;
          lastU = &model4_DW.LastUAtTimeB_o;
        }
      } else if (model4_DW.TimeStampA_l >= tmp_0) {
        rtb_Derivative2 = model4_DW.TimeStampB_i;
        lastU = &model4_DW.LastUAtTimeB_o;
      }

      rtb_Derivative2 = (model4_B.DotProduct1 - *lastU) / (tmp_0 -
        rtb_Derivative2);
    }

    /* Gain: '<Root>/Kd1' */
    model4_B.Kd1 = model4_P.Kd1_Gain * rtb_Derivative2;
  }

  if (rtmIsMajorTimeStep(model4_M)) {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative1' */
    if (model4_DW.TimeStampA == (rtInf)) {
      model4_DW.TimeStampA = model4_M->Timing.t[0];
      lastU = &model4_DW.LastUAtTimeA;
    } else if (model4_DW.TimeStampB == (rtInf)) {
      model4_DW.TimeStampB = model4_M->Timing.t[0];
      lastU = &model4_DW.LastUAtTimeB;
    } else if (model4_DW.TimeStampA < model4_DW.TimeStampB) {
      model4_DW.TimeStampA = model4_M->Timing.t[0];
      lastU = &model4_DW.LastUAtTimeA;
    } else {
      model4_DW.TimeStampB = model4_M->Timing.t[0];
      lastU = &model4_DW.LastUAtTimeB;
    }

    *lastU = model4_B.DotProduct;

    /* End of Update for Derivative: '<Root>/Derivative1' */

    /* Update for Derivative: '<Root>/Derivative2' */
    if (model4_DW.TimeStampA_l == (rtInf)) {
      model4_DW.TimeStampA_l = model4_M->Timing.t[0];
      lastU = &model4_DW.LastUAtTimeA_k;
    } else if (model4_DW.TimeStampB_i == (rtInf)) {
      model4_DW.TimeStampB_i = model4_M->Timing.t[0];
      lastU = &model4_DW.LastUAtTimeB_o;
    } else if (model4_DW.TimeStampA_l < model4_DW.TimeStampB_i) {
      model4_DW.TimeStampA_l = model4_M->Timing.t[0];
      lastU = &model4_DW.LastUAtTimeA_k;
    } else {
      model4_DW.TimeStampB_i = model4_M->Timing.t[0];
      lastU = &model4_DW.LastUAtTimeB_o;
    }

    *lastU = model4_B.DotProduct1;

    /* End of Update for Derivative: '<Root>/Derivative2' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(model4_M)) {
    rt_ertODEUpdateContinuousStates(&model4_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++model4_M->Timing.clockTick0;
    model4_M->Timing.t[0] = rtsiGetSolverStopTime(&model4_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    model4_M->Timing.clockTick1++;
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void model4_derivatives(void)
{
  XDot_model4_T *_rtXdot;
  _rtXdot = ((XDot_model4_T *) model4_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = model4_B.DotProduct;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = model4_P.TransferFcn1_A *
    model4_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += model4_B.Kd;

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = model4_B.DotProduct1;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = model4_P.TransferFcn_A *
    model4_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += model4_B.Kd1;
}

/* Model step function for TID2 */
void model4_step2(void)                /* Sample time: [0.1s, 0.0s] */
{
  real_T tmp;
  uint8_T rtb_frame[5];
  uint8_T varargin_10;
  uint8_T varargin_9;

  /* Outputs for Atomic SubSystem: '<Root>/Subsystem' */
  /* MATLAB Function: '<S6>/Arduino output1' incorporates:
   *  RateTransition generated from: '<Root>/Subsystem'
   * */
  rtb_frame[0] = model4_DW.byteL1_Buffer;
  rtb_frame[1] = model4_DW.byteL2_Buffer;
  rtb_frame[2] = model4_DW.byteR1_Buffer;
  rtb_frame[3] = model4_DW.byteR2_Buffer;
  tmp = rt_roundd_snf(model4_mod(256.0 - model4_mod((real_T)
    (((model4_DW.byteL1_Buffer + model4_DW.byteL2_Buffer) +
      model4_DW.byteR1_Buffer) + model4_DW.byteR2_Buffer))));
  if (tmp < 256.0) {
    if (tmp >= 0.0) {
      rtb_frame[4] = (uint8_T)tmp;
    } else {
      rtb_frame[4] = 0U;
    }
  } else {
    rtb_frame[4] = MAX_uint8_T;
  }

  /* End of MATLAB Function: '<S6>/Arduino output1' */

  /* MATLABSystem: '<S6>/Serial Transmit2' */
  varargin_9 = 85U;
  varargin_10 = 170U;
  MW_Serial_write(model4_DW.obj.port, &rtb_frame[0], 5.0,
                  model4_DW.obj.dataSizeInBytes, model4_DW.obj.sendModeEnum,
                  model4_DW.obj.dataType, model4_DW.obj.sendFormatEnum, 2.0,
                  '\x00', &varargin_9, 1.0, &varargin_10, 1.0);

  /* End of Outputs for SubSystem: '<Root>/Subsystem' */
}

/* Model initialize function */
void model4_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&model4_M->solverInfo, &model4_M->Timing.simTimeStep);
    rtsiSetTPtr(&model4_M->solverInfo, &rtmGetTPtr(model4_M));
    rtsiSetStepSizePtr(&model4_M->solverInfo, &model4_M->Timing.stepSize0);
    rtsiSetdXPtr(&model4_M->solverInfo, &model4_M->derivs);
    rtsiSetContStatesPtr(&model4_M->solverInfo, (real_T **)
                         &model4_M->contStates);
    rtsiSetNumContStatesPtr(&model4_M->solverInfo,
      &model4_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&model4_M->solverInfo,
      &model4_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&model4_M->solverInfo,
      &model4_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&model4_M->solverInfo,
      &model4_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&model4_M->solverInfo, (boolean_T**)
      &model4_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&model4_M->solverInfo, (&rtmGetErrorStatus(model4_M)));
    rtsiSetRTModelPtr(&model4_M->solverInfo, model4_M);
  }

  rtsiSetSimTimeStep(&model4_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&model4_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&model4_M->solverInfo, false);
  model4_M->intgData.y = model4_M->odeY;
  model4_M->intgData.f[0] = model4_M->odeF[0];
  model4_M->intgData.f[1] = model4_M->odeF[1];
  model4_M->intgData.f[2] = model4_M->odeF[2];
  model4_M->contStates = ((X_model4_T *) &model4_X);
  model4_M->contStateDisabled = ((XDis_model4_T *) &model4_XDis);
  model4_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&model4_M->solverInfo, (void *)&model4_M->intgData);
  rtsiSetSolverName(&model4_M->solverInfo,"ode3");
  rtmSetTPtr(model4_M, &model4_M->Timing.tArray[0]);
  model4_M->Timing.stepSize0 = 0.001;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  model4_DW.TimeStampA = (rtInf);
  model4_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  model4_X.Integrator_CSTATE = model4_P.Integrator_IC;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn1' */
  model4_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  model4_X.Integrator1_CSTATE = model4_P.Integrator1_IC;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  model4_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative2' */
  model4_DW.TimeStampA_l = (rtInf);
  model4_DW.TimeStampB_i = (rtInf);

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subsystem' */
  /* Start for MATLABSystem: '<S6>/Serial Transmit2' */
  model4_DW.obj.matlabCodegenIsDeleted = false;
  model4_DW.obj.isInitialized = 1L;
  model4_DW.obj.port = 1.0;
  model4_DW.obj.dataSizeInBytes = 1.0;
  model4_DW.obj.dataType = 0.0;
  model4_DW.obj.sendModeEnum = 0.0;
  model4_DW.obj.sendFormatEnum = 0.0;
  MW_SCI_Open(1);
  model4_DW.obj.isSetupComplete = true;

  /* End of SystemInitialize for SubSystem: '<Root>/Subsystem' */

  /* Start for MATLABSystem: '<Root>/Serial Receive1' */
  model4_DW.obj_e.matlabCodegenIsDeleted = false;
  model4_DW.obj_e.isInitialized = 1L;
  MW_SCI_Open(1);
  model4_DW.obj_e.isSetupComplete = true;
}

/* Model terminate function */
void model4_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Receive1' */
  if (!model4_DW.obj_e.matlabCodegenIsDeleted) {
    model4_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Receive1' */

  /* Terminate for Atomic SubSystem: '<Root>/Subsystem' */
  /* Terminate for MATLABSystem: '<S6>/Serial Transmit2' */
  if (!model4_DW.obj.matlabCodegenIsDeleted) {
    model4_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S6>/Serial Transmit2' */
  /* End of Terminate for SubSystem: '<Root>/Subsystem' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
