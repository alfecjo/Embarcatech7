#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "dht22.h"      // Biblioteca do sensor DHT22 para leitura de temperatura e umidade
#include "i2c_setup.h"  // Configuração do barramento I2C
#include "oled_setup.h" // Configuração do display OLED

#ifdef PICO_DEFAULT_LED_PIN
#define LED_PIN PICO_DEFAULT_LED_PIN
#endif

// Definição dos pinos de saída para os atuadores (ventoinha e lâmpada)
#define FAN_PIN 8   // Pino da ventoinha
#define LIGHT_PIN 9 // Pino da lâmpada

// GPIO utilizado para conexão de dados com o sensor DHT22
const uint READ_PIN_DATA = 28;

// Definição dos limites de temperatura para controle da ventoinha
#define TEMP_ON 38.0  // Liga a ventoinha acima de 38°C
#define TEMP_OFF 36.0 // Desliga a ventoinha abaixo de 36°C

// Variáveis para armazenar o estado dos dispositivos
bool fan_on = false;  // Estado da ventoinha (ligada/desligada)
bool light_on = false; // Estado da lâmpada (ligada/desligada)

// Função para inicializar os pinos dos atuadores
void setup_init_pin(void)
{
    // Configuração do pino da ventoinha como saída
    gpio_init(FAN_PIN);
    gpio_set_dir(FAN_PIN, GPIO_OUT);

    // Configuração do pino da lâmpada como saída
    gpio_init(LIGHT_PIN);
    gpio_set_dir(LIGHT_PIN, GPIO_OUT);
}

int main()
{
    DHT_PIN = 28; // Define o pino do sensor DHT22
    stdio_init_all(); // Inicializa a comunicação serial
    gpio_init(DHT_PIN); // Inicializa o pino do sensor DHT22

#ifdef LED_PIN
    // Configuração do LED embutido da placa (se existir)
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
#endif

    // Inicialização dos periféricos
    setup_i2c1();   // Configuração do barramento I2C
    setup_oled();   // Configuração do display OLED
    setup_init_pin(); // Configuração dos pinos da ventoinha e lâmpada

    int display_toggle = 0; // Variável para alternar a exibição no display OLED

    while (1) // Loop infinito
    {
        dht_reading reading; // Estrutura para armazenar os dados do sensor
        read_from_dht(&reading); // Lê os valores de temperatura e umidade do DHT22

        // Controle da ventoinha baseado na temperatura medida
        if (reading.temp_celsius >= TEMP_ON) // Se a temperatura for maior ou igual ao limite de ativação
        {
            if (!fan_on) // Se a ventoinha estiver desligada, liga
            {
                gpio_put(FAN_PIN, 1);
                fan_on = true;
            }
            gpio_put(LIGHT_PIN, 0); // Desliga a lâmpada
            light_on = false;
        }
        else if (reading.temp_celsius <= TEMP_OFF) // Se a temperatura for menor ou igual ao limite de desativação
        {
            if (fan_on) // Se a ventoinha estiver ligada, desliga
            {
                gpio_put(FAN_PIN, 0);
                fan_on = false;
            }
            gpio_put(LIGHT_PIN, 1); // Liga a lâmpada
            light_on = true;
        }

        // Alterna a exibição entre temperatura e umidade no display OLED
        if (display_toggle % 2 == 0)
        {
            update_oled(reading.temp_celsius); // Exibe a temperatura
        }
        else
        {
            update_oled(reading.humidity); // Exibe a umidade
        }

        display_toggle++; // Alterna a exibição na próxima iteração
        sleep_ms(1500); // Aguarda 1,5 segundos antes da próxima leitura
    }
}
