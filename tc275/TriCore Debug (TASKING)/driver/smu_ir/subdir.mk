################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../driver/smu_ir/SMU_IR_Alarm.c" 

COMPILED_SRCS += \
"driver/smu_ir/SMU_IR_Alarm.src" 

C_DEPS += \
"./driver/smu_ir/SMU_IR_Alarm.d" 

OBJS += \
"driver/smu_ir/SMU_IR_Alarm.o" 


# Each subdirectory must supply rules for building sources it contributes
"driver/smu_ir/SMU_IR_Alarm.src":"../driver/smu_ir/SMU_IR_Alarm.c" "driver/smu_ir/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/p2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/smu_ir/SMU_IR_Alarm.o":"driver/smu_ir/SMU_IR_Alarm.src" "driver/smu_ir/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver-2f-smu_ir

clean-driver-2f-smu_ir:
	-$(RM) ./driver/smu_ir/SMU_IR_Alarm.d ./driver/smu_ir/SMU_IR_Alarm.o ./driver/smu_ir/SMU_IR_Alarm.src

.PHONY: clean-driver-2f-smu_ir

