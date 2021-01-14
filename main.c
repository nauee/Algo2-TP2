#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include "gimnasios/gimnasios.h"
#include "personaje/personaje.h"
#include "batallas/batallas.h"

#define AMARILLO "\033[1;33m"
#define NORMAL "\033[0m"

/*
*	Postcondiciones: Devolvera la tecla pulsada por el usuario.
*/
static int getch(void){
	struct termios oldattr, newattr;
	int ch;
	tcgetattr( STDIN_FILENO, &oldattr );
	newattr = oldattr;
	newattr.c_lflag &= (unsigned int) ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
	return ch;
}

void mostrar_gimnasios (heap_t* gimnasios) {
    int tope = (*gimnasios).tope;
    for (int k = 0; k < tope; k++) {
        gimnasio_t gimnasio_actual = *(gimnasio_t*)heap_eliminar_raiz (gimnasios);
        printf("%s\n", gimnasio_actual.nombre);
        for (int i = 0; i < lista_elementos(gimnasio_actual.entrenadores); i++) {
            entrenador_t entrenador_actual = *(entrenador_t*)lista_elemento_en_posicion(gimnasio_actual.entrenadores, (size_t)i);
            printf("\t%s: ", entrenador_actual.nombre);
            for (int j = 0; j < lista_elementos(entrenador_actual.pokemones); j++) {
                pokemon_t pokemon_actual = *(pokemon_t*)lista_elemento_en_posicion(entrenador_actual.pokemones, (size_t)j);
                printf("%s", pokemon_actual.nombre);
                if (j != lista_elementos(entrenador_actual.pokemones) - 1){
                    printf(" - ");
                }
            }
            printf("\n");
        }
    }
    printf("Hay %i gimnasio/s\n", tope);
}

void mostrar_personaje (personaje_t* personaje) {
    printf("Nombre: %s\n", (*personaje).nombre);
    printf("Pokemones para combatir:\n\t");
    for (int i = 0; i < lista_elementos((*personaje).pokemon_para_combatir); i++) {
        pokemon_t aux = *(pokemon_t*)lista_elemento_en_posicion((*personaje).pokemon_para_combatir,(size_t) i);
        printf("%s", aux.nombre);
        if (i != lista_elementos((*personaje).pokemon_para_combatir) - 1){
            printf(" - ");
        }
    }
    printf("\nPokemones obtenidos: \n\t");
    for (int i = 0; i < lista_elementos((*personaje).pokemon_obtenidos); i++) {
        pokemon_t aux = *(pokemon_t*)lista_elemento_en_posicion((*personaje).pokemon_obtenidos,(size_t) i);
        printf("%s", aux.nombre);
        if (i != lista_elementos((*personaje).pokemon_obtenidos) - 1){
            printf(" - ");
        }
        if (i % 6 == 0 && i != 0) {
            printf("\n\t");
        }
    }
    printf("\n");
}

int comparador_gimnasios (void* e1, void* e2) {
    if ((*(gimnasio_t*)e1).dificultad == (*(gimnasio_t*)e2).dificultad) {
        return 0;
    } else if ((*(gimnasio_t*)e1).dificultad > (*(gimnasio_t*)e2).dificultad) {
        return -1;
    } else {
        return 1;
    }
}

void inicializar_juego (heap_t** gimnasios, personaje_t** personaje) {
    (*gimnasios) = heap_crear (comparador_gimnasios);
    cargar_gimnasios("src/GimnasiosKanto.txt", *gimnasios);
    (*personaje) = cargar_personaje ("src/Personaje.txt");
}

void enfrentar_gimnasios (heap_t* gimnasios, personaje_t* personaje) {
    bool perdio = false;
    while (!perdio) {
        
    }
}

void jugar_juego () {
    system("clear");
    heap_t* gimnasios;
    personaje_t* personaje;
    inicializar_juego(&gimnasios, &personaje);
    mostrar_gimnasios(gimnasios);
    mostrar_personaje(personaje);
    enfrentar_gimnasios (gimnasios, personaje);
}

void simular_juego () {

}

void crear_personaje () {

}

void actualizar_menu(int *opcion_actual){
	if(*opcion_actual == -1){
		*opcion_actual = 2;
	}else if(*opcion_actual == 4){
		*opcion_actual = 0;
	}
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣               DEFENDIENDO               ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                   LAS                   ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                 TORRES!                 ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣   Puedes moverte en el menu con W y S   ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	if(*opcion_actual == 0){
		printf(AMARILLO"╠╬╬╬╬╣ -> Jugar                                ╠╬╬╬╬╣\n");
	}else{
		printf(AMARILLO"╠╬╬╬╬╣    Jugar                                ╠╬╬╬╬╣\n");
	}
	if(*opcion_actual == 1){
		printf(AMARILLO"╠╬╬╬╬╣ -> Simular partida                      ╠╬╬╬╬╣\n");
	}else{
		printf(AMARILLO"╠╬╬╬╬╣    Simular partida                      ╠╬╬╬╬╣\n");
	}
	if(*opcion_actual == 2){
		printf(AMARILLO"╠╬╬╬╬╣ -> Crear personaje                      ╠╬╬╬╬╣\n");
	}else{
		printf(AMARILLO"╠╬╬╬╬╣    Crear personaje                      ╠╬╬╬╬╣\n");
	}
    if(*opcion_actual == 3){
		printf(AMARILLO"╠╬╬╬╬╣ -> Salir                                ╠╬╬╬╬╣\n");
	}else{
		printf(AMARILLO"╠╬╬╬╬╣    Salir                                ╠╬╬╬╬╣\n");
	}
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
}

void menu_principal(){
	int opcion_actual = 0;
	int tecla_pulsada;
	bool entro_a_menu = false;
	actualizar_menu(&opcion_actual);
	while(!entro_a_menu){
		tecla_pulsada = getch();
		switch(tecla_pulsada){
			case 'W':
				opcion_actual --;
				actualizar_menu(&opcion_actual);
				break;
			case 'w':
				opcion_actual --;
				actualizar_menu(&opcion_actual);
				break;
			case 'S':
				opcion_actual ++;
				actualizar_menu(&opcion_actual);
				break;
			case 's':
				opcion_actual ++;
				actualizar_menu(&opcion_actual);
				break;
			case '\n':
                entro_a_menu = true;
				break;
		}
	}
    if (opcion_actual == 0) {
        jugar_juego ();
    } else if (opcion_actual == 1) {
        simular_juego ();
    } else if (opcion_actual == 2) {
        crear_personaje ();
    } else if (opcion_actual == 3) {
        return;
    }
}

int main () {
    menu_principal();
    return 0;
}