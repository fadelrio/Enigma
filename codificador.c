#include "codificador.h"


char codificar_dai_a(uint8_t rotor[], char caracter){
	return (rotor[(caracter - 'a')] + 'a');
}

char codificar_iad_a(uint8_t rotor[], char caracter){
	size_t i = 0;	
	for(; rotor[i] == (caracter - 'a'); i++);
	return (i + 'a');
}

char codificar_dai(uint8_t rotor[], char posicion, char caracter){
	char npos = (posicion - 'a') + (caracter - 'a');
	if (npos > 25)
		npos -= 26;
	return (rotor[npos]+'a');
}

char codificar_iad(uint8_t rotor[], char posicion, char caracter){
	size_t i = 0;	
	for(; rotor[i] == (caracter - 'a'); i++);
	char npos = (posicion - 'a')  + i;
	if (npos > 25)
		npos -= 26;
	return (npos + 'a');
}
