################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsPresenter.cpp \
../TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsView.cpp 

OBJS += \
./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsPresenter.o \
./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsView.o 

CPP_DEPS += \
./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsPresenter.d \
./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsView.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/gui/src/screen_fx_params_screen/%.o TouchGFX/gui/src/screen_fx_params_screen/%.su TouchGFX/gui/src/screen_fx_params_screen/%.cyclo: ../TouchGFX/gui/src/screen_fx_params_screen/%.cpp TouchGFX/gui/src/screen_fx_params_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-gui-2f-src-2f-screen_fx_params_screen

clean-TouchGFX-2f-gui-2f-src-2f-screen_fx_params_screen:
	-$(RM) ./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsPresenter.cyclo ./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsPresenter.d ./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsPresenter.o ./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsPresenter.su ./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsView.cyclo ./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsView.d ./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsView.o ./TouchGFX/gui/src/screen_fx_params_screen/screen_fx_paramsView.su

.PHONY: clean-TouchGFX-2f-gui-2f-src-2f-screen_fx_params_screen
