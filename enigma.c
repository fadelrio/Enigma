#include "enigma.h"
#include "codificador.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static char codificar(char c, enigma_t *enigma);

static char decodificar(char c, enigma_t *enigma);

static void avanzar_rotores(enigma_t *enigma);

//static void retrasar_rotores(enigma_t *enigma);

struct enigma {
	uint8_t **rotores;
	uint8_t *reflector;
	uint8_t *posiciones_actuales; //siempre entre 0 y 25
};

enigma_t *crear_enigma(uint8_t rotores[][26], uint8_t *reflector){
	enigma_t *enigma = malloc(sizeof(enigma_t));
	if (enigma == NULL)
		return NULL;
	enigma->rotores = malloc(3 * sizeof(uint8_t*));
	if (enigma->rotores == NULL)
		return NULL;
	size_t n = 26 * sizeof(uint8_t);
	for (size_t i = 0; i < 3; i++){
		enigma->rotores[i] = malloc(n);
		if (enigma->rotores[i] == NULL)
			return NULL;
		memcpy(enigma->rotores[i], rotores[i], n);
	}
	enigma->reflector = malloc(n);
	if (enigma->reflector == NULL)
		return NULL;
	memcpy(enigma->reflector, reflector, n);
	enigma->posiciones_actuales = malloc(3 * sizeof(uint8_t));
	if (enigma->posiciones_actuales == NULL)
		return NULL;
	return enigma;	
}

void set_posiciones_iniciales(char r1, char r2, char r3, enigma_t *enigma){
	enigma->posiciones_actuales[0] = r1;
	enigma->posiciones_actuales[1] = r2;
	enigma->posiciones_actuales[2] = r3;
}

void destruir_enigma(enigma_t *enigma){
	free(enigma->reflector);
	free(enigma->posiciones_actuales);
	for (size_t i = 0; i < 3; i++)
		free(enigma->rotores[i]);
	free(enigma->rotores);
	free(enigma);
}

void codificar_linea(const char *entrada, char *salida, enigma_t *enigma){
	size_t i = 0;	
	for(; entrada[i] != '\0'; i++){
		if(!isalpha(entrada[i])){
			salida[i] = entrada[i];			
			continue;
		}
		char c = tolower(entrada[i]);
		
		salida[i] = codificar(c, enigma);
	}
	salida[i] = '\0';
}

void decodificar_linea(const char *entrada, char *salida, enigma_t *enigma){
	size_t i = 0;	
	for(; entrada[i] != '\0'; i++){
		if(!isalpha(entrada[i])){
			salida[i] = entrada[i];			
			continue;
		}
		char c = tolower(entrada[i]);
		
		salida[i] = decodificar(c, enigma);
	}
	salida[i] = '\0';
}

static char codificar(char c, enigma_t *enigma){	
	for (char i = 0; i < 3; i++)
		c = codificar_dai(enigma->rotores[i], enigma->posiciones_actuales[i] + 'a',c);
	c = codificar_dai_a (enigma->reflector, c);
	//printf("%c\n",c);
	for (char i = 2; i >= 0; i--)
		c = codificar_iad(enigma->rotores[i], enigma->posiciones_actuales[i] + 'a',c);
	avanzar_rotores(enigma);
	//printf("%c\n",c);
	return c;
}

static char decodificar(char c, enigma_t *enigma){
	for (char i = 0; i < 3; i++){
		c = codificar_dai(enigma->rotores[i], enigma->posiciones_actuales[i] + 'a',c);
		//printf("%c\n",c);
	}
	//printf("%c\n",c);
	c = codificar_iad_a (enigma->reflector, c);
	//printf("%c\n",c);
	for (char i = 2; i >= 0; i--){
		c = codificar_iad(enigma->rotores[i], enigma->posiciones_actuales[i] + 'a',c);
		//printf("%c\n",c);
	}
	avanzar_rotores(enigma);
	//printf("%c\n",c);
	return c;
}

static void avanzar_rotores(enigma_t *enigma){
	enigma->posiciones_actuales[0]++;
	if (enigma->posiciones_actuales[0] > 25){
		enigma->posiciones_actuales[1]++;
		enigma->posiciones_actuales[0] -= 26;	
	}
	if (enigma->posiciones_actuales[1] > 25){
		enigma->posiciones_actuales[2]++;
		enigma->posiciones_actuales[1] -= 26;	
	}
	if(enigma->posiciones_actuales[2] > 25)
		enigma->posiciones_actuales[2] -= 26;
}
/*static void retrasar_rotores(enigma_t *enigma){
	enigma->posiciones_actuales[0]--;
	if (enigma->posiciones_actuales[0] < 0){
		enigma->posiciones_actuales[1]--;
		enigma->posiciones_actuales[0] += 26;	
	}
	if (enigma->posiciones_actuales[1] < 0){
		enigma->posiciones_actuales[2]--;
		enigma->posiciones_actuales[1] += 26;	
	}
	if(enigma->posiciones_actuales[2] < 0)
		enigma->posiciones_actuales[2] +=26;
}*/

/*int main(){
	
	uint8_t rotores[][26] = {{4, 10, 12, 5, 11, 6, 3, 16, 21, 25, 13, 19, 14, 22, 24, 7, 23, 20, 18, 15, 0, 8, 1, 17, 2, 9},
	{0, 9, 3, 10, 18, 8, 17, 20, 23, 1, 11, 7, 22, 19, 12, 2, 16, 6, 25, 13, 15, 24, 5, 21, 14, 4},
	{1, 3, 5, 7, 9, 11, 2, 15, 17, 19, 23, 21, 25, 13, 24, 4, 8, 22, 6, 0, 10, 12, 20, 18, 16, 14},
	};
	
	uint8_t reflector_a[] = {4, 9, 12, 25, 0, 11, 24, 23, 21, 1, 22, 5, 2, 17, 16, 20, 14, 13, 19, 18, 15, 8, 10, 7, 6, 3};

	enigma_t *enigma = crear_enigma(rotores, reflector_a);
	set_posiciones_iniciales(0,0,0, enigma);

	char c = codificar('a', enigma);
	printf("%c\n",c);
	printf("pos %d", enigma->posiciones_actuales[0]);
	char d = codificar('o', enigma);
	printf("%c\n",d);
	char e = codificar('z', enigma);
	printf("%c\n",e);
	set_posiciones_iniciales(0,0,0, enigma);
	printf("%c\n", decodificar(c, enigma));
	printf("%c\n", decodificar(d, enigma));
	printf("%c\n", decodificar(e, enigma));
	
	for(int j = 0; j < 3; j++){
		puts("rotor");
		for (int i = 0; i < 26; i++)
			printf("%c<->%c\n",('a'+i),(rotores[j][i]+'a'));	
	}
	puts("reflector");
	for (int i = 0; i < 26; i++)
			printf("%c<->%c\n",('a'+i),(reflector_a[i]+'a'));
	
	return 0;
}*/












