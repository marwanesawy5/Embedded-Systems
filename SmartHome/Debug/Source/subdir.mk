################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/adc.c \
../Source/flame.c \
../Source/interrupt.c \
../Source/lcd.c \
../Source/motor.c \
../Source/outputs.c \
../Source/pwm.c 

OBJS += \
./Source/adc.o \
./Source/flame.o \
./Source/interrupt.o \
./Source/lcd.o \
./Source/motor.o \
./Source/outputs.o \
./Source/pwm.o 

C_DEPS += \
./Source/adc.d \
./Source/flame.d \
./Source/interrupt.d \
./Source/lcd.d \
./Source/motor.d \
./Source/outputs.d \
./Source/pwm.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.c Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


