#ifndef CODIFICADOR_H
#define CODIFICADOR_H
#include <stdint.h>


char codificar_dai_a(uint8_t rotor[], char caracter);

char codificar_iad_a(uint8_t rotor[], char caracter);

char codificar_dai(uint8_t rotor[], char posicion, char caracter);

char codificar_iad(uint8_t rotor[], char posicion, char caracter);

#endif
