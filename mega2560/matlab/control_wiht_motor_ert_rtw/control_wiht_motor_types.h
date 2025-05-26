/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: control_wiht_motor_types.h
 *
 * Code generated for Simulink model 'control_wiht_motor'.
 *
 * Model version                  : 1.44
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu May 22 18:17:01 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef control_wiht_motor_types_h_
#define control_wiht_motor_types_h_
#include "MW_SVD.h"
#include "rtwtypes.h"

/* Custom Type definition for MATLABSystem: '<Root>/PWM' */
#include "MW_SVD.h"
#ifndef struct_tag_7VFuPw0vSNrn5pRgG8Mc4C
#define struct_tag_7VFuPw0vSNrn5pRgG8Mc4C

struct tag_7VFuPw0vSNrn5pRgG8Mc4C
{
  MW_Handle_Type MW_PWM_HANDLE;
};

#endif                                 /* struct_tag_7VFuPw0vSNrn5pRgG8Mc4C */

#ifndef typedef_e_matlabshared_ioclient_perip_T
#define typedef_e_matlabshared_ioclient_perip_T

typedef struct tag_7VFuPw0vSNrn5pRgG8Mc4C e_matlabshared_ioclient_perip_T;

#endif                             /* typedef_e_matlabshared_ioclient_perip_T */

#ifndef struct_tag_RWocY1aAVmuibq0rYX5t0G
#define struct_tag_RWocY1aAVmuibq0rYX5t0G

struct tag_RWocY1aAVmuibq0rYX5t0G
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  e_matlabshared_ioclient_perip_T PWMDriverObj;
};

#endif                                 /* struct_tag_RWocY1aAVmuibq0rYX5t0G */

#ifndef typedef_codertarget_arduinobase_inter_T
#define typedef_codertarget_arduinobase_inter_T

typedef struct tag_RWocY1aAVmuibq0rYX5t0G codertarget_arduinobase_inter_T;

#endif                             /* typedef_codertarget_arduinobase_inter_T */

#ifndef struct_tag_bpMNyLZPCJBeBnOB7xlwFB
#define struct_tag_bpMNyLZPCJBeBnOB7xlwFB

struct tag_bpMNyLZPCJBeBnOB7xlwFB
{
  int16_T __dummy;
};

#endif                                 /* struct_tag_bpMNyLZPCJBeBnOB7xlwFB */

#ifndef typedef_c_arduinodriver_ArduinoDigita_T
#define typedef_c_arduinodriver_ArduinoDigita_T

typedef struct tag_bpMNyLZPCJBeBnOB7xlwFB c_arduinodriver_ArduinoDigita_T;

#endif                             /* typedef_c_arduinodriver_ArduinoDigita_T */

#ifndef struct_tag_Re0UPoyV6elc8rAtddQIvE
#define struct_tag_Re0UPoyV6elc8rAtddQIvE

struct tag_Re0UPoyV6elc8rAtddQIvE
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  c_arduinodriver_ArduinoDigita_T DigitalIODriverObj;
};

#endif                                 /* struct_tag_Re0UPoyV6elc8rAtddQIvE */

#ifndef typedef_codertarget_arduinobase_block_T
#define typedef_codertarget_arduinobase_block_T

typedef struct tag_Re0UPoyV6elc8rAtddQIvE codertarget_arduinobase_block_T;

#endif                             /* typedef_codertarget_arduinobase_block_T */

/* Parameters (default storage) */
typedef struct P_control_wiht_motor_T_ P_control_wiht_motor_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_control_wiht_motor_T RT_MODEL_control_wiht_motor_T;

#endif                                 /* control_wiht_motor_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
