################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_i2c.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usart.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.c 

OBJS += \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_i2c.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usart.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.o 

C_DEPS += \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_i2c.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usart.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.o: ../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DLSI_VALUE=37000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DMSI_VALUE=1048000' -DSTM32L031xx '-DUSE_FULL_ASSERT=1U' -DUSE_FULL_LL_DRIVER '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.o: ../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DLSI_VALUE=37000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DMSI_VALUE=1048000' -DSTM32L031xx '-DUSE_FULL_ASSERT=1U' -DUSE_FULL_LL_DRIVER '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.o: ../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DLSI_VALUE=37000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DMSI_VALUE=1048000' -DSTM32L031xx '-DUSE_FULL_ASSERT=1U' -DUSE_FULL_LL_DRIVER '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_i2c.o: ../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DLSI_VALUE=37000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DMSI_VALUE=1048000' -DSTM32L031xx '-DUSE_FULL_ASSERT=1U' -DUSE_FULL_LL_DRIVER '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_i2c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.o: ../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DLSI_VALUE=37000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DMSI_VALUE=1048000' -DSTM32L031xx '-DUSE_FULL_ASSERT=1U' -DUSE_FULL_LL_DRIVER '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.o: ../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DLSI_VALUE=37000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DMSI_VALUE=1048000' -DSTM32L031xx '-DUSE_FULL_ASSERT=1U' -DUSE_FULL_LL_DRIVER '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usart.o: ../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DLSI_VALUE=37000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DMSI_VALUE=1048000' -DSTM32L031xx '-DUSE_FULL_ASSERT=1U' -DUSE_FULL_LL_DRIVER '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_usart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.o: ../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DLSI_VALUE=37000' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DMSI_VALUE=1048000' -DSTM32L031xx '-DUSE_FULL_ASSERT=1U' -DUSE_FULL_LL_DRIVER '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

