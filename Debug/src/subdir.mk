################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/function.c \
../src/gethttp.c \
../src/gtkwindows.c \
../src/timeline.c \
../src/twitcrusader.c \
../src/twitter.c 

OBJS += \
./src/function.o \
./src/gethttp.o \
./src/gtkwindows.o \
./src/timeline.o \
./src/twitcrusader.o \
./src/twitter.o 

C_DEPS += \
./src/function.d \
./src/gethttp.d \
./src/gtkwindows.d \
./src/timeline.d \
./src/twitcrusader.d \
./src/twitter.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -DICONS_DIR=\""/Development/Workspace/TwitCrusader/img"\" -o"$@" "$<" `pkg-config --cflags --libs gtk+-2.0 oauth libxml-2.0`
	@echo 'Finished building: $<'
	@echo ' '

