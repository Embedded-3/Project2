/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: car_speed_control_uart_proto2_2.c
 *
 * Code generated for Simulink model 'car_speed_control_uart_proto2_2'.
 *
 * Model version                  : 1.86
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Sun May 25 16:38:11 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "car_speed_control_uart_proto2_2.h"
#include "rtwtypes.h"
#include "car_speed_control_uart_proto2_2_private.h"
#include <stddef.h>
#include "rt_nonfinite.h"
#include <math.h>

/* Block signals (default storage) */
B_car_speed_control_uart_prot_T car_speed_control_uart_proto2_B;

/* Continuous states */
X_car_speed_control_uart_prot_T car_speed_control_uart_proto2_X;

/* Disabled State Vector */
XDis_car_speed_control_uart_p_T car_speed_control_uart_pro_XDis;

/* Block states (default storage) */
DW_car_speed_control_uart_pro_T car_speed_control_uart_proto_DW;

/* Real-time model */
static RT_MODEL_car_speed_control_ua_T car_speed_control_uart_proto_M_;
RT_MODEL_car_speed_control_ua_T *const car_speed_control_uart_proto_M =
  &car_speed_control_uart_proto_M_;

/* Forward declaration for local functions */
static real_T car_speed_control_uart_prot_mod(real_T x);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void car_speed_control_uart_proto2_2_SetEventsForThisBaseStep(boolean_T
  *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[2] = ((boolean_T)rtmStepTask(car_speed_control_uart_proto_M, 2));
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
  if (car_speed_control_uart_proto_M->Timing.TaskCounters.TID[1] == 0) {
    car_speed_control_uart_proto_M->Timing.RateInteraction.TID1_2 =
      (car_speed_control_uart_proto_M->Timing.TaskCounters.TID[2] == 0);
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (car_speed_control_uart_proto_M->Timing.TaskCounters.TID[2])++;
  if ((car_speed_control_uart_proto_M->Timing.TaskCounters.TID[2]) > 99) {/* Sample time: [0.1s, 0.0s] */
    car_speed_control_uart_proto_M->Timing.TaskCounters.TID[2] = 0;
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
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  car_speed_control_uart_proto2_2_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  car_speed_control_uart_proto2_2_step0();
  car_speed_control_uart_proto2_2_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  car_speed_control_uart_proto2_2_step0();
  car_speed_control_uart_proto2_2_derivatives();

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
static real_T car_speed_control_uart_prot_mod(real_T x)
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
void car_speed_control_uart_proto2_2_step0(void) /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(car_speed_control_uart_proto_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&car_speed_control_uart_proto_M->solverInfo,
                          ((car_speed_control_uart_proto_M->Timing.clockTick0+1)*
      car_speed_control_uart_proto_M->Timing.stepSize0));

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(car_speed_control_uart_proto_M)) {
    car_speed_control_uart_proto_M->Timing.t[0] = rtsiGetT
      (&car_speed_control_uart_proto_M->solverInfo);
  }

  {
    real_T rtb_Derivative2;
    real_T y;
    real_T *lastU;
    int16_T i;
    uint16_T dutyL;
    uint8_T tmp_0;
    boolean_T tmp;
    tmp = rtmIsMajorTimeStep(car_speed_control_uart_proto_M);
    if (tmp) {
      /* MATLABSystem: '<Root>/Serial Receive1' */
      MW_Serial_read(1, 1U, &car_speed_control_uart_proto2_B.SerialReceive1_o1,
                     &car_speed_control_uart_proto2_B.SerialReceive1_o2, NULL,
                     0.0, NULL, 0.0);

      /* MATLAB Function: '<Root>/Arduino Input1' */
      car_speed_control_uart_proto2_B.ready = false;
      for (i = 0; i < 10; i++) {
        car_speed_control_uart_proto2_B.data_out[i] = 0U;
      }

      if (car_speed_control_uart_proto2_B.SerialReceive1_o2 == 1) {
        if (!car_speed_control_uart_proto_DW.collecting) {
          if (car_speed_control_uart_proto2_B.SerialReceive1_o1 == 170) {
            car_speed_control_uart_proto_DW.buffer[0] =
              car_speed_control_uart_proto2_B.SerialReceive1_o1;
            car_speed_control_uart_proto_DW.count = 1.0;
            car_speed_control_uart_proto_DW.collecting = true;
          }
        } else {
          car_speed_control_uart_proto_DW.count++;
          car_speed_control_uart_proto_DW.buffer[(int16_T)
            car_speed_control_uart_proto_DW.count - 1] =
            car_speed_control_uart_proto2_B.SerialReceive1_o1;
          if (car_speed_control_uart_proto_DW.count == 10.0) {
            for (i = 0; i < 10; i++) {
              car_speed_control_uart_proto2_B.data_out[i] =
                car_speed_control_uart_proto_DW.buffer[i];
            }

            car_speed_control_uart_proto2_B.ready = true;
            car_speed_control_uart_proto_DW.count = 0.0;
            car_speed_control_uart_proto_DW.collecting = false;
          }
        }
      }

      /* End of MATLAB Function: '<Root>/Arduino Input1' */
      /* MATLAB Function: '<Root>/Arduino Input2' */
      if (car_speed_control_uart_proto2_B.ready) {
        car_speed_control_uart_proto_DW.p_valid = true;
        car_speed_control_uart_proto_DW.p_speed_L = ((real_T)
          car_speed_control_uart_proto2_B.data_out[2] / 100.0 + (real_T)
          car_speed_control_uart_proto2_B.data_out[1]) * 10.0;
        car_speed_control_uart_proto_DW.p_speed_R = ((real_T)
          car_speed_control_uart_proto2_B.data_out[4] / 100.0 + (real_T)
          car_speed_control_uart_proto2_B.data_out[3]) * 10.0;
        dutyL = car_speed_control_uart_proto2_B.data_out[6] * 10U;
        if (dutyL > 255U) {
          dutyL = 255U;
        }

        car_speed_control_uart_proto_DW.p_v_target = (uint8_T)dutyL;
        car_speed_control_uart_proto_DW.p_slope =
          car_speed_control_uart_proto2_B.data_out[5];
        tmp_0 = car_speed_control_uart_proto2_B.data_out[7];
        if (car_speed_control_uart_proto2_B.data_out[7] > 127) {
          tmp_0 = 127U;
        }

        car_speed_control_uart_proto_DW.p_steer = (int8_T)tmp_0;
        car_speed_control_uart_proto_DW.p_crc =
          car_speed_control_uart_proto2_B.data_out[8];
      }

      car_speed_control_uart_proto2_B.valid =
        car_speed_control_uart_proto_DW.p_valid;
      car_speed_control_uart_proto2_B.speed_L =
        car_speed_control_uart_proto_DW.p_speed_L;
      car_speed_control_uart_proto2_B.speed_R =
        car_speed_control_uart_proto_DW.p_speed_R;
      car_speed_control_uart_proto2_B.v_target =
        car_speed_control_uart_proto_DW.p_v_target;
      car_speed_control_uart_proto2_B.slope =
        car_speed_control_uart_proto_DW.p_slope;
      car_speed_control_uart_proto2_B.steer =
        car_speed_control_uart_proto_DW.p_steer;
      car_speed_control_uart_proto2_B.crc =
        car_speed_control_uart_proto_DW.p_crc;

      /* End of MATLAB Function: '<Root>/Arduino Input2' */

      /* Gain: '<Root>/V_gain' */
      i = car_speed_control_uart_proto2_P.V_gain_Gain *
        car_speed_control_uart_proto2_B.steer;

      /* Sum: '<Root>/Add' incorporates:
       *  Gain: '<Root>/V_gain'
       *  Sum: '<Root>/Sum2'
       */
      car_speed_control_uart_proto2_B.error = (real_T)
        ((car_speed_control_uart_proto2_B.v_target << 3) + i) * 0.125 -
        car_speed_control_uart_proto2_B.speed_L;

      /* Gain: '<Root>/Kp' */
      car_speed_control_uart_proto2_B.Kp =
        car_speed_control_uart_proto2_P.Kp_Gain *
        car_speed_control_uart_proto2_B.error;
    }

    /* Derivative: '<Root>/Derivative1' incorporates:
     *  Derivative: '<Root>/Derivative2'
     */
    y = car_speed_control_uart_proto_M->Timing.t[0];
    if ((car_speed_control_uart_proto_DW.TimeStampA >= y) &&
        (car_speed_control_uart_proto_DW.TimeStampB >= y)) {
      rtb_Derivative2 = 0.0;
    } else {
      rtb_Derivative2 = car_speed_control_uart_proto_DW.TimeStampA;
      lastU = &car_speed_control_uart_proto_DW.LastUAtTimeA;
      if (car_speed_control_uart_proto_DW.TimeStampA <
          car_speed_control_uart_proto_DW.TimeStampB) {
        if (car_speed_control_uart_proto_DW.TimeStampB < y) {
          rtb_Derivative2 = car_speed_control_uart_proto_DW.TimeStampB;
          lastU = &car_speed_control_uart_proto_DW.LastUAtTimeB;
        }
      } else if (car_speed_control_uart_proto_DW.TimeStampA >= y) {
        rtb_Derivative2 = car_speed_control_uart_proto_DW.TimeStampB;
        lastU = &car_speed_control_uart_proto_DW.LastUAtTimeB;
      }

      rtb_Derivative2 = (car_speed_control_uart_proto2_B.error - *lastU) / (y -
        rtb_Derivative2);
    }

    /* End of Derivative: '<Root>/Derivative1' */

    /* Sum: '<Root>/Sum' incorporates:
     *  Gain: '<Root>/Kd'
     *  Gain: '<Root>/Ki'
     *  Integrator: '<Root>/Integrator'
     */
    car_speed_control_uart_proto2_B.Sum =
      (car_speed_control_uart_proto2_P.Ki_Gain *
       car_speed_control_uart_proto2_X.Integrator_CSTATE +
       car_speed_control_uart_proto2_B.Kp) +
      car_speed_control_uart_proto2_P.Kd_Gain * rtb_Derivative2;
    if (tmp) {
      /* Sum: '<Root>/Add1' incorporates:
       *  Gain: '<Root>/V_gain'
       *  Sum: '<Root>/Sum3'
       */
      car_speed_control_uart_proto2_B.error_j = (real_T)
        ((car_speed_control_uart_proto2_B.v_target << 3) - i) * 0.125 -
        car_speed_control_uart_proto2_B.speed_R;

      /* Gain: '<Root>/Kp1' */
      car_speed_control_uart_proto2_B.Kp1 =
        car_speed_control_uart_proto2_P.Kp1_Gain *
        car_speed_control_uart_proto2_B.error_j;
    }

    /* Derivative: '<Root>/Derivative2' */
    if ((car_speed_control_uart_proto_DW.TimeStampA_l >= y) &&
        (car_speed_control_uart_proto_DW.TimeStampB_i >= y)) {
      rtb_Derivative2 = 0.0;
    } else {
      rtb_Derivative2 = car_speed_control_uart_proto_DW.TimeStampA_l;
      lastU = &car_speed_control_uart_proto_DW.LastUAtTimeA_k;
      if (car_speed_control_uart_proto_DW.TimeStampA_l <
          car_speed_control_uart_proto_DW.TimeStampB_i) {
        if (car_speed_control_uart_proto_DW.TimeStampB_i < y) {
          rtb_Derivative2 = car_speed_control_uart_proto_DW.TimeStampB_i;
          lastU = &car_speed_control_uart_proto_DW.LastUAtTimeB_o;
        }
      } else if (car_speed_control_uart_proto_DW.TimeStampA_l >= y) {
        rtb_Derivative2 = car_speed_control_uart_proto_DW.TimeStampB_i;
        lastU = &car_speed_control_uart_proto_DW.LastUAtTimeB_o;
      }

      rtb_Derivative2 = (car_speed_control_uart_proto2_B.error_j - *lastU) / (y
        - rtb_Derivative2);
    }

    /* Sum: '<Root>/Sum1' incorporates:
     *  Gain: '<Root>/Kd1'
     *  Gain: '<Root>/Ki1'
     *  Integrator: '<Root>/Integrator1'
     */
    car_speed_control_uart_proto2_B.Sum1 =
      (car_speed_control_uart_proto2_P.Ki1_Gain *
       car_speed_control_uart_proto2_X.Integrator1_CSTATE +
       car_speed_control_uart_proto2_B.Kp1) +
      car_speed_control_uart_proto2_P.Kd1_Gain * rtb_Derivative2;

    /* MATLAB Function: '<Root>/MATLAB Function' */
    if (car_speed_control_uart_proto2_B.Sum >= 0.0) {
      y = car_speed_control_uart_proto2_B.Sum;
    } else {
      y = 0.0;
    }

    if (!(y <= 400.0)) {
      y = 400.0;
    }

    dutyL = (uint16_T)rt_roundd_snf(y / 400.0 * 2000.0 + 2000.0);
    car_speed_control_uart_proto2_B.byteL2 = dutyL & 255U;
    car_speed_control_uart_proto2_B.byteL1 = dutyL >> 8;
    if (car_speed_control_uart_proto2_B.Sum1 >= 0.0) {
      y = car_speed_control_uart_proto2_B.Sum1;
    } else {
      y = 0.0;
    }

    if (!(y <= 400.0)) {
      y = 400.0;
    }

    dutyL = (uint16_T)rt_roundd_snf(y / 400.0 * 2000.0 + 2000.0);
    car_speed_control_uart_proto2_B.byteR2 = dutyL & 255U;
    car_speed_control_uart_proto2_B.byteR1 = dutyL >> 8;

    /* End of MATLAB Function: '<Root>/MATLAB Function' */
    if (tmp) {
      /* RateTransition generated from: '<Root>/Subsystem' */
      if (car_speed_control_uart_proto_M->Timing.RateInteraction.TID1_2) {
        car_speed_control_uart_proto_DW.byteL1_Buffer =
          car_speed_control_uart_proto2_B.byteL1;

        /* RateTransition generated from: '<Root>/Subsystem' */
        car_speed_control_uart_proto_DW.byteL2_Buffer =
          car_speed_control_uart_proto2_B.byteL2;

        /* RateTransition generated from: '<Root>/Subsystem' */
        car_speed_control_uart_proto_DW.byteR1_Buffer =
          car_speed_control_uart_proto2_B.byteR1;

        /* RateTransition generated from: '<Root>/Subsystem' */
        car_speed_control_uart_proto_DW.byteR2_Buffer =
          car_speed_control_uart_proto2_B.byteR2;
      }

      /* End of RateTransition generated from: '<Root>/Subsystem' */
    }
  }

  if (rtmIsMajorTimeStep(car_speed_control_uart_proto_M)) {
    real_T *lastU;

    /* Update for Derivative: '<Root>/Derivative1' */
    if (car_speed_control_uart_proto_DW.TimeStampA == (rtInf)) {
      car_speed_control_uart_proto_DW.TimeStampA =
        car_speed_control_uart_proto_M->Timing.t[0];
      lastU = &car_speed_control_uart_proto_DW.LastUAtTimeA;
    } else if (car_speed_control_uart_proto_DW.TimeStampB == (rtInf)) {
      car_speed_control_uart_proto_DW.TimeStampB =
        car_speed_control_uart_proto_M->Timing.t[0];
      lastU = &car_speed_control_uart_proto_DW.LastUAtTimeB;
    } else if (car_speed_control_uart_proto_DW.TimeStampA <
               car_speed_control_uart_proto_DW.TimeStampB) {
      car_speed_control_uart_proto_DW.TimeStampA =
        car_speed_control_uart_proto_M->Timing.t[0];
      lastU = &car_speed_control_uart_proto_DW.LastUAtTimeA;
    } else {
      car_speed_control_uart_proto_DW.TimeStampB =
        car_speed_control_uart_proto_M->Timing.t[0];
      lastU = &car_speed_control_uart_proto_DW.LastUAtTimeB;
    }

    *lastU = car_speed_control_uart_proto2_B.error;

    /* End of Update for Derivative: '<Root>/Derivative1' */

    /* Update for Derivative: '<Root>/Derivative2' */
    if (car_speed_control_uart_proto_DW.TimeStampA_l == (rtInf)) {
      car_speed_control_uart_proto_DW.TimeStampA_l =
        car_speed_control_uart_proto_M->Timing.t[0];
      lastU = &car_speed_control_uart_proto_DW.LastUAtTimeA_k;
    } else if (car_speed_control_uart_proto_DW.TimeStampB_i == (rtInf)) {
      car_speed_control_uart_proto_DW.TimeStampB_i =
        car_speed_control_uart_proto_M->Timing.t[0];
      lastU = &car_speed_control_uart_proto_DW.LastUAtTimeB_o;
    } else if (car_speed_control_uart_proto_DW.TimeStampA_l <
               car_speed_control_uart_proto_DW.TimeStampB_i) {
      car_speed_control_uart_proto_DW.TimeStampA_l =
        car_speed_control_uart_proto_M->Timing.t[0];
      lastU = &car_speed_control_uart_proto_DW.LastUAtTimeA_k;
    } else {
      car_speed_control_uart_proto_DW.TimeStampB_i =
        car_speed_control_uart_proto_M->Timing.t[0];
      lastU = &car_speed_control_uart_proto_DW.LastUAtTimeB_o;
    }

    *lastU = car_speed_control_uart_proto2_B.error_j;

    /* End of Update for Derivative: '<Root>/Derivative2' */
    {
      extmodeErrorCode_T returnCode = EXTMODE_SUCCESS;
      extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
        ((car_speed_control_uart_proto_M->Timing.clockTick1 * 1) + 0);

      /* Trigger External Mode event */
      returnCode = extmodeEvent(1, extmodeTime);
      if (returnCode != EXTMODE_SUCCESS) {
        /* Code to handle External Mode event errors
           may be added here */
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(car_speed_control_uart_proto_M)) {
    rt_ertODEUpdateContinuousStates(&car_speed_control_uart_proto_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++car_speed_control_uart_proto_M->Timing.clockTick0;
    car_speed_control_uart_proto_M->Timing.t[0] = rtsiGetSolverStopTime
      (&car_speed_control_uart_proto_M->solverInfo);

    /* Update absolute time */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    car_speed_control_uart_proto_M->Timing.clockTick1++;
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void car_speed_control_uart_proto2_2_derivatives(void)
{
  XDot_car_speed_control_uart_p_T *_rtXdot;
  _rtXdot = ((XDot_car_speed_control_uart_p_T *)
             car_speed_control_uart_proto_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = car_speed_control_uart_proto2_B.error;

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = car_speed_control_uart_proto2_B.error_j;
}

/* Model step function for TID2 */
void car_speed_control_uart_proto2_2_step2(void) /* Sample time: [0.1s, 0.0s] */
{
  real_T tmp;
  uint16_T tmp_0;
  uint8_T dataIn[5];
  uint8_T varargin_10;
  uint8_T varargin_9;

  /* Outputs for Atomic SubSystem: '<Root>/Subsystem' */
  /* MATLABSystem: '<S4>/Serial Transmit2' */
  varargin_9 = 85U;
  varargin_10 = 170U;

  /* MATLAB Function: '<S4>/Arduino output1' incorporates:
   *  RateTransition generated from: '<Root>/Subsystem'
   */
  tmp_0 = car_speed_control_uart_proto_DW.byteL1_Buffer;
  if (car_speed_control_uart_proto_DW.byteL1_Buffer > 255U) {
    tmp_0 = 255U;
  }

  /* MATLABSystem: '<S4>/Serial Transmit2' incorporates:
   *  MATLAB Function: '<S4>/Arduino output1'
   */
  dataIn[0] = (uint8_T)tmp_0;

  /* MATLAB Function: '<S4>/Arduino output1' incorporates:
   *  RateTransition generated from: '<Root>/Subsystem'
   */
  tmp_0 = car_speed_control_uart_proto_DW.byteL2_Buffer;
  if (car_speed_control_uart_proto_DW.byteL2_Buffer > 255U) {
    tmp_0 = 255U;
  }

  /* MATLABSystem: '<S4>/Serial Transmit2' incorporates:
   *  MATLAB Function: '<S4>/Arduino output1'
   */
  dataIn[1] = (uint8_T)tmp_0;

  /* MATLAB Function: '<S4>/Arduino output1' incorporates:
   *  RateTransition generated from: '<Root>/Subsystem'
   */
  tmp_0 = car_speed_control_uart_proto_DW.byteR1_Buffer;
  if (car_speed_control_uart_proto_DW.byteR1_Buffer > 255U) {
    tmp_0 = 255U;
  }

  /* MATLABSystem: '<S4>/Serial Transmit2' incorporates:
   *  MATLAB Function: '<S4>/Arduino output1'
   */
  dataIn[2] = (uint8_T)tmp_0;

  /* MATLAB Function: '<S4>/Arduino output1' incorporates:
   *  RateTransition generated from: '<Root>/Subsystem'
   */
  tmp_0 = car_speed_control_uart_proto_DW.byteR2_Buffer;
  if (car_speed_control_uart_proto_DW.byteR2_Buffer > 255U) {
    tmp_0 = 255U;
  }

  /* MATLABSystem: '<S4>/Serial Transmit2' incorporates:
   *  MATLAB Function: '<S4>/Arduino output1'
   */
  dataIn[3] = (uint8_T)tmp_0;

  /* MATLAB Function: '<S4>/Arduino output1' incorporates:
   *  RateTransition generated from: '<Root>/Subsystem'
   * */
  tmp = rt_roundd_snf(car_speed_control_uart_prot_mod(256.0 -
    car_speed_control_uart_prot_mod((real_T)((((int32_T)
    car_speed_control_uart_proto_DW.byteL1_Buffer +
    car_speed_control_uart_proto_DW.byteL2_Buffer) +
    car_speed_control_uart_proto_DW.byteR1_Buffer) +
    car_speed_control_uart_proto_DW.byteR2_Buffer))));
  if (tmp < 65536.0) {
    if (tmp >= 0.0) {
      tmp_0 = (uint16_T)tmp;
    } else {
      tmp_0 = 0U;
    }
  } else {
    tmp_0 = MAX_uint16_T;
  }

  if (tmp_0 > 255U) {
    tmp_0 = 255U;
  }

  /* MATLABSystem: '<S4>/Serial Transmit2' incorporates:
   *  MATLAB Function: '<S4>/Arduino output1'
   */
  dataIn[4] = (uint8_T)tmp_0;
  MW_Serial_write(car_speed_control_uart_proto_DW.obj.port, &dataIn[0], 5.0,
                  car_speed_control_uart_proto_DW.obj.dataSizeInBytes,
                  car_speed_control_uart_proto_DW.obj.sendModeEnum,
                  car_speed_control_uart_proto_DW.obj.dataType,
                  car_speed_control_uart_proto_DW.obj.sendFormatEnum, 2.0,
                  '\x00', &varargin_9, 1.0, &varargin_10, 1.0);

  /* End of Outputs for SubSystem: '<Root>/Subsystem' */

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.1, which is the step size
   * of the task. Size of "clockTick2" ensures timer will not overflow during the
   * application lifespan selected.
   */
  car_speed_control_uart_proto_M->Timing.clockTick2++;
}

/* Model initialize function */
void car_speed_control_uart_proto2_2_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&car_speed_control_uart_proto_M->solverInfo,
                          &car_speed_control_uart_proto_M->Timing.simTimeStep);
    rtsiSetTPtr(&car_speed_control_uart_proto_M->solverInfo, &rtmGetTPtr
                (car_speed_control_uart_proto_M));
    rtsiSetStepSizePtr(&car_speed_control_uart_proto_M->solverInfo,
                       &car_speed_control_uart_proto_M->Timing.stepSize0);
    rtsiSetdXPtr(&car_speed_control_uart_proto_M->solverInfo,
                 &car_speed_control_uart_proto_M->derivs);
    rtsiSetContStatesPtr(&car_speed_control_uart_proto_M->solverInfo, (real_T **)
                         &car_speed_control_uart_proto_M->contStates);
    rtsiSetNumContStatesPtr(&car_speed_control_uart_proto_M->solverInfo,
      &car_speed_control_uart_proto_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&car_speed_control_uart_proto_M->solverInfo,
      &car_speed_control_uart_proto_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr
      (&car_speed_control_uart_proto_M->solverInfo,
       &car_speed_control_uart_proto_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr
      (&car_speed_control_uart_proto_M->solverInfo,
       &car_speed_control_uart_proto_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&car_speed_control_uart_proto_M->solverInfo,
      (boolean_T**) &car_speed_control_uart_proto_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&car_speed_control_uart_proto_M->solverInfo,
                          (&rtmGetErrorStatus(car_speed_control_uart_proto_M)));
    rtsiSetRTModelPtr(&car_speed_control_uart_proto_M->solverInfo,
                      car_speed_control_uart_proto_M);
  }

  rtsiSetSimTimeStep(&car_speed_control_uart_proto_M->solverInfo,
                     MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange
    (&car_speed_control_uart_proto_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&car_speed_control_uart_proto_M->solverInfo, false);
  car_speed_control_uart_proto_M->intgData.y =
    car_speed_control_uart_proto_M->odeY;
  car_speed_control_uart_proto_M->intgData.f[0] =
    car_speed_control_uart_proto_M->odeF[0];
  car_speed_control_uart_proto_M->intgData.f[1] =
    car_speed_control_uart_proto_M->odeF[1];
  car_speed_control_uart_proto_M->intgData.f[2] =
    car_speed_control_uart_proto_M->odeF[2];
  car_speed_control_uart_proto_M->contStates = ((X_car_speed_control_uart_prot_T
    *) &car_speed_control_uart_proto2_X);
  car_speed_control_uart_proto_M->contStateDisabled =
    ((XDis_car_speed_control_uart_p_T *) &car_speed_control_uart_pro_XDis);
  car_speed_control_uart_proto_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&car_speed_control_uart_proto_M->solverInfo, (void *)
                    &car_speed_control_uart_proto_M->intgData);
  rtsiSetSolverName(&car_speed_control_uart_proto_M->solverInfo,"ode3");
  rtmSetTPtr(car_speed_control_uart_proto_M,
             &car_speed_control_uart_proto_M->Timing.tArray[0]);
  rtmSetTFinal(car_speed_control_uart_proto_M, 500.0);
  car_speed_control_uart_proto_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  car_speed_control_uart_proto_M->Sizes.checksums[0] = (54193140U);
  car_speed_control_uart_proto_M->Sizes.checksums[1] = (77714131U);
  car_speed_control_uart_proto_M->Sizes.checksums[2] = (3952770466U);
  car_speed_control_uart_proto_M->Sizes.checksums[3] = (181471954U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[8];
    car_speed_control_uart_proto_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(car_speed_control_uart_proto_M->extModeInfo,
      &car_speed_control_uart_proto_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(car_speed_control_uart_proto_M->extModeInfo,
                        car_speed_control_uart_proto_M->Sizes.checksums);
    rteiSetTFinalTicks(car_speed_control_uart_proto_M->extModeInfo, 500000);
  }

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  car_speed_control_uart_proto2_X.Integrator_CSTATE =
    car_speed_control_uart_proto2_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  car_speed_control_uart_proto_DW.TimeStampA = (rtInf);
  car_speed_control_uart_proto_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  car_speed_control_uart_proto2_X.Integrator1_CSTATE =
    car_speed_control_uart_proto2_P.Integrator1_IC;

  /* InitializeConditions for Derivative: '<Root>/Derivative2' */
  car_speed_control_uart_proto_DW.TimeStampA_l = (rtInf);
  car_speed_control_uart_proto_DW.TimeStampB_i = (rtInf);

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subsystem' */
  /* Start for MATLABSystem: '<S4>/Serial Transmit2' */
  car_speed_control_uart_proto_DW.obj.matlabCodegenIsDeleted = false;
  car_speed_control_uart_proto_DW.obj.isInitialized = 1L;
  car_speed_control_uart_proto_DW.obj.port = 1.0;
  car_speed_control_uart_proto_DW.obj.dataSizeInBytes = 1.0;
  car_speed_control_uart_proto_DW.obj.dataType = 0.0;
  car_speed_control_uart_proto_DW.obj.sendModeEnum = 0.0;
  car_speed_control_uart_proto_DW.obj.sendFormatEnum = 0.0;
  MW_SCI_Open(1);
  car_speed_control_uart_proto_DW.obj.isSetupComplete = true;

  /* End of SystemInitialize for SubSystem: '<Root>/Subsystem' */

  /* Start for MATLABSystem: '<Root>/Serial Receive1' */
  car_speed_control_uart_proto_DW.obj_e.matlabCodegenIsDeleted = false;
  car_speed_control_uart_proto_DW.obj_e.isInitialized = 1L;
  MW_SCI_Open(1);
  car_speed_control_uart_proto_DW.obj_e.isSetupComplete = true;
}

/* Model terminate function */
void car_speed_control_uart_proto2_2_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Receive1' */
  if (!car_speed_control_uart_proto_DW.obj_e.matlabCodegenIsDeleted) {
    car_speed_control_uart_proto_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Receive1' */
  /* Terminate for Atomic SubSystem: '<Root>/Subsystem' */
  /* Terminate for MATLABSystem: '<S4>/Serial Transmit2' */
  if (!car_speed_control_uart_proto_DW.obj.matlabCodegenIsDeleted) {
    car_speed_control_uart_proto_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S4>/Serial Transmit2' */
  /* End of Terminate for SubSystem: '<Root>/Subsystem' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
