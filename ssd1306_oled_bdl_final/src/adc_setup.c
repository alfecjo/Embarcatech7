#include "hardware/adc.h"
#include "adc_setup.h"

/* Para o caso de uso do sensor LM35, o qual seria mais indicado, foi testado, más não utilizado, pois
a Bitdoglab ocupa os GPIO's 26,27,28 para outras atividades. O LM35 apresentou uma temperatura, em média
aritmética, em 2 amostragens de 10 medições, um valor cercando em 3,97 à 4,21 graus Celsius, inferior
em relação ao sensor interno do RP2040.

Para pinagem recorra a figura 7 da proposta de projeto, bem como: Figura 12: Circuito Completo.
*/

void setup_adc()
{
    adc_init(); // Inicializa o ADC
    // adc_set_temp_sensor_enabled(true);    // Habilita o sensor de temperatura interno
    // adc_select_input(4);                  // Canal 4 é o sensor de temperatura interno

    // Para uso do sensor LM35 É NECESSÁRIO COMENTAR as duas funções acima e DESCOMENTAR
    // as duas abaixo, bem como observar orientações do arquivo 'temperature.c'.

    adc_set_temp_sensor_enabled(false); // Desativa o sensor de temperatura interno
    adc_select_input(2);                // Escolhe o ADC0 (GP28) - Selecionar um ADC externo (GP26, GP27 ou GP28).
}