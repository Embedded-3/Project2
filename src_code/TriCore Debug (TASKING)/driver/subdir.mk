################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../driver/adc.c" \
"../driver/asclin.c" 

COMPILED_SRCS += \
"driver/adc.src" \
"driver/asclin.src" 

C_DEPS += \
"./driver/adc.d" \
"./driver/asclin.d" 

OBJS += \
"driver/adc.o" \
"driver/asclin.o" 


# Each subdirectory must supply rules for building sources it contributes
"driver/adc.src":"../driver/adc.c" "driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/p2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/adc.o":"driver/adc.src" "driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"driver/asclin.src":"../driver/asclin.c" "driver/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/p2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/asclin.o":"driver/asclin.src" "driver/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver

clean-driver:
	-$(RM) ./driver/adc.d ./driver/adc.o ./driver/adc.src ./driver/asclin.d ./driver/asclin.o ./driver/asclin.src

.PHONY: clean-driver

