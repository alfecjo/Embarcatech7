#ifndef DHT22_H
#define DHT22_H

#include <stdint.h>

#define MAX_TIMINGS 85  // Defina aqui se só for usar nesse arquivo

extern int DHT_PIN;  // Declare como externa

// Definição da estrutura de leitura de dados do DHT22
typedef struct
{
    float humidity;
    float temp_celsius;
} dht_reading;

// Função para ler dados do DHT22
void read_from_dht(dht_reading *result);

#endif // DHT22_H
