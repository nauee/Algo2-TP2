#include "interfaces.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/****************************************** Constantes *******************************************/

#define AMARILLO "\033[1;33m"
#define NORMAL "\033[0m \033[39m"
#define MAX_LINEA 66
#define MAX_LINEA_MENU 100

/******************************************* Funciones *******************************************/

/*
*   Precondiciones: Debe recibir un string y un ancho validos.
*   Postcondiciones: Imprimira por pantalla la string recibida centrada.
*/
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

void mostrar_personaje (personaje_t personaje) {

	system("clear");
	printf(AMARILLO"\n          ╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"          ╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"          ╠╬╬╬╬╣");
	mostrar_string_centrado (personaje.nombre, MAX_LINEA);
	printf(AMARILLO"╠╬╬╬╬╣\n");
    printf(AMARILLO"          ╠╬╬╬╬╣ Pokemones para combatir:                                         ╠╬╬╬╬╣\n");
	for (int i = 0; i < lista_elementos(personaje.pokemon_para_combatir); i++) {
		pokemon_t aux = *(pokemon_t*) lista_elemento_en_posicion (personaje.pokemon_para_combatir, (size_t) i);
		printf(AMARILLO"          ╠╬╬╬╬╣  %-64s╠╬╬╬╬╣\n", aux.nombre);
	}
	printf(AMARILLO"          ╠╬╬╬╬╣                                                                  ╠╬╬╬╬╣\n");
    printf(AMARILLO"          ╠╬╬╬╬╣ Otros pokemons:                                                  ╠╬╬╬╬╣\n");
    for (int i = 6; i < lista_elementos(personaje.pokemon_obtenidos); i++) {
        pokemon_t aux = *(pokemon_t*)lista_elemento_en_posicion(personaje.pokemon_obtenidos,(size_t) i);
        printf(AMARILLO"          ╠╬╬╬╬╣  %-64s╠╬╬╬╬╣\n", aux.nombre);
    }
	printf(AMARILLO"          ╠╬╬╬╬╣                Presiona ENTER para volver al menu                ╠╬╬╬╬╣\n");
	printf(AMARILLO"          ╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"          ╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
	getchar ();

}

void mostrar_batalla (pokemon_t pkm_1, pokemon_t pkm_2) {
	
	system("clear");
	char aux[25];
	printf (AMARILLO"\n                          ___      ___ ________                               \n");
	printf (AMARILLO"                         |\\  \\    /  /|\\   ____\\                              \n");

	mostrar_string_centrado (pkm_1.nombre, 25);
	printf (AMARILLO"\\ \\  \\  /  / | \\  \\___|_    ");
	mostrar_string_centrado (pkm_2.nombre, 25);
	printf("\n");

	strcpy (aux, "");
	sprintf (aux, "Ataque: %i", pkm_1.ataque);
	mostrar_string_centrado (aux, 25);
	printf (AMARILLO" \\ \\  \\/  / / \\ \\_____  \\   ");
	strcpy (aux, "");
	sprintf (aux, "Ataque: %i", pkm_2.ataque);
	mostrar_string_centrado (aux, 25);
	printf("\n");

	strcpy (aux, "");
	sprintf (aux, "Defensa: %i", pkm_1.defensa);
	mostrar_string_centrado (aux, 25);
	printf (AMARILLO"  \\ \\    / /   \\|____|\\  \\  ");
	strcpy (aux, "");
	sprintf (aux, "Defensa: %i", pkm_2.defensa);
	mostrar_string_centrado (aux, 25);
	printf("\n");

	strcpy (aux, "");
	sprintf (aux, "Velocidad: %i", pkm_1.velocidad);
	mostrar_string_centrado (aux, 25);
	printf (AMARILLO"   \\ \\__/ /      ____\\_\\  \\ ");
	strcpy (aux, "");
	sprintf (aux, "Velocidad: %i", pkm_2.velocidad);
	mostrar_string_centrado (aux, 25);
	printf("\n");

	printf (AMARILLO"                             \\|__|/      |\\_________\\                         \n");
	printf (AMARILLO"                                         \\|_________|                         \n"NORMAL);
	sleep (1);
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

void mostrar_menu_elegir_pokemon_lider (entrenador_t lider) {
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	for (int i = 0; i < lista_elementos (lider.pokemon); i++) {
		printf(AMARILLO"╠╬╬╬╬╣    %03i: %-32s╠╬╬╬╬╣\n", i, (*(pokemon_t*) lista_elemento_en_posicion (lider.pokemon, (size_t) i)).nombre);

	}
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n");
	printf("                          ");
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

void mostrar_menu_rearmar_equipo (personaje_t personaje, bool es_primer_pkm) {
	system("clear");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    Pokemones para combatir:             ╠╬╬╬╬╣\n");
	for (int i = 0; i < lista_elementos (personaje.pokemon_para_combatir); i++) {
		printf(AMARILLO"╠╬╬╬╬╣    %03i: %-32s╠╬╬╬╬╣\n", i+1, (*(pokemon_t*)lista_elemento_en_posicion (personaje.pokemon_para_combatir, (size_t) i)).nombre);
	}
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
	printf("\n");
	printf(AMARILLO"╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣    Pokemones en el PC:                  ╠╬╬╬╬╣\n");
	for (int i = 6; i < lista_elementos (personaje.pokemon_obtenidos); i++) {
		printf(AMARILLO"╠╬╬╬╬╣    %03i: %-32s╠╬╬╬╬╣\n", i+1, (*(pokemon_t*)lista_elemento_en_posicion(personaje.pokemon_obtenidos, (size_t) i)).nombre);
	}
	printf(AMARILLO"╠╬╬╬╬╣        Ingresa 0 para finalizar         ╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
	if (es_primer_pkm) {
		printf("1º pokemon:               ");
	} else {
		printf("2º pokemon:               ");
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

void mostrar_gimnasio (gimnasio_t gimnasio, lista_t* entrenadores_vencidos) {

	system ("clear");
	printf(AMARILLO"\n          ╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"          ╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"          ╠╬╬╬╬╣");
	mostrar_string_centrado (gimnasio.nombre, MAX_LINEA);
	printf(AMARILLO"╠╬╬╬╬╣\n");
	printf(AMARILLO"          ╠╬╬╬╬╣ Entrenadores restantes:                                          ╠╬╬╬╬╣\n");
	for (int i = 0; i < lista_elementos (gimnasio.entrenadores); i++) {
		entrenador_t entrenador = * (entrenador_t*) lista_elemento_en_posicion (gimnasio.entrenadores, (size_t) i);
		printf(AMARILLO"          ╠╬╬╬╬╣  %-64s╠╬╬╬╬╣\n", entrenador.nombre);
		for (int j = 0; j < lista_elementos (entrenador.pokemon); j++) {
			printf (AMARILLO"          ╠╬╬╬╬╣    %-62s╠╬╬╬╬╣\n", (*(pokemon_t*) lista_elemento_en_posicion (entrenador.pokemon, (size_t) j)).nombre);
		}
	}
	printf(AMARILLO"          ╠╬╬╬╬╣                                                                  ╠╬╬╬╬╣\n");
	printf(AMARILLO"          ╠╬╬╬╬╣ Entrenadores derrotados:                                         ╠╬╬╬╬╣\n");
	for (int i = 0; i < lista_elementos (entrenadores_vencidos); i++) {
		entrenador_t entrenador = * (entrenador_t*) lista_elemento_en_posicion (entrenadores_vencidos, (size_t) i);
		printf(AMARILLO"          ╠╬╬╬╬╣  %-64s╠╬╬╬╬╣\n", entrenador.nombre);
        for (int j = 0; j < lista_elementos (entrenador.pokemon); j++) {
			printf (AMARILLO"          ╠╬╬╬╬╣    %-62s╠╬╬╬╬╣\n", (*(pokemon_t*) lista_elemento_en_posicion (entrenador.pokemon, (size_t) j)).nombre);
		}
	}
	printf(AMARILLO"          ╠╬╬╬╬╣                Presiona ENTER para volver al menu                ╠╬╬╬╬╣\n");
	printf(AMARILLO"          ╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"          ╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
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

void mostrar_cargando () {
	printf (AMARILLO"Cargando");
	for (int i = 0; i < 5; i++) {
		printf(".");
		fflush (stdout);
		sleep (1);
	}
	printf(NORMAL);
}

void mostrar_victoria_juego () {

	printf(AMARILLO"                             _______  _______  __       __    ______  __  .___________.    ___       ______  __    ______   .__   __.  _______     _______.                      \n"NORMAL);
	printf(AMARILLO"                            |   ____||   ____||  |     |  |  /      ||  | |           |   /   \\     /      ||  |  /  __  \\  |  \\ |  | |   ____|   /       |                      \n"NORMAL);
	printf(AMARILLO"                            |  |__   |  |__   |  |     |  | |  ,----'|  | `---|  |----`  /  ^  \\   |  ,----'|  | |  |  |  | |   \\|  | |  |__     |   (----`                      \n"NORMAL);
	printf(AMARILLO"                            |   __|  |   __|  |  |     |  | |  |     |  |     |  |      /  /_\\  \\  |  |     |  | |  |  |  | |  . `  | |   __|     \\   \\                          \n"NORMAL);
	printf(AMARILLO"                            |  |     |  |____ |  `----.|  | |  `----.|  |     |  |     /  _____  \\ |  `----.|  | |  `--'  | |  |\\   | |  |____.----)   |                         \n"NORMAL);
	printf(AMARILLO"                            |__|     |_______||_______||__|  \\______||__|     |__|    /__/     \\__\\ \\______||__|  \\______/  |__| \\__| |_______|_______/                          \n"NORMAL);
	printf(AMARILLO"      _______ .______       _______     _______.    __    __  .__   __.    ____    ____  _______ .______       _______       ___       _______   _______ .______        ______   \n"NORMAL);
	printf(AMARILLO"     |   ____||   _  \\     |   ____|   /       |   |  |  |  | |  \\ |  |    \\   \\  /   / |   ____||   _  \\     |       \\     /   \\     |       \\ |   ____||   _  \\      /  __  \\  \n"NORMAL);
	printf(AMARILLO"     |  |__   |  |_)  |    |  |__     |   (----`   |  |  |  | |   \\|  |     \\   \\/   /  |  |__   |  |_)  |    |  .--.  |   /  ^  \\    |  .--.  ||  |__   |  |_)  |    |  |  |  | \n"NORMAL);
	printf(AMARILLO"     |   __|  |      /     |   __|     \\   \\       |  |  |  | |  . `  |      \\      /   |   __|  |      /     |  |  |  |  /  /_\\  \\   |  |  |  ||   __|  |      /     |  |  |  | \n"NORMAL);
	printf(AMARILLO"     |  |____ |  |\\  \\----.|  |____.----)   |      |  `--'  | |  |\\   |       \\    /    |  |____ |  |\\  \\----.|  '--'  | /  _____  \\  |  '--'  ||  |____ |  |\\  \\----.|  `--'  | \n"NORMAL);
	printf(AMARILLO"     |_______|| _| `._____||_______|_______/        \\______/  |__| \\__|        \\__/     |_______|| _| `._____||_______/ /__/     \\__\\ |_______/ |_______|| _| `._____| \\______/  \n"NORMAL);
	printf(AMARILLO"              .___  ___.      ___       _______     _______.___________..______        ______      .______     ______    __  ___  _______ .___  ___.   ______   .__   __.        \n"NORMAL);
	printf(AMARILLO"              |   \\/   |     /   \\     |   ____|   /       |           ||   _  \\      /  __  \\     |   _  \\   /  __  \\  |  |/  / |   ____||   \\/   |  /  __  \\  |  \\ |  |        \n"NORMAL);
	printf(AMARILLO"              |  \\  /  |    /  ^  \\    |  |__     |   (----`---|  |----`|  |_)  |    |  |  |  |    |  |_)  | |  |  |  | |  '  /  |  |__   |  \\  /  | |  |  |  | |   \\|  |        \n"NORMAL);
	printf(AMARILLO"              |  |\\/|  |   /  /_\\  \\   |   __|     \\   \\       |  |     |      /     |  |  |  |    |   ___/  |  |  |  | |    <   |   __|  |  |\\/|  | |  |  |  | |  . `  |        \n"NORMAL);
	printf(AMARILLO"              |  |  |  |  /  _____  \\  |  |____.----)   |      |  |     |  |\\  \\----.|  `--'  |    |  |      |  `--'  | |  .  \\  |  |____ |  |  |  | |  `--'  | |  |\\   |        \n"NORMAL);
	printf(AMARILLO"              |__|  |__| /__/     \\__\\ |_______|_______/       |__|     | _| `._____| \\______/     | _|       \\______/  |__|\\__\\ |_______||__|  |__|  \\______/  |__| \\__|        \n"NORMAL);
	getchar();

}

void mostrar_derrota_juego () {

	printf(AMARILLO"      _______   _______ .______      .______        ______   .___________.    ___      \n"NORMAL);
	printf(AMARILLO"     |       \\ |   ____||   _  \\     |   _  \\      /  __  \\  |           |   /   \\     \n"NORMAL);
	printf(AMARILLO"     |  .--.  ||  |__   |  |_)  |    |  |_)  |    |  |  |  | `---|  |----`  /  ^  \\    \n"NORMAL);
	printf(AMARILLO"     |  |  |  ||   __|  |      /     |      /     |  |  |  |     |  |      /  /_\\  \\   \n"NORMAL);
	printf(AMARILLO"     |  '--'  ||  |____ |  |\\  \\----.|  |\\  \\----.|  `--'  |     |  |     /  _____  \\  \n"NORMAL);
	printf(AMARILLO"     |_______/ |_______|| _| `._____|| _| `._____| \\______/      |__|    /__/     \\__\\ \n"NORMAL);

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

void mostrar_presentacion_gimnasio (char* gimnasio) {
	system("clear");
	printf(AMARILLO"\n╔╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╗\n");
	printf(AMARILLO"╠╬╬╬╬╬╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╬╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╣");
	mostrar_string_centrado (gimnasio, 41);
	printf(AMARILLO"╠╬╬╬╬╣\n");
	printf(AMARILLO"╠╬╬╬╬╬╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╬╬╬╬╬╣\n");
	printf(AMARILLO"╚╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╝\n"NORMAL);
	sleep (2);
	system("clear");
}

/*************************************************************************************************/