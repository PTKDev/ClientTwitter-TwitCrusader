################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tools/debugger.c 

OBJS += \
./src/tools/debugger.o 

C_DEPS += \
./src/tools/debugger.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/%.o: ../src/tools/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng14 -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -DGSEAL_ENABLE -pthread -DICONS_DIR=\""/Development/WorkSpace/TwitCrusader-C/share/icons"\" -DPROG_DIR=\""Development/WorkSpace/TwitCrusader-C"\" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

