# app_led

This is a driver for LED modules on ESP development boards, supporting:
- WS2812 LED strips ([example](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c6/esp32-c6-devkitc-1/user_guide.html#id12))
- LEDC ([example](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c2/esp8684-devkitm-1/user_guide.html#id7))

## Required configuration

When configuring your project, be sure to select:
- **LED module type**: `CONFIG_APP_LED_TYPE`
    - LEDC: `CONFIG_APP_LED_TYPE_LEDC=y`
    - WS2812: `CONFIG_APP_LED_TYPE_WS2812=y` (default)
- **GPIO pins**:
    - LEDC: `APP_LED_LEDC_GPIO_NUM_[R/G/B]` (default: R=0, G=1, B=8)
    - WS2812: `APP_LED_WS2812_GPIO_NUM=?` (default: 8)

Or if using `idf.py menuconfig`, then head to `Component config > App LED Control`.