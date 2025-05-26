################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../driver/imu/imu.c" 

COMPILED_SRCS += \
"driver/imu/imu.src" 

C_DEPS += \
"./driver/imu/imu.d" 

OBJS += \
"driver/imu/imu.o" 


# Each subdirectory must supply rules for building sources it contributes
"driver/imu/imu.src":"../driver/imu/imu.c" "driver/imu/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/p2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/imu/imu.o":"driver/imu/imu.src" "driver/imu/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver-2f-imu

clean-driver-2f-imu:
	-$(RM) ./driver/imu/imu.d ./driver/imu/imu.o ./driver/imu/imu.src

.PHONY: clean-driver-2f-imu

