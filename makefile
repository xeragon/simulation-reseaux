all: main

equipement.o: equipement.h equipement.c
	gcc -c -Wall equipement.c

reseau.o: reseau.h reseau.c
	gcc -c -Wall reseau.c

switch.o: switch.h switch.c
	gcc -c -Wall switch.c

station.o: station.h station.c
	gcc -c -Wall station.c

liaison.o: liaison.h liaison.c
	gcc -c -Wall liaison.c

types.o: types.h types.c
	gcc -c -Wall types.c

trame.o: trame.h trame.c
	gcc -c -Wall trame.c

main: equipement.o trame.o types.o reseau.o switch.o station.o liaison.o main.c
	gcc -Wall -o main *.o main.c

clean:
	rm -f *.o main