#include <stdio.h>

#include "ssd1306.h"
#include "oled_setup.h"

// Estrutura global do display
ssd1306_t disp;

void setup_oled(void)
{    
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);
}

// Função para atualizar a temperatura no OLED
void update_oled(float temperatura)
{
    char temp_str[20];
    snprintf(temp_str, sizeof(temp_str), "Temp: %.1f C", temperatura);
    ssd1306_clear(&disp);
    ssd1306_draw_string(&disp, 10, 24, 2, temp_str);
    ssd1306_show(&disp);
}