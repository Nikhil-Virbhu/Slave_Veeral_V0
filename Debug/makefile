################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32G4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include App/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Slave_Veeral_V0
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Slave_Veeral_V0.elf \

MAP_FILES += \
Slave_Veeral_V0.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Slave_Veeral_V0.list \

OBJCOPY_HEX += \
Slave_Veeral_V0.hex \

OBJCOPY_BIN += \
Slave_Veeral_V0.bin \

OBJCOPY_VERILOG += \
Slave_Veeral_V0.verilog \

OBJCOPY_SREC += \
Slave_Veeral_V0.srec \

OBJCOPY_SYMBOLSREC += \
Slave_Veeral_V0.symbolsrec \


# All Target
all: main-build

# Main-build Target
main-build: Slave_Veeral_V0.elf secondary-outputs

# Tool invocations
Slave_Veeral_V0.elf Slave_Veeral_V0.map: $(OBJS) $(USER_OBJS) C:\Users\HirenTejani\OneDrive\ -\ Virginia\ Transformer\ India\ Private\ Limited\Desktop\Hiren\ Tejani\Firmware\Veeral\ Slave\STM32G474VETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Slave_Veeral_V0.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\HirenTejani\OneDrive - Virginia Transformer India Private Limited\Desktop\Hiren Tejani\Firmware\Veeral Slave\STM32G474VETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Slave_Veeral_V0.map" -Wl,--gc-sections -static -L"C:\Users\HirenTejani\OneDrive - Virginia Transformer India Private Limited\Desktop\Hiren Tejani\Firmware\Veeral Slave\Drivers\CMSIS\Lib\GCC" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Slave_Veeral_V0.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Slave_Veeral_V0.list"
	@echo 'Finished building: $@'
	@echo ' '

Slave_Veeral_V0.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Slave_Veeral_V0.hex"
	@echo 'Finished building: $@'
	@echo ' '

Slave_Veeral_V0.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Slave_Veeral_V0.bin"
	@echo 'Finished building: $@'
	@echo ' '

Slave_Veeral_V0.verilog: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O verilog $(EXECUTABLES) "Slave_Veeral_V0.verilog"
	@echo 'Finished building: $@'
	@echo ' '

Slave_Veeral_V0.srec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O srec $(EXECUTABLES) "Slave_Veeral_V0.srec"
	@echo 'Finished building: $@'
	@echo ' '

Slave_Veeral_V0.symbolsrec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O symbolsrec $(EXECUTABLES) "Slave_Veeral_V0.symbolsrec"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Slave_Veeral_V0.bin Slave_Veeral_V0.elf Slave_Veeral_V0.hex Slave_Veeral_V0.list Slave_Veeral_V0.map Slave_Veeral_V0.srec Slave_Veeral_V0.symbolsrec Slave_Veeral_V0.verilog default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN) $(OBJCOPY_VERILOG) $(OBJCOPY_SREC) $(OBJCOPY_SYMBOLSREC)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
