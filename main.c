#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "gimnasios/gimnasios.h"
#include "personaje/personaje.h"
#include "batallas/batallas.h"

#define GANO 1
#define PELEANDO 0
#define PERDIO -1
#define REINTENTAR -2
#define MAX_FUNCIONES 5
#define AMARILLO "\033[1;33m"
#define NORMAL "\033[0m \033[39m"
#define MAX_LINEA 66
#define MAX_LINEA_MENU 100
#define MAX_RUTA 100

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

void limpiar_buffer (){
	char c;
	while ((c = (char) getchar()) != '\n' && c != EOF);
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

void mostrar_personaje (personaje_t personaje) {
    printf("Nombre: %s\n", personaje.nombre);
    printf("Pokemones para combatir:\n\t");
    for (int i = 0; i < personaje.cant_pokemon_para_combatir; i++) {
        pokemon_t aux = *(personaje.pokemon_para_combatir [i]);
        printf("%s", aux.nombre);
        if (i != personaje.cant_pokemon_para_combatir - 1){
            printf(" - ");
        }
    }
    printf("\nPokemones obtenidos: \n\t");
    for (int i = 0; i < lista_elementos(personaje.pokemon_obtenidos); i++) {
        pokemon_t aux = *(pokemon_t*)lista_elemento_en_posicion(personaje.pokemon_obtenidos,(size_t) i);
        printf("%s", aux.nombre);
        if (i != lista_elementos(personaje.pokemon_obtenidos) - 1){
            printf(" - ");
        }
        if (i % 6 == 0 && i != 0) {
            printf("\n\t");
        }
    }
	printf ("\nPresiona ENTER para volver al menu");
	getchar ();
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

void asignar_funciones_batalla (int (*funciones_batalla[MAX_FUNCIONES]) (void*, void*)) {
	funciones_batalla [0] = funcion_batalla_1;
	funciones_batalla [1] = funcion_batalla_2;
	funciones_batalla [2] = funcion_batalla_3;
	funciones_batalla [3] = funcion_batalla_4;
	funciones_batalla [4] = funcion_batalla_5;
}

void mostrar_string_centrado (char* string, size_t ancho_max) {
	size_t ancho_laterales = (ancho_max - strlen(string)) / 2;
	if ((ancho_max - strlen(string)) % 2 == 1) {
		printf(" ");
	}
	for (int i = 0; i < ancho_laterales; i++) {
		printf (" ");
	}
	printf("%s", string);
	for (int i = 0; i < ancho_laterales; i++) {
		printf (" ");
	}
}

void mostrar_batalla (pokemon_t pkm_1, pokemon_t pkm2) {
	system("clear");
	printf (AMARILLO"\n                          ___      ___ ________                               \n");
	printf (AMARILLO"                         |\\  \\    /  /|\\   ____\\                              \n");
	printf (AMARILLO"                         \\ \\  \\  /  / | \\  \\___|_                             \n");
	mostrar_string_centrado (pkm_1.nombre, 25);
	printf (AMARILLO" \\ \\  \\/  / / \\ \\_____  \\   ");
	mostrar_string_centrado (pkm2.nombre, 25);
	printf (AMARILLO"\n                           \\ \\    / /   \\|____|\\  \\                           \n");
	printf (AMARILLO"                            \\ \\__/ /      ____\\_\\  \\                          \n");
	printf (AMARILLO"                             \\|__|/      |\\_________\\                         \n");
	printf (AMARILLO"                                         \\|_________|                         \n"NORMAL);
	sleep (1);
}

void aumentar_stats (pokemon_t* pokemon) {
	if ((*pokemon).puntos_de_mejora > 0) {
		((*pokemon).velocidad) ++;
		((*pokemon).ataque) ++;
		((*pokemon).defensa) ++;
		((*pokemon).puntos_de_mejora) --;
	}
}

void mostrar_pokemon_ganador (char* pkm_ganador, char* pj_ganador, char* pkm_perdedor, char* pj_perdedor) {
	char linea [MAX_LINEA];
	strcpy (linea, "Gana el ");
	strcat (linea, pkm_ganador);
	strcat (linea, " de ");
	strcat (linea, pj_ganador);
	strcat (linea, " contra el ");
	strcat (linea, pkm_perdedor);
	strcat (linea, " de ");
	strcat (linea, pj_perdedor);
	
	printf(AMARILLO"\n╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣");
	mostrar_string_centrado (linea, MAX_LINEA);
	printf(AMARILLO"╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);

}

void mostrar_entrenador_ganador (char* ganador, char* perdedor) {
	char linea [MAX_LINEA] = "";
	strcat (linea, ganador);
	strcat (linea, " ha vencido a ");
	strcat (linea, perdedor);
	printf(AMARILLO"\n╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣");
	mostrar_string_centrado (linea, MAX_LINEA);
	printf(AMARILLO"╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
}

bool enfrentar_entrenador (entrenador_t* entrenador, personaje_t* personaje, int id_funcion_batalla, bool es_simulacion) {
	int estado_batalla = PELEANDO;
	int n_pokemon_entrenador = 0;
	int n_pokemon_personaje = 0;
	int (*funciones_batalla[MAX_FUNCIONES]) (void*, void*);
	asignar_funciones_batalla (funciones_batalla);
	while (estado_batalla == PELEANDO) {

		mostrar_batalla (*(*personaje).pokemon_para_combatir[n_pokemon_personaje], *(*entrenador).pokemon[n_pokemon_entrenador]);

		if (funciones_batalla [id_funcion_batalla - 1] ((*personaje).pokemon_para_combatir[n_pokemon_personaje], (*entrenador).pokemon[n_pokemon_entrenador]) == GANO_PRIMERO) {
			mostrar_pokemon_ganador ((*(*personaje).pokemon_para_combatir[n_pokemon_personaje]).nombre, (*personaje).nombre, (*(*entrenador).pokemon[n_pokemon_entrenador]).nombre, (*entrenador).nombre);
			n_pokemon_entrenador ++;
			aumentar_stats ((*personaje).pokemon_para_combatir[n_pokemon_personaje]);
		} else {
			mostrar_pokemon_ganador ((*(*entrenador).pokemon[n_pokemon_entrenador]).nombre, (*entrenador).nombre, (*(*personaje).pokemon_para_combatir[n_pokemon_personaje]).nombre, (*personaje).nombre);
			n_pokemon_personaje ++;
		}

		if (!es_simulacion) {
			printf(" Presiona ENTER para continuar ");
			getchar ();
		} else {
			sleep (2);
		}
		system ("clear");

		if (n_pokemon_entrenador == (*entrenador).cant_pokemon) {
			estado_batalla = GANO;
			mostrar_entrenador_ganador ((*personaje).nombre, (*entrenador).nombre);
			if (!es_simulacion) {
				printf(" Presiona ENTER para continuar ");
				getchar ();
				// OTRO MENU
			} else {
				sleep (2);
			}
			system ("clear");
		} else if (n_pokemon_personaje == (*personaje).cant_pokemon_para_combatir) {
			estado_batalla = PERDIO;
			mostrar_entrenador_ganador((*entrenador).nombre, (*personaje).nombre);
			if (!es_simulacion) {
				printf(" Presiona ENTER para continuar ");
				getchar ();
				// OTRO MENU
			} else {
				sleep (2);
			}
			system ("clear");
		}

	}
	return (estado_batalla == GANO);
}

void mostrar_menu_elegir_pokemon_lider (entrenador_t lider) {
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	for (int i = 0; i < lider.cant_pokemon; i++) {
		printf(AMARILLO"╠╬╬╬╬╣    %03i: %-32s╠╬╬╬╬╣\n", i, (*lider.pokemon[i]).nombre);
	}
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n");
	printf("                          ");
}

void elegir_pokemon_lider (personaje_t* personaje, entrenador_t lider) {
	int opcion_seleccionada = 0;
	mostrar_menu_elegir_pokemon_lider(lider);
	scanf (" %i", &opcion_seleccionada);
	while (opcion_seleccionada < 0 || opcion_seleccionada >= lider.cant_pokemon) {
		mostrar_string_centrado ("Esa opcion no es valida", 53);
		printf("\n                          ");
		scanf (" %i", &opcion_seleccionada);
	}
	
	lista_insertar ((*personaje).pokemon_obtenidos, lider.pokemon[opcion_seleccionada]);
}

void mostrar_menu_victoria(bool tomo_pokemon_lider){

	printf(AMARILLO"\n╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                Ingresa la opcion que quieras elegir                                ╠╬╬╬╬╣\n");
	if (!tomo_pokemon_lider)
		printf(AMARILLO"╠╬╬╬╬╣    T: Elegir un pokemon del lider                                                                  ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    C: Rearmar equipo                                                                               ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    N: Continuar                                                                                    ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n");
	printf("                                                  ");
}

void mostrar_menu_derrota () {
	
	printf(AMARILLO"\n╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                Ingresa la opcion que quieras elegir                                ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    C: Rearmar equipo                                                                               ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    R: Reintentar gimnasio                                                                          ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    F: Finalizar partida                                                                            ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
}

void mostrar_menu_rearmar_equipo (int *opcion_actual, personaje_t* personaje) {
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

void mostrar_menu_rearmar_equipo_party (int *opcion_actual, personaje_t* personaje) {
	
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
	mostrar_menu_rearmar_equipo(&opcion_actual, personaje);
	while(!entro_a_menu){
		tecla_pulsada = getch();
		switch(tecla_pulsada){
			case 'W':
				opcion_actual --;
				if (pos_pkm_pc == -1) mostrar_menu_rearmar_equipo(&opcion_actual, personaje);
				else mostrar_menu_rearmar_equipo_party (&opcion_actual, personaje);
				break;
			case 'w':
				opcion_actual --;
				if (pos_pkm_pc == -1) mostrar_menu_rearmar_equipo(&opcion_actual, personaje);
				else mostrar_menu_rearmar_equipo_party (&opcion_actual, personaje);
				break;
			case 'S':
				opcion_actual ++;
				if (pos_pkm_pc == -1) mostrar_menu_rearmar_equipo(&opcion_actual, personaje);
				else mostrar_menu_rearmar_equipo_party (&opcion_actual, personaje);
				break;
			case 's':
				opcion_actual ++;
				if (pos_pkm_pc == -1) mostrar_menu_rearmar_equipo(&opcion_actual, personaje);
				else mostrar_menu_rearmar_equipo_party (&opcion_actual, personaje);
				break;
			case '\n':

				if (pos_pkm_pc == -1) {
					if (!es_pokemon_para_combatir ((*personaje).pokemon_para_combatir, (*personaje).cant_pokemon_para_combatir, (pokemon_t*) lista_elemento_en_posicion ((*personaje).pokemon_obtenidos, (size_t) opcion_actual))){
						pos_pkm_pc = opcion_actual;
						opcion_actual = 0;
						mostrar_menu_rearmar_equipo_party (&opcion_actual, personaje);
					} else {
						printf (" Ese pokemon ya se encuentra para combatir \n");
					}
				} else {
					(*personaje).pokemon_para_combatir[opcion_actual] = (pokemon_t*) lista_elemento_en_posicion ((*personaje).pokemon_obtenidos, (size_t) pos_pkm_pc);
					pos_pkm_pc = -1;
					mostrar_menu_rearmar_equipo (&opcion_actual, personaje);
				}
				break;
			case ' ':
				entro_a_menu = true;
				break;
		}
	}
}

void mostrar_victoria (char* nombre_personaje, char* nombre_gimnasio) {
	char linea [MAX_LINEA_MENU] = "";
	strcat (linea, nombre_personaje);
	strcat (linea, " ha ganado en ");
	strcat (linea, nombre_gimnasio);
	system("clear");
	printf(AMARILLO"\n╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣");
	mostrar_string_centrado (linea, MAX_LINEA_MENU);
	printf("╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
}

void mostrar_derrota (char* nombre_personaje, char* nombre_gimnasio) {
	char linea [MAX_LINEA_MENU] = "";
	strcat (linea, nombre_personaje);
	strcat (linea, " ha perdido en ");
	strcat (linea, nombre_gimnasio);
	system("clear");
	printf(AMARILLO"\n╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣");
	mostrar_string_centrado (linea, MAX_LINEA_MENU);
	printf("╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
}

void ganar_gimnasio (personaje_t* personaje, entrenador_t lider, char* nombre_gimnasio, bool es_simulacion, bool tomo_pokemon_lider) {
	if (es_simulacion) {
		mostrar_victoria((*personaje).nombre, nombre_gimnasio);
		return;
	}
	char opcion_seleccionada = ' ';
	mostrar_victoria((*personaje).nombre, nombre_gimnasio);
	mostrar_menu_victoria(tomo_pokemon_lider);
	scanf (" %c", &opcion_seleccionada);
	while (opcion_seleccionada != 'T' && opcion_seleccionada != 'C' && opcion_seleccionada != 'N') {
		mostrar_string_centrado ("Esa opcion no es valida", 112);
		printf("\n                                                  ");
		scanf (" %c", &opcion_seleccionada);
	}
	limpiar_buffer ();
    if (opcion_seleccionada == 'T') {
        elegir_pokemon_lider (personaje, lider);
		ganar_gimnasio (personaje, lider, nombre_gimnasio, es_simulacion, true);
    } else if (opcion_seleccionada == 'C') {
        rearmar_equipo (personaje);
    } else if (opcion_seleccionada == 'N') {
		return;
	}
}

int perder_gimnasio (personaje_t* personaje, char* nombre_gimnasio, bool es_simulacion) {
	if (es_simulacion) {
		mostrar_derrota ((*personaje).nombre, nombre_gimnasio);
		return PERDIO;
	}
	char opcion_seleccionada = ' ';
	mostrar_derrota ((*personaje).nombre, nombre_gimnasio);
	mostrar_menu_derrota();
	scanf (" %c", &opcion_seleccionada);
	while (opcion_seleccionada != 'C' && opcion_seleccionada != 'R' && opcion_seleccionada != 'F') {
		mostrar_string_centrado ("Esa opcion no es valida", 112);
		printf("\n                                                  ");
		scanf (" %c", &opcion_seleccionada);
	}
	limpiar_buffer();
    if (opcion_seleccionada == 'C') {
		rearmar_equipo (personaje);
		return perder_gimnasio (personaje, nombre_gimnasio, es_simulacion);
    } else if (opcion_seleccionada == 'R'){
		return REINTENTAR;
	} else {
        return PERDIO;
    }
}

void reestablecer_gimnasio (lista_t* entrenadores, lista_t* entrenadores_vencidos) {
	size_t tope = lista_elementos (entrenadores_vencidos);
	for (int i = 0; i < tope; i++){
		lista_apilar (entrenadores, lista_tope (entrenadores_vencidos));
		lista_desapilar (entrenadores_vencidos);
	}
	lista_destruir (entrenadores_vencidos);
}

void mostrar_gimnasio (gimnasio_t gimnasio, lista_t* entrenadores_vencidos) {
	printf ("Nombre: %s\n", gimnasio.nombre);
	printf ("\t Entrenadores restantes: \n");
	for (int i = 0; i < lista_elementos (gimnasio.entrenadores); i++) {
		entrenador_t entrenador = * (entrenador_t*) lista_elemento_en_posicion (gimnasio.entrenadores, (size_t) i);
		printf("\t\t%s: \n", entrenador.nombre);
        for (int j = 0; j < (entrenador.cant_pokemon); j++) {
            pokemon_t pokemon_actual = *(entrenador.pokemon[j]);
            printf("\t\t\t%s\n", pokemon_actual.nombre);
        }
        printf("\n");
	}
	printf ("\t Entrenadores derrotados: \n");
	for (int i = 0; i < lista_elementos (entrenadores_vencidos); i++) {
		entrenador_t entrenador = * (entrenador_t*) lista_elemento_en_posicion (entrenadores_vencidos, (size_t) i);
		printf("\t\t%s: \n", entrenador.nombre);
        for (int j = 0; j < (entrenador.cant_pokemon); j++) {
            pokemon_t pokemon_actual = *(entrenador.pokemon[j]);
            printf("\t\t\t%s\n", pokemon_actual.nombre);
        }
        printf("\n");
	}
	printf ("Presiona ENTER para volver al menu");
	getchar ();
}

void mostrar_menu_gimnasio (char* nombre_gimnasio) {
	system ("clear");
	printf(AMARILLO"\n╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                                                                                    ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣");
	mostrar_string_centrado (nombre_gimnasio, MAX_LINEA_MENU);
	printf("╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                Ingresa la opcion que quieras elegir                                ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                                                                                    ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    E: Informacion del entrenador                                                                   ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    G: Informacion del gimnasio                                                                     ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    C: Rearmar equipo                                                                               ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    B: Siguiente batalla                                                                            ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n");
	printf("                                                        ");
}

void menu_gimnasio (gimnasio_t gimnasio, lista_t* entrenadores_vencidos, personaje_t* personaje) {
	char opcion_seleccionada = ' ';
	mostrar_menu_gimnasio(gimnasio.nombre);
	scanf (" %c", &opcion_seleccionada);
	while (opcion_seleccionada != 'E' && opcion_seleccionada != 'G' && opcion_seleccionada != 'C' && opcion_seleccionada != 'B') {
		mostrar_string_centrado ("Esa opcion no es valida", 112);
		printf("\n                                                        ");
		scanf (" %c", &opcion_seleccionada);
	}
	limpiar_buffer();
	if (opcion_seleccionada == 'E') {
		mostrar_personaje (*personaje);
		menu_gimnasio (gimnasio, entrenadores_vencidos, personaje);
	} else if (opcion_seleccionada == 'G') {
		mostrar_gimnasio (gimnasio, entrenadores_vencidos);
		menu_gimnasio (gimnasio, entrenadores_vencidos, personaje);
	} else if (opcion_seleccionada == 'C') {
		rearmar_equipo (personaje);
		menu_gimnasio (gimnasio, entrenadores_vencidos, personaje);
	} else if (opcion_seleccionada == 'B'){
		return;
	}
}

int enfrentar_gimnasio (gimnasio_t gimnasio, personaje_t* personaje, bool es_simulacion) {
	int estado_batalla = PELEANDO;
	lista_t* entrenadores_vencidos = lista_crear ();
	entrenador_t* proximo_entrenador = (entrenador_t*) lista_tope (gimnasio.entrenadores);
	if (!enfrentar_entrenador (proximo_entrenador, personaje, gimnasio.id_funcion_batalla, es_simulacion)){
		estado_batalla = PERDIO;
	}
	while (estado_batalla == PELEANDO) {
		lista_apilar (entrenadores_vencidos, proximo_entrenador);
		lista_desapilar (gimnasio.entrenadores);
		proximo_entrenador = (entrenador_t*) lista_tope (gimnasio.entrenadores);
		if (!proximo_entrenador) {
			estado_batalla = GANO;
		}
		if (proximo_entrenador) {
			if (!es_simulacion) {
				menu_gimnasio (gimnasio, entrenadores_vencidos, personaje);
			}
			if (!enfrentar_entrenador (proximo_entrenador, personaje, gimnasio.id_funcion_batalla, es_simulacion)){
				estado_batalla = PERDIO;
			}
		}
	}

	if (estado_batalla == GANO) {
		ganar_gimnasio (personaje, *(entrenador_t*)(lista_tope (entrenadores_vencidos)), gimnasio.nombre, es_simulacion, false);
	} else {
		estado_batalla = perder_gimnasio (personaje, gimnasio.nombre, es_simulacion);
		reestablecer_gimnasio (gimnasio.entrenadores, entrenadores_vencidos);
	}

	return estado_batalla;
}

void presentar_gimnasio (gimnasio_t proximo_gimnasio) {
	system("clear");
	printf(AMARILLO"\n╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣");
	mostrar_string_centrado (proximo_gimnasio.nombre, 41);
	printf(AMARILLO"╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
	sleep (2);
	system("clear");
}

void mostrar_cargando () {
	printf (AMARILLO"Cargando");
	for (int i = 0; i < 5; i++) {
		printf(".");
		fflush (stdout);
		sleep (1);
	}
	printf(NORMAL);
}

void enfrentar_gimnasios (heap_t* gimnasios, personaje_t* personaje, bool es_simulacion) {
	system("clear");
	int estado_batalla = PELEANDO;
	gimnasio_t* proximo_gimnasio = (gimnasio_t*) heap_ver_raiz (gimnasios);
	if (proximo_gimnasio) {
		presentar_gimnasio (*proximo_gimnasio);
		estado_batalla = enfrentar_gimnasio (*proximo_gimnasio, personaje, es_simulacion);
		if (estado_batalla == GANO) {
			estado_batalla = PELEANDO;
		}
	}
	mostrar_cargando ();
    while (estado_batalla == PELEANDO || estado_batalla == REINTENTAR) {
		if (estado_batalla == PELEANDO) {
			heap_eliminar_raiz (gimnasios);
		} else {
			estado_batalla = PELEANDO;
		}
		proximo_gimnasio = (gimnasio_t*) heap_ver_raiz (gimnasios);
		if (!proximo_gimnasio) {
			estado_batalla = GANO;
		}
		if (proximo_gimnasio) {
			presentar_gimnasio (*proximo_gimnasio);
			estado_batalla = enfrentar_gimnasio (*proximo_gimnasio, personaje, es_simulacion);
			if (estado_batalla == GANO) {
				estado_batalla = PELEANDO;
			}
		}

		mostrar_cargando ();
    }
}

void jugar_juego (heap_t* gimnasios, personaje_t** personaje, bool es_simulacion) {
	if (!(*personaje)) {
		*personaje = cargar_personaje ("src/Personaje.txt");
	}
	if (!(heap_ver_raiz (gimnasios))) {
		cargar_gimnasios ("src/GimnasiosKanto.txt", gimnasios);
	}
    enfrentar_gimnasios (gimnasios, *personaje, es_simulacion);
}

personaje_t* crear_entrenador (personaje_t* personaje) {
	char ruta[MAX_RUTA];
	printf ("Inserte la ruta del personaje: ");
	scanf (" %[^\n]", ruta);
	return cargar_personaje (ruta);
}

void agregar_nuevo_gimnasio (heap_t* gimnasios) {
	char ruta[MAX_RUTA];
	printf ("Inserte la ruta del gimnasio: ");
	scanf ("%s", ruta);
	cargar_gimnasios (ruta, gimnasios);
}

void mostrar_menu_inicio(bool personaje_seleccionado){
	system ("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                 BATALLA                 ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                 POKEMON                 ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣                                         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣   Ingresa la opcion que quieras elegir  ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    I: Comenzar partida                  ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    S: Simular partida                   ╠╬╬╬╬╣\n");
	if (!personaje_seleccionado) 
		printf(AMARILLO"╠╬╬╬╬╣    E: Ingresar archivo entrenador       ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    A: Agregar Gimnasio                  ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n");
	printf("                          ");
}

void menu_inicio(heap_t* gimnasios, personaje_t** personaje){
	
	char opcion_seleccionada = ' ';
	bool personaje_seleccionado = (*personaje != NULL);
	mostrar_menu_inicio (personaje_seleccionado);
	scanf (" %c", &opcion_seleccionada);
	while (opcion_seleccionada != 'I' && opcion_seleccionada != 'S' && opcion_seleccionada != 'E' && opcion_seleccionada != 'A') {
		mostrar_string_centrado ("Esa opcion no es valida", 53);
		printf("\n                          ");
		scanf (" %c", &opcion_seleccionada);
	}
	limpiar_buffer();
    if (opcion_seleccionada == 'I') {
        jugar_juego (gimnasios, personaje, false);
    } else if (opcion_seleccionada == 'S') {
        jugar_juego (gimnasios, personaje, true);
    } else if (opcion_seleccionada == 'E') {
        (*personaje) = crear_entrenador (*personaje);
		if (!(*personaje)) {
			printf ("Ha ocurrido un ERROR al seleccionar tu personaje, intenta nuevamente\n");
		}
		menu_inicio (gimnasios, personaje);
    } else if (opcion_seleccionada == 'A') {
        agregar_nuevo_gimnasio (gimnasios);
		menu_inicio (gimnasios, personaje);
    }
}

int main () {
	heap_t* gimnasios = heap_crear (comparador_gimnasios);
	personaje_t* personaje = NULL;
    menu_inicio(gimnasios, &personaje);
    return 0;
}