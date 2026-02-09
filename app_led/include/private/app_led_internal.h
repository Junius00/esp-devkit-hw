/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file app_led_internal.h
 * @brief Internal app_led variables and functions.
 */

#ifndef __APP_LED_INTERNAL_H__
#define __APP_LED_INTERNAL_H__

/* Includes *******************************************************/

/* Types */
#include "app_led.h"

/* Standard includes */
#include <stdbool.h>

/* Variables *******************************************************/

/**
 * @brief Current color of the LED in RGB format.
 */
extern app_led_color_rgb_t __current_color_rgb;

/**
 * @brief Whether the power is on.
 */
extern bool __is_power_on;

/* Public function declarations ****************************************************/

/**
 * @brief Convert HSV to RGB.
 *
 * @param[in] color_hsv The color in HSV format.
 * @param[out] color_rgb Pointer to the color in RGB format.
 */
void __internal_hsv_to_rgb(app_led_color_hsv_t color_hsv, app_led_color_rgb_t *color_rgb);

#endif /* __APP_LED_INTERNAL_H__ */