/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: car_speed_control_uart.c
 *
 * Code generated for Simulink model 'car_speed_control_uart'.
 *
 * Model version                  : 1.29
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu May 22 19:48:34 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "car_speed_control_uart.h"
#include "rtwtypes.h"
#include <math.h>
#include "car_speed_control_uart_private.h"
#include <stddef.h>
#include "rt_nonfinite.h"

/* Block states (default storage) */
DW_car_speed_control_uart_T car_speed_control_uart_DW;

/* Real-time model */
static RT_MODEL_car_speed_control_ua_T car_speed_control_uart_M_;
RT_MODEL_car_speed_control_ua_T *const car_speed_control_uart_M =
  &car_speed_control_uart_M_;

/* Forward declaration for local functions */
static real_T car_speed_control_uart_mod(real_T x);
static real_T car_speed_control_uart_mod_e(real_T x);

/* Function for MATLAB Function: '<Root>/Arduino output' */
static real_T car_speed_control_uart_mod(real_T x)
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
static real_T car_speed_control_uart_mod_e(real_T x)
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

/* Model step function */
void car_speed_control_uart_step(void)
{
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  uint8_T rtb_frame[7];
  uint8_T tmp_2;
  uint8_T tmp_3;

  /* MATLAB Function: '<Root>/Arduino output' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   */
  rtb_frame[0] = 170U;
  tmp_1 = floor(car_speed_control_uart_P.Constant2_Value);
  if (tmp_1 < 256.0) {
    if (tmp_1 >= 0.0) {
      rtb_frame[1] = (uint8_T)tmp_1;
    } else {
      rtb_frame[1] = 0U;
    }
  } else {
    rtb_frame[1] = MAX_uint8_T;
  }

  tmp_0 = floor(car_speed_control_uart_mod
                (car_speed_control_uart_P.Constant2_Value * 100.0));
  if (tmp_0 < 256.0) {
    if (tmp_0 >= 0.0) {
      rtb_frame[2] = (uint8_T)tmp_0;
    } else {
      rtb_frame[2] = 0U;
    }
  } else {
    rtb_frame[2] = MAX_uint8_T;
  }

  tmp_0 = floor(car_speed_control_uart_P.Constant1_Value);
  if (tmp_0 < 256.0) {
    if (tmp_0 >= 0.0) {
      rtb_frame[3] = (uint8_T)tmp_0;
    } else {
      rtb_frame[3] = 0U;
    }
  } else {
    rtb_frame[3] = MAX_uint8_T;
  }

  tmp = floor(car_speed_control_uart_mod
              (car_speed_control_uart_P.Constant1_Value * 100.0));
  if (tmp < 256.0) {
    if (tmp >= 0.0) {
      rtb_frame[4] = (uint8_T)tmp;
    } else {
      rtb_frame[4] = 0U;
    }
  } else {
    rtb_frame[4] = MAX_uint8_T;
  }

  if (tmp_1 < 256.0) {
    if (tmp_1 >= 0.0) {
      tmp_2 = (uint8_T)tmp_1;
    } else {
      tmp_2 = 0U;
    }
  } else {
    tmp_2 = MAX_uint8_T;
  }

  if (tmp_0 < 256.0) {
    if (tmp_0 >= 0.0) {
      tmp_3 = (uint8_T)tmp_0;
    } else {
      tmp_3 = 0U;
    }
  } else {
    tmp_3 = MAX_uint8_T;
  }

  tmp_1 = rt_roundd_snf(car_speed_control_uart_mod_e(256.0 -
    car_speed_control_uart_mod_e((real_T)((((tmp_2 + rtb_frame[2]) + tmp_3) +
    rtb_frame[4]) + 170))));
  if (tmp_1 < 256.0) {
    if (tmp_1 >= 0.0) {
      rtb_frame[5] = (uint8_T)tmp_1;
    } else {
      rtb_frame[5] = 0U;
    }
  } else {
    rtb_frame[5] = MAX_uint8_T;
  }

  rtb_frame[6] = 85U;

  /* End of MATLAB Function: '<Root>/Arduino output' */

  /* MATLABSystem: '<Root>/Serial Transmit1' */
  MW_Serial_write(car_speed_control_uart_DW.obj.port, &rtb_frame[0], 7.0,
                  car_speed_control_uart_DW.obj.dataSizeInBytes,
                  car_speed_control_uart_DW.obj.sendModeEnum,
                  car_speed_control_uart_DW.obj.dataType,
                  car_speed_control_uart_DW.obj.sendFormatEnum, 2.0, '\x00',
                  NULL, 0.0, NULL, 0.0);
}

/* Model initialize function */
void car_speed_control_uart_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* Start for MATLABSystem: '<Root>/Serial Transmit1' */
  car_speed_control_uart_DW.obj.matlabCodegenIsDeleted = false;
  car_speed_control_uart_DW.obj.isInitialized = 1L;
  car_speed_control_uart_DW.obj.port = 1.0;
  car_speed_control_uart_DW.obj.dataSizeInBytes = 1.0;
  car_speed_control_uart_DW.obj.dataType = 0.0;
  car_speed_control_uart_DW.obj.sendModeEnum = 0.0;
  car_speed_control_uart_DW.obj.sendFormatEnum = 0.0;
  MW_SCI_Open(1);
  car_speed_control_uart_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void car_speed_control_uart_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Transmit1' */
  if (!car_speed_control_uart_DW.obj.matlabCodegenIsDeleted) {
    car_speed_control_uart_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Transmit1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
