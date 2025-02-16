#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "ssd1306.h"

void setup_i2c1(void);
void setup_adc(void);
void setup_oled(void);
float read_temperature(void);

int main()
{
    stdio_init_all();

    setup_i2c1();
    
    setup_adc();

    setup_oled();

    return 0;
}

void setup_i2c1(void)
{
    i2c_init(i2c1, 400000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);
}

void setup_adc()
{
    adc_init();                        // Inicializa o ADC
    adc_set_temp_sensor_enabled(true); // Habilita o sensor de temperatura interno
    adc_select_input(4);               // Canal 4 é o sensor de temperatura interno
}

void setup_oled(void)
{
    ssd1306_t disp;
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);

    for (;;)
    {        
        float temp = read_temperature();
        char temp_str[20];
        snprintf(temp_str, sizeof(temp_str), "Temp: %.1f C", temp);
        ssd1306_clear(&disp);
        ssd1306_draw_string(&disp, 10, 24, 2, temp_str);
        ssd1306_show(&disp);
        sleep_ms(2000);
    }
}

float read_temperature(void)
{
    const float conversion_factor = 3.3f / (1 << 12);
    uint16_t raw = adc_read();
    float voltage = raw * conversion_factor;
    return 27.0f - (voltage - 0.706f) / 0.001721f;
}
