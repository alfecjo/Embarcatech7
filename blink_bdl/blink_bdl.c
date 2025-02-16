/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 10250
#endif

#ifndef LED_PIN_LIGHT
#define LED_PIN_LIGHT 8
#endif

#ifndef LED_PIN_FAN
#define LED_PIN_FAN 9
#endif

// Perform initialisation
int pico_led_init(void)
{
#if defined(LED_PIN_LIGHT)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(LED_PIN_LIGHT);
    gpio_set_dir(LED_PIN_LIGHT, GPIO_OUT);    
#endif

#if defined(LED_PIN_FAN)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(LED_PIN_FAN);
    gpio_set_dir(LED_PIN_FAN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
#endif
}

// Turn the led on or off
void pico_set_led_light(bool led_on)
{
#if defined(LED_PIN_LIGHT)
    // Just set the GPIO on or off
    gpio_put(LED_PIN_LIGHT, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

// Turn the led on or off
void pico_set_led_fan(bool led_on)
{
#if defined(LED_PIN_FAN)
    // Just set the GPIO on or off
    gpio_put(LED_PIN_FAN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

int main()
{
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);
    while (true)
    {
        pico_set_led_light(true);
        sleep_ms(LED_DELAY_MS);
        pico_set_led_light(false);
        

        pico_set_led_fan(true);
        sleep_ms(LED_DELAY_MS);
        pico_set_led_fan(false);
    }
}
