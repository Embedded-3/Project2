// safety.c
#include "safety.h"
#include "driver\smu_ir\SMU_IR_Alarm.h"

volatile int flag0 = 0;
volatile int flag1 = 0;

void checkSafetyFlag(){
    static int t = 0;

    if(t++ % 19 == 0){
        if(flag0 == 1){
            flag0 = 2;
            trigger_SMU_alarm();
        }

        if(flag1 == 1){
            flag1 = 2;
            trigger_SMU_alarm1();
        }
    }

}