CFLAGS=-Wall -std=c99 -pedantic -g

all: enigma

enigma: main.o codificador.o enigma.o
	gcc main.o codificador.o enigma.o -o enigma

main.o: main.c enigma.h
	gcc $(CFLAGS) -c main.c

enigma.o: enigma.c enigma.h
	gcc $(CFLAGS) -c enigma.c

codificador.o: codificador.c codificador.h
	gcc $(CFLAGS) -c codificador.c

clean: 
	rm -vf *.o enigma
