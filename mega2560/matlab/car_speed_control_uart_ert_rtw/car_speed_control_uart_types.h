/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: car_speed_control_uart_types.h
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

#ifndef car_speed_control_uart_types_h_
#define car_speed_control_uart_types_h_
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

#ifndef typedef_codertarget_arduinobase_inter_T
#define typedef_codertarget_arduinobase_inter_T

typedef struct tag_lEfVKSLRxhO8DhHRAG0Rz codertarget_arduinobase_inter_T;

#endif                             /* typedef_codertarget_arduinobase_inter_T */

/* Parameters (default storage) */
typedef struct P_car_speed_control_uart_T_ P_car_speed_control_uart_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_car_speed_control_uar_T RT_MODEL_car_speed_control_ua_T;

#endif                                 /* car_speed_control_uart_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
