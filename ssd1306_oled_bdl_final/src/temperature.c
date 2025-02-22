#include "temperature.h"
#include "hardware/adc.h"

/* Para o caso de uso do sensor LM35, o qual seria mais indicado, foi testado, más não utilizado, pois
a Bitdoglab ocupa os GPIO's 26,27,28 para outras atividades. O LM35 apresentou uma temperatura, em média
aritmética, em 2 amostragens de 10 medições, um valor cercando em 3,97 à 4,21 graus Celsius, inferior
em relação ao sensor interno do RP2040.

Para pinagem recorra a figura 7 da proposta de projeto.
*/

// Garante que uma função seja executada diretamente da RAM em vez da Flash.
// útil principalmente para funções críticas de tempo real ou para evitar atrasos devido ao acesso à memória Flash.
float __not_in_flash_func(read_temperature)(void)
{
    const float conversion_factor = 3.3f / (1 << 12); // Fator de conversão para 12 bits
    uint16_t raw = adc_read();                        // Lê o valor bruto do ADC
    float voltage = raw * conversion_factor;          // Converte para tensão
    //return 27.0f - (voltage - 0.706f) / 0.001721f;    // Converte para temperatura

    // Para uso do sensor LM35, É NECESSÁRIO COMENTAR o return acima e DESCOMENTAR
    // o return abaixo, bem como observar orientações do arquivo 'adc_setup.c'.

    return voltage * 100.0f;  // Como LM35 fornece 10mV/°C, multiplicamos por 100
}
