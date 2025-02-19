#include "hardware/adc.h"
#include "adc_setup.h"

void setup_adc()
{
    adc_init();                        // Inicializa o ADC
    adc_set_temp_sensor_enabled(true); // Habilita o sensor de temperatura interno
    adc_select_input(4);               // Canal 4 é o sensor de temperatura interno
}
