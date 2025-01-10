################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CAN1_Receving.c \
../Core/Src/CAN1_Transmitting.c \
../Core/Src/CAN2_Receving.c \
../Core/Src/CAN2_Transmitting.c \
../Core/Src/Can_Data_Xchange.c \
../Core/Src/ModbusRTU_Slave.c \
../Core/Src/adc.c \
../Core/Src/dac.c \
../Core/Src/dma.c \
../Core/Src/error_display.c \
../Core/Src/gpio.c \
../Core/Src/hrtim.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/spi.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

C_DEPS += \
./Core/Src/CAN1_Receving.d \
./Core/Src/CAN1_Transmitting.d \
./Core/Src/CAN2_Receving.d \
./Core/Src/CAN2_Transmitting.d \
./Core/Src/Can_Data_Xchange.d \
./Core/Src/ModbusRTU_Slave.d \
./Core/Src/adc.d \
./Core/Src/dac.d \
./Core/Src/dma.d \
./Core/Src/error_display.d \
./Core/Src/gpio.d \
./Core/Src/hrtim.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/spi.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 

OBJS += \
./Core/Src/CAN1_Receving.o \
./Core/Src/CAN1_Transmitting.o \
./Core/Src/CAN2_Receving.o \
./Core/Src/CAN2_Transmitting.o \
./Core/Src/Can_Data_Xchange.o \
./Core/Src/ModbusRTU_Slave.o \
./Core/Src/adc.o \
./Core/Src/dac.o \
./Core/Src/dma.o \
./Core/Src/error_display.o \
./Core/Src/gpio.o \
./Core/Src/hrtim.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/spi.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/CMSIS/DSP/Include -I../App/Inc -I../App/Src -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/CAN1_Receving.cyclo ./Core/Src/CAN1_Receving.d ./Core/Src/CAN1_Receving.o ./Core/Src/CAN1_Receving.su ./Core/Src/CAN1_Transmitting.cyclo ./Core/Src/CAN1_Transmitting.d ./Core/Src/CAN1_Transmitting.o ./Core/Src/CAN1_Transmitting.su ./Core/Src/CAN2_Receving.cyclo ./Core/Src/CAN2_Receving.d ./Core/Src/CAN2_Receving.o ./Core/Src/CAN2_Receving.su ./Core/Src/CAN2_Transmitting.cyclo ./Core/Src/CAN2_Transmitting.d ./Core/Src/CAN2_Transmitting.o ./Core/Src/CAN2_Transmitting.su ./Core/Src/Can_Data_Xchange.cyclo ./Core/Src/Can_Data_Xchange.d ./Core/Src/Can_Data_Xchange.o ./Core/Src/Can_Data_Xchange.su ./Core/Src/ModbusRTU_Slave.cyclo ./Core/Src/ModbusRTU_Slave.d ./Core/Src/ModbusRTU_Slave.o ./Core/Src/ModbusRTU_Slave.su ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/dac.cyclo ./Core/Src/dac.d ./Core/Src/dac.o ./Core/Src/dac.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/error_display.cyclo ./Core/Src/error_display.d ./Core/Src/error_display.o ./Core/Src/error_display.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/hrtim.cyclo ./Core/Src/hrtim.d ./Core/Src/hrtim.o ./Core/Src/hrtim.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32g4xx_hal_msp.cyclo ./Core/Src/stm32g4xx_hal_msp.d ./Core/Src/stm32g4xx_hal_msp.o ./Core/Src/stm32g4xx_hal_msp.su ./Core/Src/stm32g4xx_it.cyclo ./Core/Src/stm32g4xx_it.d ./Core/Src/stm32g4xx_it.o ./Core/Src/stm32g4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g4xx.cyclo ./Core/Src/system_stm32g4xx.d ./Core/Src/system_stm32g4xx.o ./Core/Src/system_stm32g4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

