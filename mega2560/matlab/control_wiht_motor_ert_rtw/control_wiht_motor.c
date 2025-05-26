/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: control_wiht_motor.c
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

#include "control_wiht_motor.h"
#include "rtwtypes.h"
#include "control_wiht_motor_private.h"

/* Block signals (default storage) */
B_control_wiht_motor_T control_wiht_motor_B;

/* Continuous states */
X_control_wiht_motor_T control_wiht_motor_X;

/* Disabled State Vector */
XDis_control_wiht_motor_T control_wiht_motor_XDis;

/* Block states (default storage) */
DW_control_wiht_motor_T control_wiht_motor_DW;

/* Real-time model */
static RT_MODEL_control_wiht_motor_T control_wiht_motor_M_;
RT_MODEL_control_wiht_motor_T *const control_wiht_motor_M =
  &control_wiht_motor_M_;
static void rate_scheduler(void);

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (control_wiht_motor_M->Timing.TaskCounters.TID[2])++;
  if ((control_wiht_motor_M->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.1s, 0.0s] */
    control_wiht_motor_M->Timing.TaskCounters.TID[2] = 0;
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
  control_wiht_motor_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  control_wiht_motor_step();
  control_wiht_motor_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  control_wiht_motor_step();
  control_wiht_motor_derivatives();

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

/* Model step function */
void control_wiht_motor_step(void)
{
  real_T y;
  boolean_T rtb_Compare;
  boolean_T rtb_Compare_o;
  boolean_T rtb_FixPtRelationalOperator;
  boolean_T tmp;
  if (rtmIsMajorTimeStep(control_wiht_motor_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&control_wiht_motor_M->solverInfo,
                          ((control_wiht_motor_M->Timing.clockTick0+1)*
      control_wiht_motor_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(control_wiht_motor_M)) {
    control_wiht_motor_M->Timing.t[0] = rtsiGetT
      (&control_wiht_motor_M->solverInfo);
  }

  tmp = (rtmIsMajorTimeStep(control_wiht_motor_M) &&
         control_wiht_motor_M->Timing.TaskCounters.TID[1] == 0);

  /* TransferFcn: '<Root>/Transfer Fcn' */
  control_wiht_motor_B.v_t = 0.0;
  control_wiht_motor_B.v_t += control_wiht_motor_P.TransferFcn_C *
    control_wiht_motor_X.TransferFcn_CSTATE;
  if (tmp) {
    /* Constant: '<Root>/v_target(cm//s)' */
    control_wiht_motor_B.v_targetcms = control_wiht_motor_P.v_targetcms_Value;
  }

  /* Sum: '<Root>/Add' */
  control_wiht_motor_B.error = control_wiht_motor_B.v_targetcms -
    control_wiht_motor_B.v_t;
  if (tmp) {
  }

  if (rtmIsMajorTimeStep(control_wiht_motor_M) &&
      control_wiht_motor_M->Timing.TaskCounters.TID[2] == 0) {
    /* Outputs for Atomic SubSystem: '<Root>/Subsystem' */
    /* MATLABSystem: '<S1>/Digital Input1' */
    rtb_Compare_o = readDigitalPin(4);

    /* RelationalOperator: '<S5>/Compare' incorporates:
     *  Constant: '<S5>/Constant'
     *  MATLABSystem: '<S1>/Digital Input1'
     * */
    rtb_Compare = ((int16_T)rtb_Compare_o < (int16_T)
                   control_wiht_motor_P.Constant_Value_o);

    /* RelationalOperator: '<S2>/FixPt Relational Operator' incorporates:
     *  UnitDelay: '<S2>/Delay Input1'
     *
     * Block description for '<S2>/Delay Input1':
     *
     *  Store in Global RAM
     */
    rtb_FixPtRelationalOperator = ((int16_T)rtb_Compare > (int16_T)
      control_wiht_motor_DW.DelayInput1_DSTATE);

    /* RelationalOperator: '<S6>/Compare' incorporates:
     *  Constant: '<S6>/Constant'
     *  MATLABSystem: '<S1>/Digital Input1'
     * */
    rtb_Compare_o = ((int16_T)rtb_Compare_o > (int16_T)
                     control_wiht_motor_P.Constant_Value_m);

    /* UnitDelay: '<S3>/Delay Input1' incorporates:
     *  UnitDelay: '<S2>/Delay Input1'
     *
     * Block description for '<S3>/Delay Input1':
     *
     *  Store in Global RAM
     *
     * Block description for '<S2>/Delay Input1':
     *
     *  Store in Global RAM
     */
    control_wiht_motor_DW.DelayInput1_DSTATE =
      control_wiht_motor_DW.DelayInput1_DSTATE_l;

    /* Logic: '<S1>/OR' incorporates:
     *  RelationalOperator: '<S3>/FixPt Relational Operator'
     *  UnitDelay: '<S2>/Delay Input1'
     *
     * Block description for '<S2>/Delay Input1':
     *
     *  Store in Global RAM
     */
    control_wiht_motor_B.OR = (rtb_FixPtRelationalOperator || ((int16_T)
      rtb_Compare_o > (int16_T)control_wiht_motor_DW.DelayInput1_DSTATE));

    /* MATLABSystem: '<S1>/Digital Input' */
    control_wiht_motor_B.DigitalInput = readDigitalPin(2);

    /* MATLAB Function: '<S1>/MATLAB Function1' */
    if (control_wiht_motor_B.OR != control_wiht_motor_DW.prevA) {
      control_wiht_motor_DW.pulseCount++;
    }

    control_wiht_motor_DW.prevA = control_wiht_motor_B.OR;
    control_wiht_motor_B.pulse = control_wiht_motor_DW.pulseCount;

    /* End of MATLAB Function: '<S1>/MATLAB Function1' */
    /* Update for UnitDelay: '<S2>/Delay Input1'
     *
     * Block description for '<S2>/Delay Input1':
     *
     *  Store in Global RAM
     */
    control_wiht_motor_DW.DelayInput1_DSTATE = rtb_Compare;

    /* Update for UnitDelay: '<S3>/Delay Input1'
     *
     * Block description for '<S3>/Delay Input1':
     *
     *  Store in Global RAM
     */
    control_wiht_motor_DW.DelayInput1_DSTATE_l = rtb_Compare_o;

    /* End of Outputs for SubSystem: '<Root>/Subsystem' */

    /* Sum: '<Root>/Subtract' incorporates:
     *  UnitDelay: '<Root>/Unit Delay'
     */
    control_wiht_motor_B.Subtract = control_wiht_motor_B.pulse -
      control_wiht_motor_DW.UnitDelay_DSTATE;

    /* Gain: '<Root>/Gain1' */
    control_wiht_motor_B.Gain1 = control_wiht_motor_P.Gain1_Gain *
      control_wiht_motor_B.Subtract;
  }

  if (tmp) {
    /* MATLABSystem: '<Root>/PWM' */
    control_wiht_motor_DW.obj.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(3UL);

    /* Start for MATLABSystem: '<Root>/PWM' incorporates:
     *  Constant: '<Root>/Constant'
     */
    if (control_wiht_motor_P.Constant_Value <= 255.0) {
      y = control_wiht_motor_P.Constant_Value;
    } else {
      y = 255.0;
    }

    if (!(y >= 0.0)) {
      y = 0.0;
    }

    /* MATLABSystem: '<Root>/PWM' */
    MW_PWM_SetDutyCycle(control_wiht_motor_DW.obj.PWMDriverObj.MW_PWM_HANDLE, y);
  }

  if (rtmIsMajorTimeStep(control_wiht_motor_M)) {
    if (rtmIsMajorTimeStep(control_wiht_motor_M) &&
        control_wiht_motor_M->Timing.TaskCounters.TID[2] == 0) {
      /* Update for UnitDelay: '<Root>/Unit Delay' */
      control_wiht_motor_DW.UnitDelay_DSTATE = control_wiht_motor_B.pulse;
    }

    if (rtmIsMajorTimeStep(control_wiht_motor_M) &&
        control_wiht_motor_M->Timing.TaskCounters.TID[1] == 0) {/* Sample time: [0.01s, 0.0s] */
      extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
      extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
        ((control_wiht_motor_M->Timing.clockTick1 * 1) + 0);

      /* Trigger External Mode event */
      errorCode = extmodeEvent(1, extmodeTime);
      if (errorCode != EXTMODE_SUCCESS) {
        /* Code to handle External Mode event errors
           may be added here */
      }
    }

    if (rtmIsMajorTimeStep(control_wiht_motor_M) &&
        control_wiht_motor_M->Timing.TaskCounters.TID[2] == 0) {/* Sample time: [0.1s, 0.0s] */
      extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
      extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
        ((control_wiht_motor_M->Timing.clockTick2 * 10) + 0);

      /* Trigger External Mode event */
      errorCode = extmodeEvent(2, extmodeTime);
      if (errorCode != EXTMODE_SUCCESS) {
        /* Code to handle External Mode event errors
           may be added here */
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(control_wiht_motor_M)) {
    rt_ertODEUpdateContinuousStates(&control_wiht_motor_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++control_wiht_motor_M->Timing.clockTick0;
    control_wiht_motor_M->Timing.t[0] = rtsiGetSolverStopTime
      (&control_wiht_motor_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      control_wiht_motor_M->Timing.clockTick1++;
    }

    if (rtmIsMajorTimeStep(control_wiht_motor_M) &&
        control_wiht_motor_M->Timing.TaskCounters.TID[2] == 0) {
      /* Update absolute timer for sample time: [0.1s, 0.0s] */
      /* The "clockTick2" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.1, which is the step size
       * of the task. Size of "clockTick2" ensures timer will not overflow during the
       * application lifespan selected.
       */
      control_wiht_motor_M->Timing.clockTick2++;
    }

    rate_scheduler();
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void control_wiht_motor_derivatives(void)
{
  XDot_control_wiht_motor_T *_rtXdot;
  _rtXdot = ((XDot_control_wiht_motor_T *) control_wiht_motor_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = control_wiht_motor_P.TransferFcn_A *
    control_wiht_motor_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += control_wiht_motor_B.Gain1;

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = control_wiht_motor_B.error;
}

/* Model initialize function */
void control_wiht_motor_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&control_wiht_motor_M->solverInfo,
                          &control_wiht_motor_M->Timing.simTimeStep);
    rtsiSetTPtr(&control_wiht_motor_M->solverInfo, &rtmGetTPtr
                (control_wiht_motor_M));
    rtsiSetStepSizePtr(&control_wiht_motor_M->solverInfo,
                       &control_wiht_motor_M->Timing.stepSize0);
    rtsiSetdXPtr(&control_wiht_motor_M->solverInfo,
                 &control_wiht_motor_M->derivs);
    rtsiSetContStatesPtr(&control_wiht_motor_M->solverInfo, (real_T **)
                         &control_wiht_motor_M->contStates);
    rtsiSetNumContStatesPtr(&control_wiht_motor_M->solverInfo,
      &control_wiht_motor_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&control_wiht_motor_M->solverInfo,
      &control_wiht_motor_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&control_wiht_motor_M->solverInfo,
      &control_wiht_motor_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&control_wiht_motor_M->solverInfo,
      &control_wiht_motor_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&control_wiht_motor_M->solverInfo, (boolean_T**)
      &control_wiht_motor_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&control_wiht_motor_M->solverInfo, (&rtmGetErrorStatus
      (control_wiht_motor_M)));
    rtsiSetRTModelPtr(&control_wiht_motor_M->solverInfo, control_wiht_motor_M);
  }

  rtsiSetSimTimeStep(&control_wiht_motor_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&control_wiht_motor_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&control_wiht_motor_M->solverInfo, false);
  control_wiht_motor_M->intgData.y = control_wiht_motor_M->odeY;
  control_wiht_motor_M->intgData.f[0] = control_wiht_motor_M->odeF[0];
  control_wiht_motor_M->intgData.f[1] = control_wiht_motor_M->odeF[1];
  control_wiht_motor_M->intgData.f[2] = control_wiht_motor_M->odeF[2];
  control_wiht_motor_M->contStates = ((X_control_wiht_motor_T *)
    &control_wiht_motor_X);
  control_wiht_motor_M->contStateDisabled = ((XDis_control_wiht_motor_T *)
    &control_wiht_motor_XDis);
  control_wiht_motor_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&control_wiht_motor_M->solverInfo, (void *)
                    &control_wiht_motor_M->intgData);
  rtsiSetSolverName(&control_wiht_motor_M->solverInfo,"ode3");
  rtmSetTPtr(control_wiht_motor_M, &control_wiht_motor_M->Timing.tArray[0]);
  rtmSetTFinal(control_wiht_motor_M, 180.0);
  control_wiht_motor_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  control_wiht_motor_M->Sizes.checksums[0] = (781790795U);
  control_wiht_motor_M->Sizes.checksums[1] = (780624210U);
  control_wiht_motor_M->Sizes.checksums[2] = (530281461U);
  control_wiht_motor_M->Sizes.checksums[3] = (2185875586U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[6];
    control_wiht_motor_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(control_wiht_motor_M->extModeInfo,
      &control_wiht_motor_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(control_wiht_motor_M->extModeInfo,
                        control_wiht_motor_M->Sizes.checksums);
    rteiSetTFinalTicks(control_wiht_motor_M->extModeInfo, 18000);
  }

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  control_wiht_motor_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
  control_wiht_motor_DW.UnitDelay_DSTATE =
    control_wiht_motor_P.UnitDelay_InitialCondition;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  control_wiht_motor_X.Integrator_CSTATE = control_wiht_motor_P.Integrator_IC;

  /* InitializeConditions for UnitDelay: '<S2>/Delay Input1'
   *
   * Block description for '<S2>/Delay Input1':
   *
   *  Store in Global RAM
   */
  control_wiht_motor_DW.DelayInput1_DSTATE =
    control_wiht_motor_P.DetectFallNegative_vinit;

  /* InitializeConditions for UnitDelay: '<S3>/Delay Input1'
   *
   * Block description for '<S3>/Delay Input1':
   *
   *  Store in Global RAM
   */
  control_wiht_motor_DW.DelayInput1_DSTATE_l =
    control_wiht_motor_P.DetectRisePositive_vinit;

  /* Start for MATLABSystem: '<S1>/Digital Input1' */
  control_wiht_motor_DW.obj_m.matlabCodegenIsDeleted = false;
  control_wiht_motor_DW.obj_m.isInitialized = 1L;
  digitalIOSetup(4, 0);
  control_wiht_motor_DW.obj_m.isSetupComplete = true;

  /* Start for MATLABSystem: '<S1>/Digital Input' */
  control_wiht_motor_DW.obj_i.matlabCodegenIsDeleted = false;
  control_wiht_motor_DW.obj_i.isInitialized = 1L;
  digitalIOSetup(2, 0);
  control_wiht_motor_DW.obj_i.isSetupComplete = true;

  /* End of SystemInitialize for SubSystem: '<Root>/Subsystem' */

  /* Start for MATLABSystem: '<Root>/PWM' */
  control_wiht_motor_DW.obj.matlabCodegenIsDeleted = false;
  control_wiht_motor_DW.obj.isInitialized = 1L;
  control_wiht_motor_DW.obj.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(3UL, 0.0,
    0.0);
  control_wiht_motor_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void control_wiht_motor_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subsystem' */
  /* Terminate for MATLABSystem: '<S1>/Digital Input1' */
  if (!control_wiht_motor_DW.obj_m.matlabCodegenIsDeleted) {
    control_wiht_motor_DW.obj_m.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Digital Input1' */

  /* Terminate for MATLABSystem: '<S1>/Digital Input' */
  if (!control_wiht_motor_DW.obj_i.matlabCodegenIsDeleted) {
    control_wiht_motor_DW.obj_i.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Digital Input' */
  /* Terminate for MATLABSystem: '<Root>/PWM' */
  if (!control_wiht_motor_DW.obj.matlabCodegenIsDeleted) {
    control_wiht_motor_DW.obj.matlabCodegenIsDeleted = true;
    if ((control_wiht_motor_DW.obj.isInitialized == 1L) &&
        control_wiht_motor_DW.obj.isSetupComplete) {
      control_wiht_motor_DW.obj.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (3UL);
      MW_PWM_SetDutyCycle(control_wiht_motor_DW.obj.PWMDriverObj.MW_PWM_HANDLE,
                          0.0);
      control_wiht_motor_DW.obj.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (3UL);
      MW_PWM_Close(control_wiht_motor_DW.obj.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/PWM' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
