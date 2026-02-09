/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file app_button.h
 * @brief App button header file.
 */

#ifndef __APP_BUTTON_H__
#define __APP_BUTTON_H__

/* Includes ****************************************************************/

/* ESP-IDF includes */
#include "esp_err.h"
#include "iot_button.h"

/* Types ****************************************************************/

/**
 * @brief Callback for any button event. Follows the button_cb_t type.
 */
typedef button_cb_t app_button_callback_t;

/**
 * @brief Callbacks for the button.
 */
typedef struct {
    app_button_callback_t on_short_press; // Callback for short press. NULL if not needed.
    app_button_callback_t on_long_press; // Callback for long press. NULL if not needed.
} app_button_callbacks_t;

/**
 * @brief Configuration for the button.
 *
 * @param[in] timing_config Timing configuration for the button.
 * @param[in] callbacks Callbacks for the button.
 */
typedef struct {
    /** Timing configuration for the button. */
    button_config_t timing_config;
    /** Callbacks for the button. */
    app_button_callbacks_t callbacks;
} app_button_config_t;

/* Public function declarations ****************************************************/

/**
 * @brief Initialize the button.
 *
 * @param[in] config Configuration for the button.
 *
 * @return ESP_OK on success, otherwise error code.
 */
esp_err_t app_button_init(app_button_config_t *config);

#endif /* __APP_BUTTON_H__ */