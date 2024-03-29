#include "personaje.h"
#include <stdlib.h>
#include <stdio.h>

/****************************************** Constantes *******************************************/

#define TAMANIO_BUFFER 1024
#define FORMATO_ENTRENADOR "%c;%[^\n]\n"
#define FORMATO_POKEMON "%c;%[^;];%i;%i;%i\n"
#define PUNTOS_MAX_MEJORA 63
#define MAX_POKEMON_BATALLA 6

/******************************************* Funciones *******************************************/

static int leer_de_archivo (FILE* arch_personaje, char* tipo_leido, pokemon_t* pokemon_leido, personaje_t* personaje_leido) {
    
    char buffer[TAMANIO_BUFFER];
    int leidos = 0;
    char* linea = fgets(buffer, TAMANIO_BUFFER, arch_personaje);
    if (!linea) {
        return -1;
    }

    if ((linea[0]) == 'E') {
        leidos = sscanf(linea, FORMATO_ENTRENADOR, tipo_leido, (*personaje_leido).nombre);
        (*personaje_leido).pokemon_para_combatir = lista_crear();
        (*personaje_leido).pokemon_obtenidos = lista_crear();
    } else if ((linea[0]) == 'P') {
        (*pokemon_leido).nombre[0] = '\0';
        (*pokemon_leido).velocidad = 0;
        (*pokemon_leido).ataque = 0;
        (*pokemon_leido).defensa = 0;
        leidos = sscanf(linea, FORMATO_POKEMON, tipo_leido, (*pokemon_leido).nombre, &((*pokemon_leido).velocidad), &((*pokemon_leido).ataque), &((*pokemon_leido).defensa));
    }
    
    return leidos;

}

/*
*   Precondiciones: Debe recibir un entrenador valido con su cola de pokemones inicializada y un pokemon a agregar valido.
*   Postcondiciones: Agregara el pokemon a la cola de pokemon_para_combatir del personaje o a los pokemon_obtenidos en caso
*   de ya tener 6 pokemones en pokemon_para_combatir.
*/
static void agregar_pokemon (personaje_t* personaje, pokemon_t pokemon_agregar) {

    if (pokemon_agregar.nombre[0] == '\0' || pokemon_agregar.velocidad <= 0 || pokemon_agregar.ataque <= 0 || pokemon_agregar.defensa <= 0) {
        return;
    }

    pokemon_t* pokemon = calloc (1, sizeof(pokemon_t));
    if (!pokemon) {
        return;
    }
    (*pokemon) = pokemon_agregar;
    if (lista_elementos((*personaje).pokemon_para_combatir) < MAX_POKEMON_BATALLA) {
        lista_insertar ((*personaje).pokemon_para_combatir, pokemon);
    }
    lista_insertar ((*personaje).pokemon_obtenidos, pokemon);

}

personaje_t* cargar_personaje (char* ruta) {
    
    if (!ruta) {
        return NULL;
    }

    FILE* arch_personaje = fopen (ruta, "r");
    if (!arch_personaje) {
        return NULL;
    }

    personaje_t* personaje = calloc (1, sizeof(personaje_t));
    pokemon_t pokemon_leido;
    char tipo_leido = ' ';
    int leidos;
    leidos = leer_de_archivo (arch_personaje, &tipo_leido, &pokemon_leido, personaje);
    if (tipo_leido != 'E' || (*personaje).nombre[0] == '\0') {
        free (personaje);
        fclose (arch_personaje);
        return NULL;
    }
    leidos = leer_de_archivo (arch_personaje, &tipo_leido, &pokemon_leido, personaje);
    while (leidos != EOF && tipo_leido == 'P'){
        pokemon_leido.puntos_de_mejora = PUNTOS_MAX_MEJORA;
        agregar_pokemon (personaje, pokemon_leido);
        leidos = leer_de_archivo (arch_personaje, &tipo_leido, &pokemon_leido, personaje);
    }
    fclose (arch_personaje);
    return personaje;
}

/*************************************************************************************************/