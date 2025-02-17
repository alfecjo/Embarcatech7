#include <stdio.h>

#include "ssd1306.h"
#include "oled_setup.h"
#include "temperature.h"

void setup_oled(void)
{
    ssd1306_t disp;
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);

    for (;;)
    {        
        float temp = read_temperature();  // Lê a temperatura
        char temp_str[20];
        snprintf(temp_str, sizeof(temp_str), "Temp: %.1f C", temp);
        ssd1306_clear(&disp);
        ssd1306_draw_string(&disp, 10, 24, 2, temp_str);  // Exibe a temperatura no OLED
        ssd1306_show(&disp);
        sleep_ms(2000);  // Aguarda 2 segundos antes de atualizar
    }
}
