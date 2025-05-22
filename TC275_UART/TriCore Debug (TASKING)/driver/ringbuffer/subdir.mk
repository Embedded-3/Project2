################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../driver/ringbuffer/ring_buffer.c" 

COMPILED_SRCS += \
"driver/ringbuffer/ring_buffer.src" 

C_DEPS += \
"./driver/ringbuffer/ring_buffer.d" 

OBJS += \
"driver/ringbuffer/ring_buffer.o" 


# Each subdirectory must supply rules for building sources it contributes
"driver/ringbuffer/ring_buffer.src":"../driver/ringbuffer/ring_buffer.c" "driver/ringbuffer/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.10-workspace/TC275_UART/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"driver/ringbuffer/ring_buffer.o":"driver/ringbuffer/ring_buffer.src" "driver/ringbuffer/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver-2f-ringbuffer

clean-driver-2f-ringbuffer:
	-$(RM) ./driver/ringbuffer/ring_buffer.d ./driver/ringbuffer/ring_buffer.o ./driver/ringbuffer/ring_buffer.src

.PHONY: clean-driver-2f-ringbuffer

