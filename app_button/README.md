# app_button

This is a driver for buttons on ESP development boards. It allows quick registration of callbacks with the BOOT button by default.

## Required configuration

If your BOOT button is non-standard, or using a different button, you should configure:
- **GPIO pin**: `CONFIG_APP_BUTTON_GPIO_NUM=?` (default: 9)
- **Active level**: `CONFIG_APP_BUTTON_IS_ACTIVE_HIGH=[y/n]` (default: y)

Or if using `idf.py menuconfig`, then head to `Component config > ESP RainMaker App Button Configuration`.