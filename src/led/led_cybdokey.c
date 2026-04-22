#include "pico_keys.h"

#ifdef PICO_PLATFORM

static uint8_t gpio_blue = 12;
static uint8_t gpio_red = 14;


uint8_t pixel[][2] = {
    {0, 0}, // 0: off
    {0, 1}, // 1: red
    {1, 0}, // 2: blue
    {1, 1}  // 3: purple

};

static void led_driver_init_cybdokey(void) {
    if (phy_data.led_gpio_present) {
        gpio = phy_data.led_gpio;
    }
    gpio_init(gpio_blue);
    gpio_set_dir(gpio_blue, GPIO_OUT);
    gpio_init(gpio_red);
    gpio_set_dir(gpio_red, GPIO_OUT);

}

static void led_driver_color_cybdokey(uint8_t color, uint32_t led_brightness, float progress) {
    (void)led_brightness;
    if (progress < 0.5) {
        color = LED_COLOR_OFF;
    }
    gpio_put(gpio_blue, pixel[color][0]);
    gpio_put(gpio_red, pixel[color][1]);
}

led_driver_t led_driver_cybdokey = {
    .init = led_driver_init_cybdokey,
    .set_color = led_driver_color_cybdokey,
};

#endif
