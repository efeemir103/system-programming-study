################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32L0xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Traffic\ Lights\ with\ Timer.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Traffic\ Lights\ with\ Timer.list \


# All Target
all: Traffic\ Lights\ with\ Timer.elf secondary-outputs

# Tool invocations
Traffic\ Lights\ with\ Timer.elf: $(OBJS) $(USER_OBJS) /home/null/STM32CubeIDE/workspace_1.0.2/Traffic\ Lights\ with\ Timer/STM32L053R8TX_FLASH.ld
	arm-none-eabi-gcc -o "Traffic Lights with Timer.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"/home/null/STM32CubeIDE/workspace_1.0.2/Traffic Lights with Timer/STM32L053R8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Traffic Lights with Timer.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Traffic\ Lights\ with\ Timer.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Traffic Lights with Timer.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
