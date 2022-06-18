################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CAN_program.c \
../Core/Src/Delay_program.c \
../Core/Src/ESP8266_program.c \
../Core/Src/EXTI_program.c \
../Core/Src/Flash_Program.c \
../Core/Src/GPIO_program.c \
../Core/Src/NVIC_config.c \
../Core/Src/NVIC_program.c \
../Core/Src/RCC_Program.c \
../Core/Src/STK_program.c \
../Core/Src/Timer_program.c \
../Core/Src/USART_program.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/CAN_program.o \
./Core/Src/Delay_program.o \
./Core/Src/ESP8266_program.o \
./Core/Src/EXTI_program.o \
./Core/Src/Flash_Program.o \
./Core/Src/GPIO_program.o \
./Core/Src/NVIC_config.o \
./Core/Src/NVIC_program.o \
./Core/Src/RCC_Program.o \
./Core/Src/STK_program.o \
./Core/Src/Timer_program.o \
./Core/Src/USART_program.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/CAN_program.d \
./Core/Src/Delay_program.d \
./Core/Src/ESP8266_program.d \
./Core/Src/EXTI_program.d \
./Core/Src/Flash_Program.d \
./Core/Src/GPIO_program.d \
./Core/Src/NVIC_config.d \
./Core/Src/NVIC_program.d \
./Core/Src/RCC_Program.d \
./Core/Src/STK_program.d \
./Core/Src/Timer_program.d \
./Core/Src/USART_program.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/CAN_program.d ./Core/Src/CAN_program.o ./Core/Src/CAN_program.su ./Core/Src/Delay_program.d ./Core/Src/Delay_program.o ./Core/Src/Delay_program.su ./Core/Src/ESP8266_program.d ./Core/Src/ESP8266_program.o ./Core/Src/ESP8266_program.su ./Core/Src/EXTI_program.d ./Core/Src/EXTI_program.o ./Core/Src/EXTI_program.su ./Core/Src/Flash_Program.d ./Core/Src/Flash_Program.o ./Core/Src/Flash_Program.su ./Core/Src/GPIO_program.d ./Core/Src/GPIO_program.o ./Core/Src/GPIO_program.su ./Core/Src/NVIC_config.d ./Core/Src/NVIC_config.o ./Core/Src/NVIC_config.su ./Core/Src/NVIC_program.d ./Core/Src/NVIC_program.o ./Core/Src/NVIC_program.su ./Core/Src/RCC_Program.d ./Core/Src/RCC_Program.o ./Core/Src/RCC_Program.su ./Core/Src/STK_program.d ./Core/Src/STK_program.o ./Core/Src/STK_program.su ./Core/Src/Timer_program.d ./Core/Src/Timer_program.o ./Core/Src/Timer_program.su ./Core/Src/USART_program.d ./Core/Src/USART_program.o ./Core/Src/USART_program.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

