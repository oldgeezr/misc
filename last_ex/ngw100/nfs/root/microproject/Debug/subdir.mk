################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hello_world.c \
../main.c \
../miniproject.c \
../pid_controller.c 

OBJS += \
./hello_world.o \
./main.o \
./miniproject.o \
./pid_controller.o 

C_DEPS += \
./hello_world.d \
./main.d \
./miniproject.d \
./pid_controller.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	avr32-linux-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


