#include <stdio.h>
#include "enigma.h"
#include <string.h>

void clears();

int main(int argc, char *argv[]){
	
	uint8_t rotores[][26] = {{4, 10, 12, 5, 11, 6, 3, 16, 21, 25, 13, 19, 14, 22, 24, 7, 23, 20, 18, 15, 0, 8, 1, 17, 2, 9},
	{0, 9, 3, 10, 18, 8, 17, 20, 23, 1, 11, 7, 22, 19, 12, 2, 16, 6, 25, 13, 15, 24, 5, 21, 14, 4},
	{1, 3, 5, 7, 9, 11, 2, 15, 17, 19, 23, 21, 25, 13, 24, 4, 8, 22, 6, 0, 10, 12, 20, 18, 16, 14},
	{4, 18, 14, 21, 15, 25, 9, 0, 24, 16, 20, 8, 17, 7, 23, 11, 13, 5, 19, 6, 10, 3, 2, 12, 22, 1},
	{21, 25, 1, 17, 6, 8, 19, 24, 20, 15, 18, 3, 13, 7, 11, 23, 0, 22, 12, 9, 16, 14, 5, 4, 2, 10},
	{9, 15, 6, 21, 14, 20, 12, 5, 24, 16, 1, 4, 13, 7, 25, 17, 3, 10, 0, 18, 23, 11, 8, 2, 19, 22},
	{13, 25, 9, 7, 6, 17, 2, 23, 12, 24, 18, 22, 1, 14, 20, 5, 0, 8, 21, 11, 15, 4, 10, 16, 3, 19},
	{5, 10, 16, 7, 19, 11, 23, 14, 2, 1, 9, 18, 15, 3, 25, 17, 0, 12, 4, 22, 13, 8, 20, 24, 6, 21},
	};
	uint8_t reflector_a[] = {4, 9, 12, 25, 0, 11, 24, 23, 21, 1, 22, 5, 2, 17, 16, 20, 14, 13, 19, 18, 15, 8, 10, 7, 6, 3};
	//uint8_t reflector_b[] = {24, 17, 20, 7, 16, 18, 11, 3, 15, 23, 13, 6, 14, 10, 12, 8, 4, 1, 5, 25, 2, 22, 21, 9, 0, 19};
	//uint8_t reflector_c[] = {5, 21, 15, 9, 8, 0, 14, 24, 4, 3, 17, 25, 23, 22, 6, 2, 19, 10, 20, 16, 18, 1, 13, 12, 7, 11};
	if (argc == 2){
		if (!strcmp(argv[1], "-help")){
			printf("Uso:\n\t%s 'entrada' 'salida'\nModos:\n\t1(codificar)\n\t2(decodificar)\n", argv[0]);
			return 0;
		}
	}
	if (argc != 3){
		fprintf(stderr, "Uso incorrecto, para ayuda correr con -help\n");
		return 1;
	}
	FILE *entrada = fopen(argv[1], "r");
	if (entrada == NULL){
		fprintf(stderr, "No se pudo abrir el archivo de entrada %s", argv[1]);
		return 1;
	}
	FILE *salida = fopen(argv[2], "w");
	if (entrada == NULL){
		fprintf(stderr, "No se pudo abrir el archivo de salida %s", argv[2]);
		fclose(entrada);
		return 1;
	}
	printf("Modo:");	
	char c = getchar();
	clears();
	if (c != 'c' && c != 'd'){
		fprintf(stderr, "Modo incorrecto, para ayuda correr con -help\n");
		fclose(entrada);
		fclose(salida);
		return 1;
	}
	printf("Posicion rotor 1:");
	char r1 = getchar();
	clears();
	printf("Posicion rotor 2:");
	char r2 = getchar();
	clears();
	printf("Posicion rotor 3:");
	char r3 = getchar();
	clears();
	enigma_t *enigma = crear_enigma(rotores, reflector_a);
	if ('a'>r1||r1>'z'||'a'>r2||r1>'z'||'a'>r3||r1>'z'){
		fprintf(stderr, "Posiciones incorrectas, solo son validos valores entre 'a' y 'z'\n");
		fclose(entrada);
		fclose(salida);
		return 1;
	}
	set_posiciones_iniciales((r1 - 'a'),(r2 - 'a'),(r3 - 'a'), enigma);
	
	if(c == 'c'){
		char entradat[1000];
		char salidat[1000];
		while (fgets(entradat, 1000, entrada) != NULL){
			codificar_linea(entradat,salidat,enigma);
			fprintf(salida, "%s", salidat);
		}
		return 0;
	}
	if(c == 100){
		char entradat[1000];
		char salidat[1000];
		while (fgets(entradat, 1000, entrada) != NULL){
			decodificar_linea(entradat,salidat,enigma);
			fprintf(salida, "%s", salidat);
		}
		return 0;
	}
	destruir_enigma(enigma);
	fclose(entrada);
	fclose(salida);
	return 0;
}

void clears(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
