################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Src/Kalman.c \
../App/Src/debug.c \
../App/Src/i2cEeprom.c \
../App/Src/io.c \
../App/Src/measurement.c \
../App/Src/ntc_measurement.c \
../App/Src/pcp.c \
../App/Src/process.c \
../App/Src/protection.c \
../App/Src/soft_start.c 

C_DEPS += \
./App/Src/Kalman.d \
./App/Src/debug.d \
./App/Src/i2cEeprom.d \
./App/Src/io.d \
./App/Src/measurement.d \
./App/Src/ntc_measurement.d \
./App/Src/pcp.d \
./App/Src/process.d \
./App/Src/protection.d \
./App/Src/soft_start.d 

OBJS += \
./App/Src/Kalman.o \
./App/Src/debug.o \
./App/Src/i2cEeprom.o \
./App/Src/io.o \
./App/Src/measurement.o \
./App/Src/ntc_measurement.o \
./App/Src/pcp.o \
./App/Src/process.o \
./App/Src/protection.o \
./App/Src/soft_start.o 


# Each subdirectory must supply rules for building sources it contributes
App/Src/%.o App/Src/%.su App/Src/%.cyclo: ../App/Src/%.c App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/CMSIS/DSP/Include -I../App/Inc -I../App/Src -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Src

clean-App-2f-Src:
	-$(RM) ./App/Src/Kalman.cyclo ./App/Src/Kalman.d ./App/Src/Kalman.o ./App/Src/Kalman.su ./App/Src/debug.cyclo ./App/Src/debug.d ./App/Src/debug.o ./App/Src/debug.su ./App/Src/i2cEeprom.cyclo ./App/Src/i2cEeprom.d ./App/Src/i2cEeprom.o ./App/Src/i2cEeprom.su ./App/Src/io.cyclo ./App/Src/io.d ./App/Src/io.o ./App/Src/io.su ./App/Src/measurement.cyclo ./App/Src/measurement.d ./App/Src/measurement.o ./App/Src/measurement.su ./App/Src/ntc_measurement.cyclo ./App/Src/ntc_measurement.d ./App/Src/ntc_measurement.o ./App/Src/ntc_measurement.su ./App/Src/pcp.cyclo ./App/Src/pcp.d ./App/Src/pcp.o ./App/Src/pcp.su ./App/Src/process.cyclo ./App/Src/process.d ./App/Src/process.o ./App/Src/process.su ./App/Src/protection.cyclo ./App/Src/protection.d ./App/Src/protection.o ./App/Src/protection.su ./App/Src/soft_start.cyclo ./App/Src/soft_start.d ./App/Src/soft_start.o ./App/Src/soft_start.su

.PHONY: clean-App-2f-Src

