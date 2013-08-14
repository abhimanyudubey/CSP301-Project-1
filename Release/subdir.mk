################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../imageloader.cpp \
../main.cpp \
../vec3f.cpp 

C_SRCS += \
../glm1.c 

OBJS += \
./glm1.o \
./imageloader.o \
./main.o \
./vec3f.o 

C_DEPS += \
./glm1.d 

CPP_DEPS += \
./imageloader.d \
./main.d \
./vec3f.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/opt/local/lib -I/usr/llvm-gcc-4.2 -I/opt/X11/include/GL -I"/Users/abhimanyu/git/csp301" -I/Users/abhimanyu/Downloads/opencv-2.4.6 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/local/lib -I/usr/llvm-gcc-4.2 -I/opt/X11/include/GL -I"/Users/abhimanyu/git/csp301" -I/Users/abhimanyu/Downloads/opencv-2.4.6 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


