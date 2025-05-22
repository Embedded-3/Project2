################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../driver/mp.c" \
"../driver/user_MotorCtl.c" 

COMPILED_SRCS += \
"driver/mp.src" \
"driver/user_MotorCtl.src" 

C_DEPS += \
"./driver/mp.d" \
"./driver/user_MotorCtl.d" 

OBJS += \
"driver/mp.o" \
"driver/user_MotorCtl.o" 


# Each subdirectory must supply rules for building sources it contributes
"driver/mp.src":"../driver/mp.c" "driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/p2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/mp.o":"driver/mp.src" "driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"driver/user_MotorCtl.src":"../driver/user_MotorCtl.c" "driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/p2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/user_MotorCtl.o":"driver/user_MotorCtl.src" "driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver

clean-driver:
	-$(RM) ./driver/mp.d ./driver/mp.o ./driver/mp.src ./driver/user_MotorCtl.d ./driver/user_MotorCtl.o ./driver/user_MotorCtl.src

.PHONY: clean-driver

