set(APP_LED_SRCS 
    "src/common.c"
)
set(APP_LED_INCLUDE_DIRS 
    "include/public"
)
set(APP_LED_PRIV_INCLUDE_DIRS 
    "include/private"
)
set(APP_LED_PRIV_REQUIRES
    "led_strip"
    "esp_driver_ledc"
)

### WS2812 ###
if (CONFIG_APP_LED_TYPE_WS2812)
    list(APPEND APP_LED_SRCS "src/ws2812_impl.c")

### LEDC ###
elseif (CONFIG_APP_LED_TYPE_LEDC)
    list(APPEND APP_LED_SRCS "src/ledc_impl.c")
    if ("${IDF_VERSION_MAJOR}.${IDF_VERSION_MINOR}" VERSION_LESS_EQUAL "5.4")
        # ESP-IDF v5.4 and below require a manual include of the esp_driver_gpio component include directory.
        list(APPEND APP_LED_INCLUDE_DIRS "${IDF_PATH}/components/esp_driver_gpio/include")
    endif()
endif()

idf_component_register(
    SRCS ${APP_LED_SRCS}
    INCLUDE_DIRS ${APP_LED_INCLUDE_DIRS}
    PRIV_INCLUDE_DIRS ${APP_LED_PRIV_INCLUDE_DIRS}
    PRIV_REQUIRES ${APP_LED_PRIV_REQUIRES}
)