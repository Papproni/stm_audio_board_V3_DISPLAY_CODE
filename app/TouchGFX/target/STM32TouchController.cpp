/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.22.1. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>
#include "ili9341.h"
#include "xpt2046.h"

extern "C" {
static void ConvXPTtoILI(uint16_t *x, uint16_t *y)
{
	int16_t tx,ty;
//	tx = (int16_t)(((int32_t)*x - XPT_XMIN) * GUI_WIDTH / XPT_WIDTH);
//	tx = (tx < 0) ? 0 : tx;
//	tx = (tx >= GUI_WIDTH) ? GUI_WIDTH-1 : tx;
//	ty = (int16_t)(((int32_t)*y - XPT_YMIN) * GUI_HEIGHT / XPT_HEIGHT);
//	ty = (ty < 0) ? 0 : ty;
//	ty = (ty >= GUI_HEIGHT) ? GUI_HEIGHT-1 : ty;
//	*x = tx;
//	*y = ty;
//
    // Invert x-coordinate for 180-degree rotation
    tx = (int16_t)(((int32_t)*x - XPT_XMIN) * GUI_WIDTH / XPT_WIDTH);
    tx = GUI_WIDTH - 1 - tx; // Invert the x-coordinate
    tx = (tx < 0) ? 0 : tx;
    tx = (tx >= GUI_WIDTH) ? GUI_WIDTH - 1 : tx;

    // Invert y-coordinate for 180-degree rotation
    ty = (int16_t)(((int32_t)*y - XPT_YMIN) * GUI_HEIGHT / XPT_HEIGHT);
    ty = GUI_HEIGHT - 1 - ty; // Invert the y-coordinate
    ty = (ty < 0) ? 0 : ty;
    ty = (ty >= GUI_HEIGHT) ? GUI_HEIGHT - 1 : ty;

    *x = tx;
    *y = ty;
}
}

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */

    // XPT2046_Update() only writes *x/*y while the finger is on the pad
    // (pressure above threshold). Pre-filling with out-of-range sentinels
    // turns "no write" into a reliable no-touch signal, and also removes
    // the previous use of uninitialized values when nothing was written.
    uint16_t intx = 0; // 0 < XPT_XMIN(350) -> never reasonable
    uint16_t inty = 0;
    XPT2046_Update(&intx, &inty);

    if (XPT2046_IsReasonable(intx, inty)) {
        ConvXPTtoILI(&intx, &inty);
        x = (int32_t)intx;
        y = (int32_t)inty;
        // Report touch for EVERY tick the finger is on the pad - even when
        // the coordinates have not changed. The framework then keeps the
        // button in its PRESSED state and only emits RELEASED after the
        // finger really leaves the pad, so actions fire on release, never
        // while the finger is still resting on the screen. Moving fingers
        // still deliver coordinate changes exactly as before (sliders,
        // scroll areas and drag gestures are unaffected).
        return true;
    }
    // Finger actually off the pad -> framework debounce will emit RELEASED.
    return false;
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
