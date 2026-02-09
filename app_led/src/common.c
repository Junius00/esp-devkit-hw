/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file common.c
 * @brief Common functions for the app_led.
 */

/* Includes ****************************************************************/

#include "app_led_internal.h"

/* Standard includes */
#include <stdint.h>
#include <stdbool.h>

/* Variables ****************************************************************/

app_led_color_rgb_t __current_color_rgb = {
    .red = 0,
    .green = 0,
    .blue = 0,
};

bool __is_power_on = false;

/* Public function definitions ****************************************************/

void __internal_hsv_to_rgb(app_led_color_hsv_t color_hsv, app_led_color_rgb_t *color_rgb)
{
    uint16_t h = color_hsv.hue % 360;
    uint8_t s = color_hsv.saturation;
    uint8_t v = color_hsv.brightness;

    uint16_t rgb_max = v * 2.55f;
    uint16_t rgb_min = rgb_max * (100 - s) / 100.0f;

    uint16_t i = h / 60;
    uint16_t diff = h % 60;

    // RGB adjustment amount by hue
    uint16_t rgb_adj = (rgb_max - rgb_min) * diff / 60;

    switch (i) {
    case 0:
        color_rgb->red = rgb_max;
        color_rgb->green = rgb_min + rgb_adj;
        color_rgb->blue = rgb_min;
        break;
    case 1:
        color_rgb->red = rgb_max - rgb_adj;
        color_rgb->green = rgb_max;
        color_rgb->blue = rgb_min;
        break;
    case 2:
        color_rgb->red = rgb_min;
        color_rgb->green = rgb_max;
        color_rgb->blue = rgb_min + rgb_adj;
        break;
    case 3:
        color_rgb->red = rgb_min;
        color_rgb->green = rgb_max - rgb_adj;
        color_rgb->blue = rgb_max;
        break;
    case 4:
        color_rgb->red = rgb_min + rgb_adj;
        color_rgb->green = rgb_min;
        color_rgb->blue = rgb_max;
        break;
    default:
        color_rgb->red = rgb_max;
        color_rgb->green = rgb_min;
        color_rgb->blue = rgb_max - rgb_adj;
        break;
    }
}