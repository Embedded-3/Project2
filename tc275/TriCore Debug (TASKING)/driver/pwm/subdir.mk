################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../driver/pwm/pwm.c" 

COMPILED_SRCS += \
"driver/pwm/pwm.src" 

C_DEPS += \
"./driver/pwm/pwm.d" 

OBJS += \
"driver/pwm/pwm.o" 


# Each subdirectory must supply rules for building sources it contributes
"driver/pwm/pwm.src":"../driver/pwm/pwm.c" "driver/pwm/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/p2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/pwm/pwm.o":"driver/pwm/pwm.src" "driver/pwm/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver-2f-pwm

clean-driver-2f-pwm:
	-$(RM) ./driver/pwm/pwm.d ./driver/pwm/pwm.o ./driver/pwm/pwm.src

.PHONY: clean-driver-2f-pwm

