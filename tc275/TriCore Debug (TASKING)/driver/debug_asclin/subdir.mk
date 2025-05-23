################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../driver/debug_asclin/asclin.c" 

COMPILED_SRCS += \
"driver/debug_asclin/asclin.src" 

C_DEPS += \
"./driver/debug_asclin/asclin.d" 

OBJS += \
"driver/debug_asclin/asclin.o" 


# Each subdirectory must supply rules for building sources it contributes
"driver/debug_asclin/asclin.src":"../driver/debug_asclin/asclin.c" "driver/debug_asclin/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/p2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/debug_asclin/asclin.o":"driver/debug_asclin/asclin.src" "driver/debug_asclin/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver-2f-debug_asclin

clean-driver-2f-debug_asclin:
	-$(RM) ./driver/debug_asclin/asclin.d ./driver/debug_asclin/asclin.o ./driver/debug_asclin/asclin.src

.PHONY: clean-driver-2f-debug_asclin

