#include <stdio.h>
#include <stdint.h>

#include "pico/stdio.h"

#include "i2c_setup.h"
#include "adc_setup.h"
#include "oled_setup.h"
#include "temperature.h"

int main()
{
    stdio_init_all();

    // Configurações iniciais
    setup_i2c1();    
    setup_adc();
    setup_oled();

    return 0;
}
