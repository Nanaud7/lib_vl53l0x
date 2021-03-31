################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L0X_API/core/src/vl53l0x_api.c \
../Drivers/VL53L0X_API/core/src/vl53l0x_api_calibration.c \
../Drivers/VL53L0X_API/core/src/vl53l0x_api_core.c \
../Drivers/VL53L0X_API/core/src/vl53l0x_api_ranging.c \
../Drivers/VL53L0X_API/core/src/vl53l0x_api_strings.c 

OBJS += \
./Drivers/VL53L0X_API/core/src/vl53l0x_api.o \
./Drivers/VL53L0X_API/core/src/vl53l0x_api_calibration.o \
./Drivers/VL53L0X_API/core/src/vl53l0x_api_core.o \
./Drivers/VL53L0X_API/core/src/vl53l0x_api_ranging.o \
./Drivers/VL53L0X_API/core/src/vl53l0x_api_strings.o 

C_DEPS += \
./Drivers/VL53L0X_API/core/src/vl53l0x_api.d \
./Drivers/VL53L0X_API/core/src/vl53l0x_api_calibration.d \
./Drivers/VL53L0X_API/core/src/vl53l0x_api_core.d \
./Drivers/VL53L0X_API/core/src/vl53l0x_api_ranging.d \
./Drivers/VL53L0X_API/core/src/vl53l0x_api_strings.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L0X_API/core/src/vl53l0x_api.o: ../Drivers/VL53L0X_API/core/src/vl53l0x_api.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/core/inc" -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/platform/inc" -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/VL53L0X_API/core/src/vl53l0x_api.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/VL53L0X_API/core/src/vl53l0x_api_calibration.o: ../Drivers/VL53L0X_API/core/src/vl53l0x_api_calibration.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/core/inc" -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/platform/inc" -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/VL53L0X_API/core/src/vl53l0x_api_calibration.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/VL53L0X_API/core/src/vl53l0x_api_core.o: ../Drivers/VL53L0X_API/core/src/vl53l0x_api_core.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/core/inc" -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/platform/inc" -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/VL53L0X_API/core/src/vl53l0x_api_core.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/VL53L0X_API/core/src/vl53l0x_api_ranging.o: ../Drivers/VL53L0X_API/core/src/vl53l0x_api_ranging.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/core/inc" -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/platform/inc" -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/VL53L0X_API/core/src/vl53l0x_api_ranging.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/VL53L0X_API/core/src/vl53l0x_api_strings.o: ../Drivers/VL53L0X_API/core/src/vl53l0x_api_strings.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/core/inc" -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Drivers/VL53L0X_API/platform/inc" -I"E:/ARNAUD/Arnaud 3.0/Git folder/lib_vl53l0x/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/VL53L0X_API/core/src/vl53l0x_api_strings.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

