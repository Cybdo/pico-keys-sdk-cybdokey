#include "led/led.h"
#include "picokeys.h"

#if defined(PICO_PLATFORM)
#include "hardware/gpio.h"
#endif

#ifdef PICO_PLATFORM

static uint8_t gpio_blue = 12;
static uint8_t gpio_red = 14;

static const uint8_t pixel[][2] = {
    {0, 0}, // 0: off
    {0, 1}, // 1: red
    {1, 0}, // 2: green (mapped to blue on 2-channel LED)
    {1, 0}, // 3: blue
    {0, 1}, // 4: yellow (mapped to red on 2-channel LED)
    {1, 1}, // 5: magenta
    {1, 0}, // 6: cyan (mapped to blue on 2-channel LED)
    {1, 1}  // 7: white (mapped to both)
};

static void led_driver_init_cybdokey(void) {
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
    if (color >= (sizeof(pixel) / sizeof(pixel[0]))) {
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
