/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: car_speed_control_uart_test.c
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

#include "car_speed_control_uart_test.h"
#include "rtwtypes.h"
#include <math.h>
#include "car_speed_control_uart_test_private.h"
#include <stddef.h>
#include "rt_nonfinite.h"

/* Block signals (default storage) */
B_car_speed_control_uart_test_T car_speed_control_uart_test_B;

/* Continuous states */
X_car_speed_control_uart_test_T car_speed_control_uart_test_X;

/* Disabled State Vector */
XDis_car_speed_control_uart_t_T car_speed_control_uart_tes_XDis;

/* Block states (default storage) */
DW_car_speed_control_uart_tes_T car_speed_control_uart_test_DW;

/* Real-time model */
static RT_MODEL_car_speed_control_ua_T car_speed_control_uart_test_M_;
RT_MODEL_car_speed_control_ua_T *const car_speed_control_uart_test_M =
  &car_speed_control_uart_test_M_;

/* Forward declaration for local functions */
static real_T car_speed_control_uart_test_mod(real_T x);
static real_T car_speed_control_uart_te_mod_e(real_T x);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void car_speed_control_uart_test_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[2] = ((boolean_T)rtmStepTask(car_speed_control_uart_test_M, 2));
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
  if (car_speed_control_uart_test_M->Timing.TaskCounters.TID[1] == 0) {
    car_speed_control_uart_test_M->Timing.RateInteraction.TID1_2 =
      (car_speed_control_uart_test_M->Timing.TaskCounters.TID[2] == 0);
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (car_speed_control_uart_test_M->Timing.TaskCounters.TID[2])++;
  if ((car_speed_control_uart_test_M->Timing.TaskCounters.TID[2]) > 1) {/* Sample time: [1.0s, 0.0s] */
    car_speed_control_uart_test_M->Timing.TaskCounters.TID[2] = 0;
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
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  car_speed_control_uart_test_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  car_speed_control_uart_test_step0();
  car_speed_control_uart_test_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  car_speed_control_uart_test_step0();
  car_speed_control_uart_test_derivatives();

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

/* Function for MATLAB Function: '<Root>/Arduino output' */
static real_T car_speed_control_uart_test_mod(real_T x)
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

/* Function for MATLAB Function: '<Root>/Arduino output' */
static real_T car_speed_control_uart_te_mod_e(real_T x)
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
void car_speed_control_uart_test_step0(void) /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(car_speed_control_uart_test_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&car_speed_control_uart_test_M->solverInfo,
                          ((car_speed_control_uart_test_M->Timing.clockTick0+1)*
      car_speed_control_uart_test_M->Timing.stepSize0));

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(car_speed_control_uart_test_M)) {
    car_speed_control_uart_test_M->Timing.t[0] = rtsiGetT
      (&car_speed_control_uart_test_M->solverInfo);
  }

  {
    real_T rtb_Derivative1;
    real_T rtb_error;
    real_T tmp_0;
    real_T *lastU;
    uint8_T rtb_frame[7];
    uint8_T tmp_1;
    uint8_T tmp_2;
    boolean_T tmp;

    /* RateTransition generated from: '<Root>/error' incorporates:
     *  RateTransition generated from: '<Root>/Derivative1'
     *  RateTransition generated from: '<Root>/Integrator'
     */
    tmp = rtmIsMajorTimeStep(car_speed_control_uart_test_M);
    if (tmp && car_speed_control_uart_test_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition generated from: '<Root>/error' */
      car_speed_control_uart_test_B.TmpRTBAterrorInport1 =
        car_speed_control_uart_test_DW.TmpRTBAterrorInport1_Buffer0;

      /* RateTransition generated from: '<Root>/Sum' */
      car_speed_control_uart_test_B.TmpRTBAtSumInport1 =
        car_speed_control_uart_test_DW.TmpRTBAtSumInport1_Buffer0;

      /* RateTransition generated from: '<Root>/Derivative1' */
      car_speed_control_uart_test_B.error =
        car_speed_control_uart_test_DW.TmpRTBAtDerivative1Inport1_Buff;
    }

    /* End of RateTransition generated from: '<Root>/error' */

    /* Derivative: '<Root>/Derivative1' */
    rtb_Derivative1 = car_speed_control_uart_test_M->Timing.t[0];
    if ((car_speed_control_uart_test_DW.TimeStampA >= rtb_Derivative1) &&
        (car_speed_control_uart_test_DW.TimeStampB >= rtb_Derivative1)) {
      rtb_Derivative1 = 0.0;
    } else {
      rtb_error = car_speed_control_uart_test_DW.TimeStampA;
      lastU = &car_speed_control_uart_test_DW.LastUAtTimeA;
      if (car_speed_control_uart_test_DW.TimeStampA <
          car_speed_control_uart_test_DW.TimeStampB) {
        if (car_speed_control_uart_test_DW.TimeStampB < rtb_Derivative1) {
          rtb_error = car_speed_control_uart_test_DW.TimeStampB;
          lastU = &car_speed_control_uart_test_DW.LastUAtTimeB;
        }
      } else if (car_speed_control_uart_test_DW.TimeStampA >= rtb_Derivative1) {
        rtb_error = car_speed_control_uart_test_DW.TimeStampB;
        lastU = &car_speed_control_uart_test_DW.LastUAtTimeB;
      }

      rtb_Derivative1 = (car_speed_control_uart_test_B.error - *lastU) /
        (rtb_Derivative1 - rtb_error);
    }

    /* End of Derivative: '<Root>/Derivative1' */

    /* Sum: '<Root>/error' incorporates:
     *  Gain: '<Root>/Kd'
     *  Gain: '<Root>/Ki'
     *  Integrator: '<Root>/Integrator'
     *  Sum: '<Root>/Sum'
     */
    rtb_error = ((car_speed_control_uart_test_P.Ki_Gain *
                  car_speed_control_uart_test_X.Integrator_CSTATE +
                  car_speed_control_uart_test_B.TmpRTBAtSumInport1) +
                 car_speed_control_uart_test_P.Kd_Gain * rtb_Derivative1) +
      car_speed_control_uart_test_B.TmpRTBAterrorInport1;

    /* MATLAB Function: '<Root>/Arduino output' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    rtb_frame[0] = 170U;
    rtb_Derivative1 = floor(rtb_error);
    if (rtb_Derivative1 < 256.0) {
      if (rtb_Derivative1 >= 0.0) {
        rtb_frame[1] = (uint8_T)rtb_Derivative1;
      } else {
        rtb_frame[1] = 0U;
      }
    } else {
      rtb_frame[1] = MAX_uint8_T;
    }

    rtb_error = floor(car_speed_control_uart_test_mod(rtb_error * 100.0));
    if (rtb_error < 256.0) {
      if (rtb_error >= 0.0) {
        rtb_frame[2] = (uint8_T)rtb_error;
      } else {
        rtb_frame[2] = 0U;
      }
    } else {
      rtb_frame[2] = MAX_uint8_T;
    }

    rtb_error = floor(car_speed_control_uart_test_P.Constant1_Value);
    if (rtb_error < 256.0) {
      if (rtb_error >= 0.0) {
        rtb_frame[3] = (uint8_T)rtb_error;
      } else {
        rtb_frame[3] = 0U;
      }
    } else {
      rtb_frame[3] = MAX_uint8_T;
    }

    tmp_0 = floor(car_speed_control_uart_test_mod
                  (car_speed_control_uart_test_P.Constant1_Value * 100.0));
    if (tmp_0 < 256.0) {
      if (tmp_0 >= 0.0) {
        rtb_frame[4] = (uint8_T)tmp_0;
      } else {
        rtb_frame[4] = 0U;
      }
    } else {
      rtb_frame[4] = MAX_uint8_T;
    }

    if (rtb_Derivative1 < 256.0) {
      if (rtb_Derivative1 >= 0.0) {
        tmp_1 = (uint8_T)rtb_Derivative1;
      } else {
        tmp_1 = 0U;
      }
    } else {
      tmp_1 = MAX_uint8_T;
    }

    if (rtb_error < 256.0) {
      if (rtb_error >= 0.0) {
        tmp_2 = (uint8_T)rtb_error;
      } else {
        tmp_2 = 0U;
      }
    } else {
      tmp_2 = MAX_uint8_T;
    }

    rtb_Derivative1 = rt_roundd_snf(car_speed_control_uart_te_mod_e(256.0 -
      car_speed_control_uart_te_mod_e((real_T)((((tmp_1 + rtb_frame[2]) + tmp_2)
      + rtb_frame[4]) + 170))));
    if (rtb_Derivative1 < 256.0) {
      if (rtb_Derivative1 >= 0.0) {
        rtb_frame[5] = (uint8_T)rtb_Derivative1;
      } else {
        rtb_frame[5] = 0U;
      }
    } else {
      rtb_frame[5] = MAX_uint8_T;
    }

    rtb_frame[6] = 85U;

    /* End of MATLAB Function: '<Root>/Arduino output' */

    /* MATLABSystem: '<Root>/Serial Transmit1' */
    MW_Serial_write(car_speed_control_uart_test_DW.obj.port, &rtb_frame[0], 7.0,
                    car_speed_control_uart_test_DW.obj.dataSizeInBytes,
                    car_speed_control_uart_test_DW.obj.sendModeEnum,
                    car_speed_control_uart_test_DW.obj.dataType,
                    car_speed_control_uart_test_DW.obj.sendFormatEnum, 2.0,
                    '\x00', NULL, 0.0, NULL, 0.0);

    /* RateTransition generated from: '<Root>/Integrator' */
    if (tmp && car_speed_control_uart_test_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition generated from: '<Root>/Integrator' */
      car_speed_control_uart_test_B.error_g =
        car_speed_control_uart_test_DW.TmpRTBAtIntegratorInport1_Buffe;
    }
  }

  if (rtmIsMajorTimeStep(car_speed_control_uart_test_M)) {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative1' */
    if (car_speed_control_uart_test_DW.TimeStampA == (rtInf)) {
      car_speed_control_uart_test_DW.TimeStampA =
        car_speed_control_uart_test_M->Timing.t[0];
      lastU = &car_speed_control_uart_test_DW.LastUAtTimeA;
    } else if (car_speed_control_uart_test_DW.TimeStampB == (rtInf)) {
      car_speed_control_uart_test_DW.TimeStampB =
        car_speed_control_uart_test_M->Timing.t[0];
      lastU = &car_speed_control_uart_test_DW.LastUAtTimeB;
    } else if (car_speed_control_uart_test_DW.TimeStampA <
               car_speed_control_uart_test_DW.TimeStampB) {
      car_speed_control_uart_test_DW.TimeStampA =
        car_speed_control_uart_test_M->Timing.t[0];
      lastU = &car_speed_control_uart_test_DW.LastUAtTimeA;
    } else {
      car_speed_control_uart_test_DW.TimeStampB =
        car_speed_control_uart_test_M->Timing.t[0];
      lastU = &car_speed_control_uart_test_DW.LastUAtTimeB;
    }

    *lastU = car_speed_control_uart_test_B.error;

    /* End of Update for Derivative: '<Root>/Derivative1' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(car_speed_control_uart_test_M)) {
    rt_ertODEUpdateContinuousStates(&car_speed_control_uart_test_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++car_speed_control_uart_test_M->Timing.clockTick0;
    car_speed_control_uart_test_M->Timing.t[0] = rtsiGetSolverStopTime
      (&car_speed_control_uart_test_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.5, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    car_speed_control_uart_test_M->Timing.clockTick1++;
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void car_speed_control_uart_test_derivatives(void)
{
  XDot_car_speed_control_uart_t_T *_rtXdot;
  _rtXdot = ((XDot_car_speed_control_uart_t_T *)
             car_speed_control_uart_test_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = car_speed_control_uart_test_B.error_g;
}

/* Model step function for TID2 */
void car_speed_control_uart_test_step2(void) /* Sample time: [1.0s, 0.0s] */
{
  real_T rtb_Gain2;
  uint8_T tmp[7];
  uint8_T b_status;

  /* MATLABSystem: '<Root>/Serial Receive' */
  MW_Serial_read(1, 7U, &tmp[0], &b_status, NULL, 0.0, NULL, 0.0);

  /* Gain: '<Root>/Gain2' incorporates:
   *  MATLAB Function: '<Root>/Arduino Input'
   */
  rtb_Gain2 = car_speed_control_uart_test_P.Gain2_Gain * 0.0;

  /* RateTransition generated from: '<Root>/error' */
  car_speed_control_uart_test_DW.TmpRTBAterrorInport1_Buffer0 = rtb_Gain2;

  /* Gain: '<Root>/Kp' */
  rtb_Gain2 = car_speed_control_uart_test_P.Kp_Gain * 0.0;

  /* RateTransition generated from: '<Root>/Sum' */
  car_speed_control_uart_test_DW.TmpRTBAtSumInport1_Buffer0 = rtb_Gain2;

  /* RateTransition generated from: '<Root>/Derivative1' */
  car_speed_control_uart_test_DW.TmpRTBAtDerivative1Inport1_Buff = 0.0;

  /* RateTransition generated from: '<Root>/Integrator' */
  car_speed_control_uart_test_DW.TmpRTBAtIntegratorInport1_Buffe = 0.0;
}

/* Model initialize function */
void car_speed_control_uart_test_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&car_speed_control_uart_test_M->solverInfo,
                          &car_speed_control_uart_test_M->Timing.simTimeStep);
    rtsiSetTPtr(&car_speed_control_uart_test_M->solverInfo, &rtmGetTPtr
                (car_speed_control_uart_test_M));
    rtsiSetStepSizePtr(&car_speed_control_uart_test_M->solverInfo,
                       &car_speed_control_uart_test_M->Timing.stepSize0);
    rtsiSetdXPtr(&car_speed_control_uart_test_M->solverInfo,
                 &car_speed_control_uart_test_M->derivs);
    rtsiSetContStatesPtr(&car_speed_control_uart_test_M->solverInfo, (real_T **)
                         &car_speed_control_uart_test_M->contStates);
    rtsiSetNumContStatesPtr(&car_speed_control_uart_test_M->solverInfo,
      &car_speed_control_uart_test_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&car_speed_control_uart_test_M->solverInfo,
      &car_speed_control_uart_test_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr
      (&car_speed_control_uart_test_M->solverInfo,
       &car_speed_control_uart_test_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&car_speed_control_uart_test_M->solverInfo,
      &car_speed_control_uart_test_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&car_speed_control_uart_test_M->solverInfo,
      (boolean_T**) &car_speed_control_uart_test_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&car_speed_control_uart_test_M->solverInfo,
                          (&rtmGetErrorStatus(car_speed_control_uart_test_M)));
    rtsiSetRTModelPtr(&car_speed_control_uart_test_M->solverInfo,
                      car_speed_control_uart_test_M);
  }

  rtsiSetSimTimeStep(&car_speed_control_uart_test_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange
    (&car_speed_control_uart_test_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&car_speed_control_uart_test_M->solverInfo, false);
  car_speed_control_uart_test_M->intgData.y =
    car_speed_control_uart_test_M->odeY;
  car_speed_control_uart_test_M->intgData.f[0] =
    car_speed_control_uart_test_M->odeF[0];
  car_speed_control_uart_test_M->intgData.f[1] =
    car_speed_control_uart_test_M->odeF[1];
  car_speed_control_uart_test_M->intgData.f[2] =
    car_speed_control_uart_test_M->odeF[2];
  car_speed_control_uart_test_M->contStates = ((X_car_speed_control_uart_test_T *)
    &car_speed_control_uart_test_X);
  car_speed_control_uart_test_M->contStateDisabled =
    ((XDis_car_speed_control_uart_t_T *) &car_speed_control_uart_tes_XDis);
  car_speed_control_uart_test_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&car_speed_control_uart_test_M->solverInfo, (void *)
                    &car_speed_control_uart_test_M->intgData);
  rtsiSetSolverName(&car_speed_control_uart_test_M->solverInfo,"ode3");
  rtmSetTPtr(car_speed_control_uart_test_M,
             &car_speed_control_uart_test_M->Timing.tArray[0]);
  car_speed_control_uart_test_M->Timing.stepSize0 = 0.5;

  /* Start for RateTransition generated from: '<Root>/error' */
  car_speed_control_uart_test_B.TmpRTBAterrorInport1 =
    car_speed_control_uart_test_P.TmpRTBAterrorInport1_InitialCon;

  /* Start for RateTransition generated from: '<Root>/Sum' */
  car_speed_control_uart_test_B.TmpRTBAtSumInport1 =
    car_speed_control_uart_test_P.TmpRTBAtSumInport1_InitialCondi;

  /* Start for RateTransition generated from: '<Root>/Derivative1' */
  car_speed_control_uart_test_B.error =
    car_speed_control_uart_test_P.TmpRTBAtDerivative1Inport1_Init;

  /* Start for RateTransition generated from: '<Root>/Integrator' */
  car_speed_control_uart_test_B.error_g =
    car_speed_control_uart_test_P.TmpRTBAtIntegratorInport1_Initi;

  /* InitializeConditions for RateTransition generated from: '<Root>/error' */
  car_speed_control_uart_test_DW.TmpRTBAterrorInport1_Buffer0 =
    car_speed_control_uart_test_P.TmpRTBAterrorInport1_InitialCon;

  /* InitializeConditions for RateTransition generated from: '<Root>/Sum' */
  car_speed_control_uart_test_DW.TmpRTBAtSumInport1_Buffer0 =
    car_speed_control_uart_test_P.TmpRTBAtSumInport1_InitialCondi;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  car_speed_control_uart_test_X.Integrator_CSTATE =
    car_speed_control_uart_test_P.Integrator_IC;

  /* InitializeConditions for RateTransition generated from: '<Root>/Derivative1' */
  car_speed_control_uart_test_DW.TmpRTBAtDerivative1Inport1_Buff =
    car_speed_control_uart_test_P.TmpRTBAtDerivative1Inport1_Init;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  car_speed_control_uart_test_DW.TimeStampA = (rtInf);
  car_speed_control_uart_test_DW.TimeStampB = (rtInf);

  /* InitializeConditions for RateTransition generated from: '<Root>/Integrator' */
  car_speed_control_uart_test_DW.TmpRTBAtIntegratorInport1_Buffe =
    car_speed_control_uart_test_P.TmpRTBAtIntegratorInport1_Initi;

  /* Start for MATLABSystem: '<Root>/Serial Transmit1' */
  car_speed_control_uart_test_DW.obj.matlabCodegenIsDeleted = false;
  car_speed_control_uart_test_DW.obj.isInitialized = 1L;
  car_speed_control_uart_test_DW.obj.port = 1.0;
  car_speed_control_uart_test_DW.obj.dataSizeInBytes = 1.0;
  car_speed_control_uart_test_DW.obj.dataType = 0.0;
  car_speed_control_uart_test_DW.obj.sendModeEnum = 0.0;
  car_speed_control_uart_test_DW.obj.sendFormatEnum = 0.0;
  MW_SCI_Open(1);
  car_speed_control_uart_test_DW.obj.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Serial Receive' */
  car_speed_control_uart_test_DW.obj_b.matlabCodegenIsDeleted = false;
  car_speed_control_uart_test_DW.obj_b.isInitialized = 1L;
  MW_SCI_Open(1);
  car_speed_control_uart_test_DW.obj_b.isSetupComplete = true;
}

/* Model terminate function */
void car_speed_control_uart_test_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Transmit1' */
  if (!car_speed_control_uart_test_DW.obj.matlabCodegenIsDeleted) {
    car_speed_control_uart_test_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Transmit1' */

  /* Terminate for MATLABSystem: '<Root>/Serial Receive' */
  if (!car_speed_control_uart_test_DW.obj_b.matlabCodegenIsDeleted) {
    car_speed_control_uart_test_DW.obj_b.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Receive' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
