################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../driver/message/message.c" 

COMPILED_SRCS += \
"driver/message/message.src" 

C_DEPS += \
"./driver/message/message.d" 

OBJS += \
"driver/message/message.o" 


# Each subdirectory must supply rules for building sources it contributes
"driver/message/message.src":"../driver/message/message.c" "driver/message/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.10-workspace/TC275_UART_now/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/message/message.o":"driver/message/message.src" "driver/message/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver-2f-message

clean-driver-2f-message:
	-$(RM) ./driver/message/message.d ./driver/message/message.o ./driver/message/message.src

.PHONY: clean-driver-2f-message

