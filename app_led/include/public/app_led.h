/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file app_led.h
 * @brief Control the LED present on most ESP development boards.
*/

#ifndef __APP_LED_H__
#define __APP_LED_H__

/* Standard includes */
#include <stdbool.h>
#include <stdint.h>

/* ESP-IDF includes */
#include "esp_err.h"

/* Types ****************************************************************/

typedef struct {
    uint16_t hue; // 0-360
    uint8_t saturation; // 0-100
    uint8_t brightness; // 0-100
} app_led_color_hsv_t;

typedef struct {
    uint8_t red; // 0-255
    uint8_t green; // 0-255
    uint8_t blue; // 0-255
} app_led_color_rgb_t;

/* Public function declarations ****************************************************/

/**
 * @brief Initialize the LED.
 *
 * @return ESP_OK on success, otherwise error code.
 */
esp_err_t app_led_init(void);

/**
 * @brief Set the power of the LED.
 *
 * @param[in] power True to turn on the LED, false to turn off the LED.
 *
 * @return ESP_OK on success, otherwise error code.
 */
esp_err_t app_led_set_power(bool power);

/**
 * @brief Set the color of the LED in HSV format.
 *
 * @param[in] color_hsv The color of the LED.
 *
 * @return ESP_OK on success, otherwise error code.
 */
esp_err_t app_led_set_color_hsv(app_led_color_hsv_t color_hsv);

/**
 * @brief Set the color of the LED in RGB format.
 *
 * @param[in] color_rgb The color of the LED.
 *
 * @return ESP_OK on success, otherwise error code.
 */
esp_err_t app_led_set_color_rgb(app_led_color_rgb_t color_rgb);

#endif /* __APP_LED_H__ */