################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/ToF.c \
../driver/asclin.c \
../driver/etc.c \
../driver/imu.c \
../driver/my_stdio.c \
../driver/stm.c 

COMPILED_SRCS += \
driver/ToF.src \
driver/asclin.src \
driver/etc.src \
driver/imu.src \
driver/my_stdio.src \
driver/stm.src 

C_DEPS += \
driver/ToF.d \
driver/asclin.d \
driver/etc.d \
driver/imu.d \
driver/my_stdio.d \
driver/stm.d 

OBJS += \
driver/ToF.o \
driver/asclin.o \
driver/etc.o \
driver/imu.o \
driver/my_stdio.o \
driver/stm.o 


# Each subdirectory must supply rules for building sources it contributes
driver/ToF.src: ../driver/ToF.c driver/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/TEST/auto_pilot/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
driver/ToF.o: driver/ToF.src driver/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
driver/asclin.src: ../driver/asclin.c driver/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/TEST/auto_pilot/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
driver/asclin.o: driver/asclin.src driver/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
driver/etc.src: ../driver/etc.c driver/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/TEST/auto_pilot/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
driver/etc.o: driver/etc.src driver/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
driver/imu.src: ../driver/imu.c driver/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/TEST/auto_pilot/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
driver/imu.o: driver/imu.src driver/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
driver/my_stdio.src: ../driver/my_stdio.c driver/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/TEST/auto_pilot/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
driver/my_stdio.o: driver/my_stdio.src driver/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
driver/stm.src: ../driver/stm.c driver/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/TEST/auto_pilot/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
driver/stm.o: driver/stm.src driver/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-driver

clean-driver:
	-$(RM) driver/ToF.d driver/ToF.o driver/ToF.src driver/asclin.d driver/asclin.o driver/asclin.src driver/etc.d driver/etc.o driver/etc.src driver/imu.d driver/imu.o driver/imu.src driver/my_stdio.d driver/my_stdio.o driver/my_stdio.src driver/stm.d driver/stm.o driver/stm.src

.PHONY: clean-driver

