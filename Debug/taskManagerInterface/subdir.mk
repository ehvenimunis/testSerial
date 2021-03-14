################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../taskManagerInterface/taskManagerInterface.c 

OBJS += \
./taskManagerInterface/taskManagerInterface.o 

C_DEPS += \
./taskManagerInterface/taskManagerInterface.d 


# Each subdirectory must supply rules for building sources it contributes
taskManagerInterface/taskManagerInterface.o: ../taskManagerInterface/taskManagerInterface.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/salih/Documents/CubeWorkSpace/testSerial/motorDriverInterface" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"/home/salih/Documents/CubeWorkSpace/testSerial/analogValuesController" -I"/home/salih/Documents/CubeWorkSpace/testSerial/buttonController" -I"/home/salih/Documents/CubeWorkSpace/testSerial/ComputerInterface" -I"/home/salih/Documents/CubeWorkSpace/testSerial/lcdDriver" -I"/home/salih/Documents/CubeWorkSpace/testSerial/taskManagerInterface" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"taskManagerInterface/taskManagerInterface.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

