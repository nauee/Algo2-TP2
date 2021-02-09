#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "gimnasios/gimnasios.h"
#include "personaje/personaje.h"
#include "batallas/batallas.h"

#define AMARILLO "\033[1;33m"
#define PELEANDO 0
#define GANO 1
#define PERDIO -1
#define MAX_FUNCIONES 5
#define NORMAL "\033[0m \033[39m"
#define FONDO_BLANCO "\033[107m"
#define NEGRO "\033[30m"
#define AZUL "\033[34m"
#define CELESTE "\033[36m"

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
        gimnasio_t gimnasio_actual = *(gimnasio_t*)(*gimnasios).elementos[k];
        printf("%s\n", gimnasio_actual.nombre);
        for (int i = 0; i < lista_elementos(gimnasio_actual.entrenadores); i++) {
            entrenador_t entrenador_actual = *(entrenador_t*)lista_elemento_en_posicion(gimnasio_actual.entrenadores, (size_t)i);
            printf("\t%s: ", entrenador_actual.nombre);
            for (int j = 0; j < (entrenador_actual.cant_pokemon); j++) {
                pokemon_t pokemon_actual = *(entrenador_actual.pokemon[j]);
                printf("%s", pokemon_actual.nombre);
                if (j != entrenador_actual.cant_pokemon - 1){
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
    for (int i = 0; i < (*personaje).cant_pokemon_para_combatir; i++) {
        pokemon_t aux = *((*personaje).pokemon_para_combatir [i]);
        printf("%s", aux.nombre);
        if (i != (*personaje).cant_pokemon_para_combatir - 1){
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

void asignar_funciones_batalla (int (*funciones_batalla[MAX_FUNCIONES]) (void*, void*)) {
	funciones_batalla [0] = funcion_batalla_1;
	funciones_batalla [1] = funcion_batalla_2;
	funciones_batalla [2] = funcion_batalla_3;
	funciones_batalla [3] = funcion_batalla_4;
	funciones_batalla [4] = funcion_batalla_5;
}

void mostrar_string_centrado (char* string, size_t ancho_max) {
	size_t ancho_laterales = (ancho_max - strlen(string)) / 2;
	for (int i = 0; i < ancho_laterales; i++) {
		printf (" ");
	}
	printf("%s", string);
	for (int i = 0; i < ancho_laterales; i++) {
		printf (" ");
	}
	if ( strlen(string) % 2 == 0) printf(" ");
}

void mostrar_batalla (pokemon_t pkm_1, pokemon_t pkm2) {
	printf ("                          ___      ___ ________                               \n");
	printf ("                         |\\  \\    /  /|\\   ____\\                              \n");
	printf ("                         \\ \\  \\  /  / | \\  \\___|_                             \n");
	mostrar_string_centrado (pkm_1.nombre, 25);
	printf (" \\ \\  \\/  / / \\ \\_____  \\   ");
	mostrar_string_centrado (pkm2.nombre, 25);
	printf ("\n                           \\ \\    / /   \\|____|\\  \\                           \n");
	printf ("                            \\ \\__/ /      ____\\_\\  \\                          \n");
	printf ("                             \\|__|/      |\\_________\\                         \n");
	printf ("                                         \\|_________|                         \n");

}

void aumentar_stats (pokemon_t* pokemon) {
	if ((*pokemon).velocidad < 63) ((*pokemon).velocidad) ++;
	if ((*pokemon).ataque < 63) ((*pokemon).ataque) ++;
	if ((*pokemon).defensa < 63) ((*pokemon).defensa) ++;
}

bool enfrentar_entrenador (entrenador_t* entrenador, personaje_t* personaje, int id_funcion_batalla) {
	int estado_batalla = PELEANDO;
	int n_pokemon_entrenador = 0;
	int n_pokemon_personaje = 0;
	int (*funciones_batalla[MAX_FUNCIONES]) (void*, void*);
	asignar_funciones_batalla (funciones_batalla);
	while (estado_batalla == PELEANDO) {

		mostrar_batalla (*(*personaje).pokemon_para_combatir[n_pokemon_personaje], *(*entrenador).pokemon[n_pokemon_entrenador]);

		if (funciones_batalla [id_funcion_batalla - 1] ((*personaje).pokemon_para_combatir[n_pokemon_personaje], (*entrenador).pokemon[n_pokemon_entrenador]) == GANO_PRIMERO) {
			printf("Gana el %s de %s contra el %s de %s\n", (*(*personaje).pokemon_para_combatir[n_pokemon_personaje]).nombre, (*personaje).nombre, (*(*entrenador).pokemon[n_pokemon_entrenador]).nombre, (*entrenador).nombre);
			n_pokemon_entrenador ++;
			aumentar_stats ((*personaje).pokemon_para_combatir[n_pokemon_personaje]);
		} else {
			printf("Gana el %s de %s contra el %s de %s\n", (*(*entrenador).pokemon[n_pokemon_entrenador]).nombre, (*entrenador).nombre, (*(*personaje).pokemon_para_combatir[n_pokemon_personaje]).nombre, (*personaje).nombre);
			n_pokemon_personaje ++;
		}

		getchar();
		system("clear");

		if (n_pokemon_entrenador == (*entrenador).cant_pokemon) {
			estado_batalla = GANO;
			printf ("Gana %s contra %s", (*personaje).nombre, (*entrenador).nombre);
		} else if (n_pokemon_personaje == (*personaje).cant_pokemon_para_combatir) {
			estado_batalla = PERDIO;
			printf ("Gana %s contra %s", (*entrenador).nombre, (*personaje).nombre);
		}

	}
	return (estado_batalla == GANO);
}

void actualizar_menu_elegir_pokemon_lider (int *opcion_actual, entrenador_t* lider) {
	if(*opcion_actual == -1){
		*opcion_actual = (*lider).cant_pokemon - 1;
	}else if(*opcion_actual == (*lider).cant_pokemon){
		*opcion_actual = 0;
	}
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	for (int i = 0; i < (*lider).cant_pokemon; i++) {
		if (*opcion_actual == i) {
			printf(AMARILLO"╠╬╬╬╬╣ -> %-37s╠╬╬╬╬╣\n",(*(*lider).pokemon[i]).nombre);
		} else {
			printf(AMARILLO"╠╬╬╬╬╣    %-37s╠╬╬╬╬╣\n",(*(*lider).pokemon[i]).nombre);
		}
	}
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
}

void elegir_pokemon_lider (personaje_t* personaje, entrenador_t* lider) {
	int opcion_actual = 0;
	int tecla_pulsada;
	bool entro_a_menu = false;
	actualizar_menu_elegir_pokemon_lider(&opcion_actual, lider);
	while(!entro_a_menu){
		tecla_pulsada = getch();
		switch(tecla_pulsada){
			case 'W':
				opcion_actual --;
				actualizar_menu_elegir_pokemon_lider(&opcion_actual, lider);
				break;
			case 'w':
				opcion_actual --;
				actualizar_menu_elegir_pokemon_lider(&opcion_actual, lider);
				break;
			case 'S':
				opcion_actual ++;
				actualizar_menu_elegir_pokemon_lider(&opcion_actual, lider);
				break;
			case 's':
				opcion_actual ++;
				actualizar_menu_elegir_pokemon_lider(&opcion_actual, lider);
				break;
			case '\n':
                entro_a_menu = true;
				break;
		}
	}
	lista_insertar ((*personaje).pokemon_obtenidos, (*lider).pokemon[opcion_actual]);
	mostrar_personaje (personaje);
}

void actualizar_menu_victoria(int *opcion_actual){
	if(*opcion_actual == -1){
		*opcion_actual = 2;
	}else if(*opcion_actual == 3){
		*opcion_actual = 0;
	}
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	if(*opcion_actual == 0){
		printf(AMARILLO"╠╬╬╬╬╣ -> Elegir un pokemon del lider          ╠╬╬╬╬╣\n");
	}else{
		printf(AMARILLO"╠╬╬╬╬╣    Elegir un pokemon del lider          ╠╬╬╬╬╣\n");
	}
	if(*opcion_actual == 1){
		printf(AMARILLO"╠╬╬╬╬╣ -> Rearmar equipo                       ╠╬╬╬╬╣\n");
	}else{
		printf(AMARILLO"╠╬╬╬╬╣    Rearmar equipo                       ╠╬╬╬╬╣\n");
	}
	if(*opcion_actual == 2){
		printf(AMARILLO"╠╬╬╬╬╣ -> Continuar                            ╠╬╬╬╬╣\n");
	}else{
		printf(AMARILLO"╠╬╬╬╬╣    Continuar                            ╠╬╬╬╬╣\n");
	}
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
}

void actualizar_menu_rearmar_equipo (int *opcion_actual, personaje_t* personaje) {
	if(*opcion_actual == -1){
		*opcion_actual = (int) lista_elementos((*personaje).pokemon_obtenidos) - 1;
	}else if(*opcion_actual == lista_elementos((*personaje).pokemon_obtenidos)){
		*opcion_actual = 0;
	}
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    Pokemones para combatir:             ╠╬╬╬╬╣\n");
	for (int i = 0; i < (*personaje).cant_pokemon_para_combatir; i++) {
		printf(AMARILLO"╠╬╬╬╬╣    %-37s╠╬╬╬╬╣\n",(*(*personaje).pokemon_para_combatir[i]).nombre);
	}
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
	printf("\n");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	for (int i = 0; i < lista_elementos ((*personaje).pokemon_obtenidos); i++) {
		if (*opcion_actual == i) {
			printf(AMARILLO"╠╬╬╬╬╣ -> %-37s╠╬╬╬╬╣\n",(*((pokemon_t*)lista_elemento_en_posicion((*personaje).pokemon_obtenidos, (size_t)i))).nombre);
		} else {
			printf(AMARILLO"╠╬╬╬╬╣    %-37s╠╬╬╬╬╣\n",(*((pokemon_t*)lista_elemento_en_posicion((*personaje).pokemon_obtenidos, (size_t)i))).nombre);
		}
	}
	printf(AMARILLO"╠╬╬╬╬╣    Pulsa espacio para continuar         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);


}

void actualizar_menu_rearmar_equipo_party (int *opcion_actual, personaje_t* personaje) {
	
	if(*opcion_actual == -1){
		*opcion_actual = (*personaje).cant_pokemon_para_combatir - 1;
	}else if(*opcion_actual == (*personaje).cant_pokemon_para_combatir){
		*opcion_actual = 0;
	}
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    Pokemones para combatir:             ╠╬╬╬╬╣\n");
	for (int i = 0; i < (*personaje).cant_pokemon_para_combatir; i++) {
		if (*opcion_actual == i) {
			printf(AMARILLO"╠╬╬╬╬╣ -> %-37s╠╬╬╬╬╣\n",(*(*personaje).pokemon_para_combatir[i]).nombre);
		} else {
			printf(AMARILLO"╠╬╬╬╬╣    %-37s╠╬╬╬╬╣\n",(*(*personaje).pokemon_para_combatir[i]).nombre);
		}
	}
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
	printf("\n");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	for (int i = 0; i < lista_elementos ((*personaje).pokemon_obtenidos); i++) {
		printf(AMARILLO"╠╬╬╬╬╣    %-37s╠╬╬╬╬╣\n",(*((pokemon_t*)lista_elemento_en_posicion((*personaje).pokemon_obtenidos, (size_t)i))).nombre);
	}
	printf(AMARILLO"╠╬╬╬╬╣    Pulsa espacio para continuar         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);


}

bool es_pokemon_para_combatir (pokemon_t* pokemon_para_combatir [MAX_POKEMONES_COMBATE], int cant_pokemon, pokemon_t* pokemon) {
	bool pokemones_repetidos = false;
	for (int i = 0; i < cant_pokemon; i++) {
		if (pokemon_para_combatir[i] == pokemon) {
			pokemones_repetidos = true;
		}
	}
	return pokemones_repetidos;
}

void rearmar_equipo (personaje_t* personaje) {
	int opcion_actual = 0;
	int tecla_pulsada;
	bool entro_a_menu = false;
	int pos_pkm_pc = -1;
	actualizar_menu_rearmar_equipo(&opcion_actual, personaje);
	while(!entro_a_menu){
		tecla_pulsada = getch();
		switch(tecla_pulsada){
			case 'W':
				opcion_actual --;
				if (pos_pkm_pc == -1) actualizar_menu_rearmar_equipo(&opcion_actual, personaje);
				else actualizar_menu_rearmar_equipo_party (&opcion_actual, personaje);
				break;
			case 'w':
				opcion_actual --;
				if (pos_pkm_pc == -1) actualizar_menu_rearmar_equipo(&opcion_actual, personaje);
				else actualizar_menu_rearmar_equipo_party (&opcion_actual, personaje);
				break;
			case 'S':
				opcion_actual ++;
				if (pos_pkm_pc == -1) actualizar_menu_rearmar_equipo(&opcion_actual, personaje);
				else actualizar_menu_rearmar_equipo_party (&opcion_actual, personaje);
				break;
			case 's':
				opcion_actual ++;
				if (pos_pkm_pc == -1) actualizar_menu_rearmar_equipo(&opcion_actual, personaje);
				else actualizar_menu_rearmar_equipo_party (&opcion_actual, personaje);
				break;
			case '\n':

				if (pos_pkm_pc == -1) {
					if (!es_pokemon_para_combatir ((*personaje).pokemon_para_combatir, (*personaje).cant_pokemon_para_combatir, (pokemon_t*) lista_elemento_en_posicion ((*personaje).pokemon_obtenidos, (size_t) opcion_actual))){
						pos_pkm_pc = opcion_actual;
						opcion_actual = 0;
						actualizar_menu_rearmar_equipo_party (&opcion_actual, personaje);
					} else {
						printf (" Ese pokemon ya se encuentra para combatir ");
					}
				} else {
					(*personaje).pokemon_para_combatir[opcion_actual] = (pokemon_t*) lista_elemento_en_posicion ((*personaje).pokemon_obtenidos, (size_t) pos_pkm_pc);
					pos_pkm_pc = -1;
					actualizar_menu_rearmar_equipo (&opcion_actual, personaje);
				}
				break;
			case ' ':
				entro_a_menu = true;
				break;
		}
	}
}

void ganar_gimnasio (personaje_t* personaje, entrenador_t* lider) {
	printf ("%s ha ganado a %s", (*personaje).nombre, (*lider).nombre);
	int opcion_actual = 0;
	int tecla_pulsada;
	bool entro_a_menu = false;
	actualizar_menu_victoria(&opcion_actual);
	while(!entro_a_menu){
		tecla_pulsada = getch();
		switch(tecla_pulsada){
			case 'W':
				opcion_actual --;
				actualizar_menu_victoria(&opcion_actual);
				break;
			case 'w':
				opcion_actual --;
				actualizar_menu_victoria(&opcion_actual);
				break;
			case 'S':
				opcion_actual ++;
				actualizar_menu_victoria(&opcion_actual);
				break;
			case 's':
				opcion_actual ++;
				actualizar_menu_victoria(&opcion_actual);
				break;
			case '\n':
                entro_a_menu = true;
				break;
		}
	}
    if (opcion_actual == 0) {
        elegir_pokemon_lider (personaje, lider);
		rearmar_equipo (personaje);
    } else if (opcion_actual == 1) {
        rearmar_equipo (personaje);
    } else if (opcion_actual == 2) {
		return;
	}
}

void perder_gimnasio (personaje_t* personaje, entrenador_t* lider) {
	printf ("%s ha perdido con %s", (*personaje).nombre, (*lider).nombre);
}

bool enfrentar_gimnasio (gimnasio_t* gimnasio, personaje_t* personaje) {
	int estado_batalla = PELEANDO;
	lista_t* entrenadores_vencidos = lista_crear ();
	entrenador_t* proximo_entrenador = (entrenador_t*) lista_tope ((*gimnasio).entrenadores);
	if (!enfrentar_entrenador (proximo_entrenador, personaje, (*gimnasio).id_funcion_batalla)){
		estado_batalla = PERDIO;
	}
	getchar();
	while (estado_batalla == PELEANDO) {
		lista_apilar (entrenadores_vencidos, proximo_entrenador);
		lista_desapilar ((*gimnasio).entrenadores);
		proximo_entrenador = (entrenador_t*) lista_tope ((*gimnasio).entrenadores);
		if (!proximo_entrenador) {
			estado_batalla = GANO;
		}
		if (proximo_entrenador) {
			if (!enfrentar_entrenador (proximo_entrenador, personaje, (*gimnasio).id_funcion_batalla)){
				estado_batalla = PERDIO;
			}
		}
		getchar();
	}

	if (estado_batalla == GANO) {
		ganar_gimnasio (personaje, lista_tope (entrenadores_vencidos));
	} else {
		perder_gimnasio (personaje, lista_tope (entrenadores_vencidos));
	}

	return (estado_batalla == GANO);
}

void enfrentar_gimnasios (heap_t* gimnasios, personaje_t* personaje) {
	int estado_batalla = PELEANDO;
	gimnasio_t* proximo_gimnasio = (gimnasio_t*) heap_ver_raiz (gimnasios);
	if (proximo_gimnasio) {
		printf("===== %s =====\n", (*proximo_gimnasio).nombre);
		if (!enfrentar_gimnasio (proximo_gimnasio, personaje)) {
			estado_batalla = PERDIO;
		}
	}
	getchar ();
    while (estado_batalla == PELEANDO) {
		heap_eliminar_raiz (gimnasios);
		proximo_gimnasio = (gimnasio_t*) heap_ver_raiz (gimnasios);
		if (!proximo_gimnasio) {
			estado_batalla = GANO;
		}
		if (proximo_gimnasio) {
			printf("===== %s =====\n", (*proximo_gimnasio).nombre);
			if (!enfrentar_gimnasio (proximo_gimnasio, personaje)) {
				estado_batalla = PERDIO;
			}
		}

		getchar ();
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
		*opcion_actual = 3;
	}else if(*opcion_actual == 4){
		*opcion_actual = 0;
	}
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                 BATALLA                 ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                 POKEMON                 ╠╬╬╬╬╣\n");
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
    //menu_principal();
	jugar_juego ();
    return 0;
}