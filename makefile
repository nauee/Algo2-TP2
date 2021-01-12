CFLAGS=-g -std=c99 -Wall -Werror -Wconversion

main: heap/heap.c main.c
	gcc main.c tdas/*/*.c $(CFLAGS) -o main

ejecutar: main
	clear
	./main

debug: main
	clear
	gdb ./main