CFLAGS=-g -std=c99 -Wall -Werror -Wconversion

main: main.c
	gcc main.c tdas/*/*.c gimnasios/gimnasios.c batallas/batallas.c $(CFLAGS) -o main

ejecutar: main
	clear
	./main

debug: main
	clear
	gdb ./main

