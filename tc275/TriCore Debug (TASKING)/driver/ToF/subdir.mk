################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../driver/ToF/ToF.c" 

COMPILED_SRCS += \
"driver/ToF/ToF.src" 

C_DEPS += \
"./driver/ToF/ToF.d" 

OBJS += \
"driver/ToF/ToF.o" 


# Each subdirectory must supply rules for building sources it contributes
"driver/ToF/ToF.src":"../driver/ToF/ToF.c" "driver/ToF/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/p2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/ToF/ToF.o":"driver/ToF/ToF.src" "driver/ToF/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver-2f-ToF

clean-driver-2f-ToF:
	-$(RM) ./driver/ToF/ToF.d ./driver/ToF/ToF.o ./driver/ToF/ToF.src

.PHONY: clean-driver-2f-ToF

