################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../driver/stm/stm.c" 

COMPILED_SRCS += \
"driver/stm/stm.src" 

C_DEPS += \
"./driver/stm/stm.d" 

OBJS += \
"driver/stm/stm.o" 


# Each subdirectory must supply rules for building sources it contributes
"driver/stm/stm.src":"../driver/stm/stm.c" "driver/stm/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/p2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/stm/stm.o":"driver/stm/stm.src" "driver/stm/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver-2f-stm

clean-driver-2f-stm:
	-$(RM) ./driver/stm/stm.d ./driver/stm/stm.o ./driver/stm/stm.src

.PHONY: clean-driver-2f-stm

