/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file app_button.c
 * @brief App button implementation.
 */

/* Includes ****************************************************************/

/* Declarations */
#include "app_button.h"

/* Standard includes */
#include <stddef.h>

/* espressif/button includes */
#include "button_gpio.h"

/* Preprocessor definitions ****************************************************/

#define GPIO_NUM CONFIG_APP_BUTTON_GPIO_NUM
#ifdef CONFIG_APP_BUTTON_IS_ACTIVE_HIGH
#define IS_ACTIVE_HIGH 1
#else
#define IS_ACTIVE_HIGH 0
#endif

/* Public function definitions ****************************************************/

esp_err_t app_button_init(app_button_config_t *config)
{
    /* Validate the configuration. */
    if (config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    /* Create GPIO button */
    const button_config_t btn_cfg = {0};
    const button_gpio_config_t btn_gpio_cfg = {
        .gpio_num = GPIO_NUM,
        .active_level = IS_ACTIVE_HIGH,
    };
    button_handle_t gpio_btn = NULL;
    esp_err_t ret = iot_button_new_gpio_device(&btn_cfg, &btn_gpio_cfg, &gpio_btn);
    if (gpio_btn == NULL) {
        return ret;
    }

    /* Set the callbacks. */
    if (config->callbacks.on_short_press != NULL) {
        iot_button_register_cb(gpio_btn, BUTTON_SINGLE_CLICK, NULL, config->callbacks.on_short_press, NULL);
    }
    if (config->callbacks.on_long_press != NULL) {
        iot_button_register_cb(gpio_btn, BUTTON_LONG_PRESS_START, NULL, config->callbacks.on_long_press, NULL);
    }

    return ESP_OK;
}