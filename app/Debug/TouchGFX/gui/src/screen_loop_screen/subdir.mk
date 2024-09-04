################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/screen_loop_screen/screen_loopPresenter.cpp \
../TouchGFX/gui/src/screen_loop_screen/screen_loopView.cpp 

OBJS += \
./TouchGFX/gui/src/screen_loop_screen/screen_loopPresenter.o \
./TouchGFX/gui/src/screen_loop_screen/screen_loopView.o 

CPP_DEPS += \
./TouchGFX/gui/src/screen_loop_screen/screen_loopPresenter.d \
./TouchGFX/gui/src/screen_loop_screen/screen_loopView.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/screen_loop_screen/%.o TouchGFX/gui/src/screen_loop_screen/%.su TouchGFX/gui/src/screen_loop_screen/%.cyclo: ../TouchGFX/gui/src/screen_loop_screen/%.cpp TouchGFX/gui/src/screen_loop_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-screen_loop_screen

clean-TouchGFX-2f-gui-2f-src-2f-screen_loop_screen:
	-$(RM) ./TouchGFX/gui/src/screen_loop_screen/screen_loopPresenter.cyclo ./TouchGFX/gui/src/screen_loop_screen/screen_loopPresenter.d ./TouchGFX/gui/src/screen_loop_screen/screen_loopPresenter.o ./TouchGFX/gui/src/screen_loop_screen/screen_loopPresenter.su ./TouchGFX/gui/src/screen_loop_screen/screen_loopView.cyclo ./TouchGFX/gui/src/screen_loop_screen/screen_loopView.d ./TouchGFX/gui/src/screen_loop_screen/screen_loopView.o ./TouchGFX/gui/src/screen_loop_screen/screen_loopView.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-screen_loop_screen

