/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: UART_test_types.h
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

#ifndef UART_test_types_h_
#define UART_test_types_h_
#include "rtwtypes.h"
#ifndef struct_tag_Pbgev5zVqPH5mwobtiKYmC
#define struct_tag_Pbgev5zVqPH5mwobtiKYmC

struct tag_Pbgev5zVqPH5mwobtiKYmC
{
  int16_T __dummy;
};

#endif                                 /* struct_tag_Pbgev5zVqPH5mwobtiKYmC */

#ifndef typedef_c_arduinodriver_ArduinoSerial_T
#define typedef_c_arduinodriver_ArduinoSerial_T

typedef struct tag_Pbgev5zVqPH5mwobtiKYmC c_arduinodriver_ArduinoSerial_T;

#endif                             /* typedef_c_arduinodriver_ArduinoSerial_T */

#ifndef struct_tag_9nWnLOWX6DqWTzZVGtpmOD
#define struct_tag_9nWnLOWX6DqWTzZVGtpmOD

struct tag_9nWnLOWX6DqWTzZVGtpmOD
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  c_arduinodriver_ArduinoSerial_T SerialDriverObj;
};

#endif                                 /* struct_tag_9nWnLOWX6DqWTzZVGtpmOD */

#ifndef typedef_codertarget_arduinobase_inter_T
#define typedef_codertarget_arduinobase_inter_T

typedef struct tag_9nWnLOWX6DqWTzZVGtpmOD codertarget_arduinobase_inter_T;

#endif                             /* typedef_codertarget_arduinobase_inter_T */

#ifndef struct_tag_lEfVKSLRxhO8DhHRAG0Rz
#define struct_tag_lEfVKSLRxhO8DhHRAG0Rz

struct tag_lEfVKSLRxhO8DhHRAG0Rz
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T port;
  real_T dataSizeInBytes;
  real_T dataType;
  real_T sendModeEnum;
  real_T sendFormatEnum;
  c_arduinodriver_ArduinoSerial_T SerialDriverObj;
};

#endif                                 /* struct_tag_lEfVKSLRxhO8DhHRAG0Rz */

#ifndef typedef_codertarget_arduinobase_int_h_T
#define typedef_codertarget_arduinobase_int_h_T

typedef struct tag_lEfVKSLRxhO8DhHRAG0Rz codertarget_arduinobase_int_h_T;

#endif                             /* typedef_codertarget_arduinobase_int_h_T */

/* Parameters (default storage) */
typedef struct P_UART_test_T_ P_UART_test_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_UART_test_T RT_MODEL_UART_test_T;

#endif                                 /* UART_test_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
