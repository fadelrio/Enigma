#ifndef ENIGMA_H
#define ENIGMA_H

#include <stdint.h>

typedef struct enigma enigma_t;

//recibe un arreglo de 3 rotores y un reflector de 26 elementos con numeros entre el 0 y el 25 y crea una instancia de la estrictura de tipo enigma_t 
enigma_t *crear_enigma(uint8_t rotores[][26], uint8_t *reflector);

void set_posiciones_iniciales(char r1, char r2, char r3, enigma_t *enigma);

void destruir_enigma(enigma_t *enigma);

void codificar_linea(const char *entrada, char *salida, enigma_t *enigma);
//para su correcto funcionamiento las posiciones iniciales de enigma deben ser las mismas que cuando se codifico dicha linea
void decodificar_linea(const char *entrada, char *salida, enigma_t *enigma);



#endif
