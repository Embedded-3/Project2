
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#define SIMPLIFIED_RTWTYPES_COMPATIBILITY
#include "rtwtypes.h"
#undef SIMPLIFIED_RTWTYPES_COMPATIBILITY
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <Arduino.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
#define encoder0pinA 2
#define encoder0pinB 4

volatile long pulseCount = 0;
byte encoder0PinALast = LOW;
// bool Direction = true;

void countPulse() {
    int Lstate = digitalRead(encoder0pinA);
    if ((encoder0PinALast == LOW) && (Lstate == HIGH)) {
        int val = digitalRead(encoder0pinB);
        if (val == LOW && Direction)
            Direction = false;
        else if (val == HIGH && !Direction)
            Direction = true;
    }
    encoder0PinALast = Lstate;
    if (!Direction)
        pulseCount++;
    else
        pulseCount--;
}
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
extern void readEncoder_Start_wrapper(real_T *xD);

void readEncoder_Start_wrapper(real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
pinMode(encoder0pinA, INPUT);
    pinMode(encoder0pinB, INPUT);
    encoder0PinALast = digitalRead(encoder0pinA);
    Direction = true;
    attachInterrupt(digitalPinToInterrupt(encoder0pinA), countPulse, CHANGE);
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
extern void readEncoder_Outputs_wrapper(real_T *y0,
			const real_T *xD);

void readEncoder_Outputs_wrapper(real_T *y0,
			const real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
noInterrupts();
    y0[0] = (real_T)pulseCount;
    pulseCount = 0;
    interrupts();
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Updates function
 *
 */
extern void readEncoder_Update_wrapper(real_T *y0,
			real_T *xD);

void readEncoder_Update_wrapper(real_T *y0,
			real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
 
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Terminate function
 *
 */
extern void readEncoder_Terminate_wrapper(real_T *xD);

void readEncoder_Terminate_wrapper(real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_BEGIN --- EDIT HERE TO _END */
detachInterrupt(digitalPinToInterrupt(encoder0pinA));
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}

