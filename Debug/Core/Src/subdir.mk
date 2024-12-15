################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/clock_cfg.c \
../Core/Src/drawing.c \
../Core/Src/ds1307_for_stm32_hal.c \
../Core/Src/flash_mem.c \
../Core/Src/gpio.c \
../Core/Src/gpio_cfg.c \
../Core/Src/i2c.c \
../Core/Src/ili9341.c \
../Core/Src/ltdc_cfg.c \
../Core/Src/main.c \
../Core/Src/rc522.c \
../Core/Src/sdram_cfg.c \
../Core/Src/spi.c \
../Core/Src/spi_cfg.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/clock_cfg.o \
./Core/Src/drawing.o \
./Core/Src/ds1307_for_stm32_hal.o \
./Core/Src/flash_mem.o \
./Core/Src/gpio.o \
./Core/Src/gpio_cfg.o \
./Core/Src/i2c.o \
./Core/Src/ili9341.o \
./Core/Src/ltdc_cfg.o \
./Core/Src/main.o \
./Core/Src/rc522.o \
./Core/Src/sdram_cfg.o \
./Core/Src/spi.o \
./Core/Src/spi_cfg.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/clock_cfg.d \
./Core/Src/drawing.d \
./Core/Src/ds1307_for_stm32_hal.d \
./Core/Src/flash_mem.d \
./Core/Src/gpio.d \
./Core/Src/gpio_cfg.d \
./Core/Src/i2c.d \
./Core/Src/ili9341.d \
./Core/Src/ltdc_cfg.d \
./Core/Src/main.d \
./Core/Src/rc522.d \
./Core/Src/sdram_cfg.d \
./Core/Src/spi.d \
./Core/Src/spi_cfg.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/clock_cfg.cyclo ./Core/Src/clock_cfg.d ./Core/Src/clock_cfg.o ./Core/Src/clock_cfg.su ./Core/Src/drawing.cyclo ./Core/Src/drawing.d ./Core/Src/drawing.o ./Core/Src/drawing.su ./Core/Src/ds1307_for_stm32_hal.cyclo ./Core/Src/ds1307_for_stm32_hal.d ./Core/Src/ds1307_for_stm32_hal.o ./Core/Src/ds1307_for_stm32_hal.su ./Core/Src/flash_mem.cyclo ./Core/Src/flash_mem.d ./Core/Src/flash_mem.o ./Core/Src/flash_mem.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/gpio_cfg.cyclo ./Core/Src/gpio_cfg.d ./Core/Src/gpio_cfg.o ./Core/Src/gpio_cfg.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/ili9341.cyclo ./Core/Src/ili9341.d ./Core/Src/ili9341.o ./Core/Src/ili9341.su ./Core/Src/ltdc_cfg.cyclo ./Core/Src/ltdc_cfg.d ./Core/Src/ltdc_cfg.o ./Core/Src/ltdc_cfg.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rc522.cyclo ./Core/Src/rc522.d ./Core/Src/rc522.o ./Core/Src/rc522.su ./Core/Src/sdram_cfg.cyclo ./Core/Src/sdram_cfg.d ./Core/Src/sdram_cfg.o ./Core/Src/sdram_cfg.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/spi_cfg.cyclo ./Core/Src/spi_cfg.d ./Core/Src/spi_cfg.o ./Core/Src/spi_cfg.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

