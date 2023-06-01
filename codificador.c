#include "codificador.h"
#include <stddef.h>
#include <stdio.h>

char codificar_dai_a(uint8_t rotor[], char caracter){
	return (rotor[(caracter - 'a')] + 'a');
}

char codificar_iad_a(uint8_t rotor[], char caracter){
	size_t i = 0;	
	for(; rotor[i] != (caracter - 'a'); i++);
	return (i + 'a');
}

char codificar_dai(uint8_t rotor[], char posicion, char caracter){
	char npos = (caracter - 'a') - (posicion - 'a');
	if (npos < 0)
		npos += 26;
//	printf("%d\n",npos);
	return (rotor[npos]+'a');
}

char codificar_iad(uint8_t rotor[], char posicion, char caracter){
	size_t i = 0;	
	for(; rotor[i] != (caracter - 'a'); i++);
//	printf("%d\n",i);
	char npos = (posicion - 'a')  + i;
	if (npos > 25)
		npos -= 26;
	return (npos + 'a');
}

/*int main(){
	uint8_t rotor_i[26] = {4, 10, 12, 5, 11, 6, 3, 16, 21, 25, 13, 19, 14, 22, 24, 7, 23, 20, 18, 15, 0, 8, 1, 17, 2, 9};
	char c = codificar_dai(rotor_i, 'g', 'b');	
	printf("%c", c);
	printf("%c", codificar_iad(rotor_i, 'g', c));

	return 0;
}*/
