// readEncoder.c - Simulink-compatible S-Function for reading encoder pulses
#define S_FUNCTION_NAME  readEncoder
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"
#include <Arduino.h>

#define encoder0pinA 2
#define encoder0pinB 4

static volatile long pulseCount = 0;
static byte encoder0PinALast = LOW;
static bool Direction = true;

// 인터럽트 핸들러 함수
void countPulse() {
    int Lstate = digitalRead(encoder0pinA);
    if ((encoder0PinALast == LOW) && (Lstate == HIGH)) {
        int val = digitalRead(encoder0pinB);
        if (val == LOW && Direction) {
            Direction = false;
        } else if (val == HIGH && !Direction) {
            Direction = true;
        }
    }
    encoder0PinALast = Lstate;

    if (!Direction)
        pulseCount++;
    else
        pulseCount--;
}

static void mdlInitializeSizes(SimStruct *S) {
    ssSetNumSFcnParams(S, 0);
    ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 1);
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    ssSetNumSampleTimes(S, 1);
}

static void mdlInitializeSampleTimes(SimStruct *S) {
    ssSetSampleTime(S, 0, 0.1);  // 100ms 주기
    ssSetOffsetTime(S, 0, 0.0);
}

static void mdlStart(SimStruct *S) {
    pinMode(encoder0pinA, INPUT);
    pinMode(encoder0pinB, INPUT);
    encoder0PinALast = digitalRead(encoder0pinA);
    Direction = true;
    attachInterrupt(digitalPinToInterrupt(encoder0pinA), countPulse, CHANGE);
}

static void mdlOutputs(SimStruct *S, int_T tid) {
    real_T *y = ssGetOutputPortRealSignal(S, 0);
    noInterrupts();
    y[0] = (real_T)pulseCount;
    pulseCount = 0;
    interrupts();
}

static void mdlTerminate(SimStruct *S) {
    detachInterrupt(digitalPinToInterrupt(encoder0pinA));
}

#ifdef MATLAB_MEX_FILE
#include "simulink.c"
#else
#include "cg_sfun.h"
#endif
