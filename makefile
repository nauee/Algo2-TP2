CFLAGS=-g -std=c99 -Wall -Werror -Wconversion

juego: juego.c tdas/*/*.c gimnasios/gimnasios.c batallas/batallas.c personaje/personaje.c interfaces/interfaces.c
	gcc juego.c tdas/*/*.c gimnasios/gimnasios.c batallas/batallas.c personaje/personaje.c interfaces/interfaces.c $(CFLAGS) -o juego

ejecutar: juego
	clear
	./juego

debug: juego
	clear
	gdb ./juego

probar: juego
	clear
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./juego