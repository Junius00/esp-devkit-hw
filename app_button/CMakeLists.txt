set(APP_BUTTON_SRCS "src/app_button.c")
set(APP_BUTTON_INCLUDE_DIRS "include")
set(APP_BUTTON_REQUIRES "button")

idf_component_register(
    SRCS ${APP_BUTTON_SRCS}
    INCLUDE_DIRS ${APP_BUTTON_INCLUDE_DIRS}
    REQUIRES ${APP_BUTTON_REQUIRES}
)