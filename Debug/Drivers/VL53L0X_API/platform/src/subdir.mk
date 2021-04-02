################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L0X_API/platform/src/vl53l0x_platform.c 

OBJS += \
./Drivers/VL53L0X_API/platform/src/vl53l0x_platform.o 

C_DEPS += \
./Drivers/VL53L0X_API/platform/src/vl53l0x_platform.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L0X_API/platform/src/vl53l0x_platform.o: ../Drivers/VL53L0X_API/platform/src/vl53l0x_platform.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arnau/Documents/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/core/inc" -I"C:/Users/arnau/Documents/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/platform/inc" -I"C:/Users/arnau/Documents/Git folder/lib_vl53l0x/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/VL53L0X_API/platform/src/vl53l0x_platform.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

