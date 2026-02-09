/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file ws2812_impl.c
 * @brief implementation of the app_led.h interface for WS2812 LED strips.
 */

/* Includes ****************************************************************/

/* Declarations */
#include "app_led_internal.h"

/* Standard includes */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* ESP-IDF includes */
#include "esp_err.h"
#include "esp_log.h"
#include "led_strip.h"

/* Preprocessor definitions ****************************************************/

#define LED_STRIP_GPIO_PIN CONFIG_APP_LED_WS2812_GPIO_NUM   // GPIO pin connected to the LED strip's data line
#define LED_STRIP_LED_COUNT (1)                             // 1 LED in the strip
#define LED_STRIP_RMT_RES_HZ (10 * 1000 * 1000)             // 10 MHz
#define LED_STRIP_MEMORY_BLOCK_WORDS (0)                    // 0 means automatic
#define LED_STRIP_USE_DMA (0)                               // 0 means no DMA

/* Variables ****************************************************************/

/**
 * @brief Tag for logging.
 */
static const char *TAG = "app_led_ws2812";

/**
 * @brief LED strip handle.
 */
static led_strip_handle_t __led_strip = NULL;

/* Private function declarations ****************************************************/

/**
 * @brief Set the current color of the LED in RGB format.
 */
static esp_err_t __ws2812_set_current_color_rgb(void);

/* Private function definitions ****************************************************/

static esp_err_t __ws2812_set_current_color_rgb(void)
{
    esp_err_t ret = ESP_OK;
    ret = led_strip_set_pixel(__led_strip, 0, __current_color_rgb.red, __current_color_rgb.green, __current_color_rgb.blue);
    if (ret != ESP_OK) {
        return ret;
    }
    ret = led_strip_refresh(__led_strip);
    if (ret != ESP_OK) {
        return ret;
    }
    return ret;
}

/* Public function definitions ****************************************************/

esp_err_t app_led_init(void)
{
    // LED strip general initialization, according to your led board design
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_GPIO_PIN, // The GPIO that connected to the LED strip's data line
        .max_leds = 1,      // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812,        // LED strip model
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color order of the strip: GRB
        .flags = {
            .invert_out = false, // don't invert the output signal
        }
    };

    /* Use RMT if available */
#if defined(SOC_RMT_CLKS)
    // LED strip backend configuration: RMT
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,        // different clock source can lead to different power consumption
        .resolution_hz = LED_STRIP_RMT_RES_HZ, // RMT counter clock frequency
        .mem_block_symbols = LED_STRIP_MEMORY_BLOCK_WORDS, // the memory block size used by the RMT channel
        .flags = {
            .with_dma = LED_STRIP_USE_DMA,     // Using DMA can improve performance when driving more LEDs
        }
    };

    return led_strip_new_rmt_device(&strip_config, &rmt_config, &__led_strip);

    /* Fallback to SPI if RMT is not available */
#elif defined(SOC_SPI_CLKS) && defined(SOC_SPI_PERIPH_NUM) && SOC_SPI_PERIPH_NUM >= 2
    // LED strip backend configuration: SPI
    led_strip_spi_config_t spi_config = {
        .clk_src = SPI_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
        .spi_bus = SPI2_HOST,           // SPI bus ID
        .flags = {
            .with_dma = LED_STRIP_USE_DMA, // Using DMA can improve performance and help drive more LEDs
        }
    };
    return led_strip_new_spi_device(&strip_config, &spi_config, &__led_strip);
#endif

    /* No backend available */
    ESP_LOGE(TAG, "No backend available");
    return ESP_FAIL;
}

esp_err_t app_led_set_power(bool power)
{
    __is_power_on = power;
    if (power) {
        return __ws2812_set_current_color_rgb();
    } else {
        /* avoid overwriting the current color */
        return led_strip_clear(__led_strip);
    }
}
esp_err_t app_led_set_color_hsv(app_led_color_hsv_t color_hsv)
{
    __internal_hsv_to_rgb(color_hsv, &__current_color_rgb);
    if (__is_power_on) {
        return __ws2812_set_current_color_rgb();
    } else {
        return ESP_OK;
    }
}

esp_err_t app_led_set_color_rgb(app_led_color_rgb_t color_rgb)
{
    __current_color_rgb = color_rgb;
    if (__is_power_on) {
        return __ws2812_set_current_color_rgb();
    } else {
        return ESP_OK;
    }
}