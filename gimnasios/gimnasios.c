#include "gimnasios.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../datos.h"
#include "../tdas/lista/lista.h"

/****************************************** Constantes *******************************************/

#define TAMANIO_BUFFER 1024
#define FORMATO_ENTRENADOR "%c;%[^\n]\n"
#define FORMATO_POKEMON "%c;%[^;];%i;%i;%i\n"
#define FORMATO_GIMNASIO "%c;%[^;];%i;%i\n"
#define MAX_PUNTOS_MEJORA 63

/******************************************* Funciones *******************************************/

/*
*   Precondiciones: Debe recibir un archivo con el gimnasio abierto correctamente.
*   Postcondiciones: Leera una linea del archivo y la guardara en el dato correspondiente (entrenador, pokemon o gimnasio),
*   ademas guardara tambien que tipo de dato leyo (G, E, L, P).
*/
static int leer_de_archivo (FILE* arch_gimnasio, char* tipo_leido, entrenador_t* entrenador_leido, pokemon_t* pokemon_leido, gimnasio_t* gimnasio_leido) {
    
    char buffer[TAMANIO_BUFFER];
    int leidos = 0;
    char* linea = fgets(buffer, TAMANIO_BUFFER, arch_gimnasio);
    if (!linea) {
        return EOF;
    }

    if ((linea[0]) == 'E' || (linea[0]) == 'L') {
        (*entrenador_leido).nombre[0] = '\0';
        leidos = sscanf(linea, FORMATO_ENTRENADOR, tipo_leido, (*entrenador_leido).nombre);
        (*entrenador_leido).es_lider = ((*tipo_leido) == 'L');
        (*entrenador_leido).cant_pokemon = 0;
    } else if ((linea[0]) == 'P') {
        (*pokemon_leido).nombre[0] = '\0';
        (*pokemon_leido).velocidad = 0;
        (*pokemon_leido).ataque = 0;
        (*pokemon_leido).defensa = 0;
        leidos = sscanf(linea, FORMATO_POKEMON, tipo_leido, (*pokemon_leido).nombre, &((*pokemon_leido).velocidad), &((*pokemon_leido).ataque), &((*pokemon_leido).defensa));
        (*pokemon_leido).puntos_de_mejora = MAX_PUNTOS_MEJORA;
    } else if ((linea[0]) == 'G') {
        (*gimnasio_leido).nombre[0] = '\0';
        (*gimnasio_leido).dificultad = 0;
        (*gimnasio_leido).id_funcion_batalla = 0;
        leidos = sscanf(linea, FORMATO_GIMNASIO, tipo_leido, (*gimnasio_leido).nombre, &((*gimnasio_leido).dificultad), &((*gimnasio_leido).id_funcion_batalla));
        (*gimnasio_leido).entrenadores = lista_crear ();
    }
    
    return leidos;

}

/*
*   Precondiciones: Debe recibir un entrenador valido con su cola de pokemones inicializada y un pokemon a agregar valido.
*   Postcondiciones: Agregara el pokemon a la cola de pokemones del entrenador.
*/
static void agregar_pokemon (entrenador_t* entrenador, pokemon_t pokemon_agregar) {

    if (pokemon_agregar.nombre[0] == '\0' || pokemon_agregar.velocidad <= 0 || pokemon_agregar.ataque <= 0 || pokemon_agregar.defensa <= 0) {
        return;
    }

    pokemon_t* pokemon = calloc (1, sizeof(pokemon_t));
    if (!pokemon) {
        return;
    }
    (*pokemon) = pokemon_agregar;
    ((*entrenador).pokemon[(*entrenador).cant_pokemon]) = pokemon;
    ((*entrenador).cant_pokemon) ++;

}

/*
*   Precondiciones: Debe recibir un gimnasio valido con su pila de entrenadores inicializadas y un entrenador a agregar valido.
*   Postcondiciones: Agregara el entrenador a la pila de entrenadores del gimnasio.
*/
void agregar_entrenador (gimnasio_t* gimnasio, entrenador_t entrenador_agregar) {
    
    if (entrenador_agregar.cant_pokemon == 0) {
        return;
    }

    if (entrenador_agregar.nombre[0] == '\0') {
        for (int i = 0; i < entrenador_agregar.cant_pokemon; i++) {
            free (entrenador_agregar.pokemon[i]);
        }
        return;
    }

    entrenador_t* entrenador = calloc (1, sizeof(entrenador_t));
    if (!entrenador) {
        return;
    }
    (*entrenador) = entrenador_agregar;
    lista_apilar((*gimnasio).entrenadores, entrenador);

}

/*
*   Precondiciones: Debe recibir un heap de gimnasios inicializado y un gimnasio a agregar valido.
*   Postcondiciones: Agregara el gimnasio al heap de gimnasios.
*/
void agregar_gimnasio (heap_t* gimnasios, gimnasio_t gimnasio_agregar) {
    
    bool esta_mal_cargado = false;
    bool tiene_lider = false;

    if (lista_elementos(gimnasio_agregar.entrenadores) == 0) {
        return;
    }

    if (gimnasio_agregar.nombre[0] == '\0' || gimnasio_agregar.dificultad <= 0 || gimnasio_agregar.id_funcion_batalla <= 0 || gimnasio_agregar.id_funcion_batalla > 5) {
        esta_mal_cargado = true;
    }
    for (int i = 0; i < lista_elementos (gimnasio_agregar.entrenadores); i++) {
        if ((*(entrenador_t*) lista_elemento_en_posicion (gimnasio_agregar.entrenadores, (size_t) i)).es_lider) {
            tiene_lider = true;
        }
    }
    if (!tiene_lider || esta_mal_cargado) {
        while (lista_elementos(gimnasio_agregar.entrenadores) > 0) {
		    entrenador_t* entrenador_borrar = (entrenador_t*) lista_primero (gimnasio_agregar.entrenadores);
		    for (int i = 0; i < (*entrenador_borrar).cant_pokemon; i++) {
		    	free ((*entrenador_borrar).pokemon[i]);
		    }
		    free (entrenador_borrar);
		    lista_borrar_de_posicion (gimnasio_agregar.entrenadores, 0);
	    }
	    lista_destruir (gimnasio_agregar.entrenadores);
        return;
    }

    gimnasio_t* gimnasio = calloc (1, sizeof(gimnasio_t));
    if (!gimnasio) {
        return;
    }
    (*gimnasio) = gimnasio_agregar;
    heap_insertar(gimnasios, gimnasio);

}

/*
*   Precondiciones: Debe recibir una ruta valida y un heap de gimnasios inicializado.
*   Postcondicones: Agregara al heap de gimnasios los gimnasios leidos en el archivo ubicado en la ruta.
*/
void cargar_gimnasios (char* ruta, heap_t* gimnasios){
    
    if (!gimnasios) {
        return;
    }

    FILE* arch_gimnasio = fopen (ruta, "r");
    if (!arch_gimnasio) {
        return;
    }

    gimnasio_t gimnasio_leido;
    entrenador_t entrenador_leido;
    pokemon_t pokemon_leido;
    char tipo_leido = ' ';
    int leidos = 0;
    leidos = leer_de_archivo (arch_gimnasio, &tipo_leido, &entrenador_leido, &pokemon_leido, &gimnasio_leido);
    while (leidos != EOF) {
        gimnasio_t gimnasio_actual = gimnasio_leido;
        leidos = leer_de_archivo (arch_gimnasio, &tipo_leido, &entrenador_leido, &pokemon_leido, &gimnasio_leido);
        while (strcmp (gimnasio_leido.nombre, gimnasio_actual.nombre) == 0 && leidos != EOF) {
            if ((tipo_leido == 'E' || tipo_leido == 'L')) {
                entrenador_t entrenador_actual = entrenador_leido;
                leidos = leer_de_archivo (arch_gimnasio, &tipo_leido, &entrenador_leido, &pokemon_leido, &gimnasio_leido);
                while (strcmp (gimnasio_leido.nombre, gimnasio_actual.nombre) == 0 && strcmp (entrenador_leido.nombre, entrenador_actual.nombre) == 0 &&leidos != EOF){
                    if (tipo_leido == 'P') {
                        agregar_pokemon(&entrenador_actual, pokemon_leido);
                    }
                    leidos = leer_de_archivo (arch_gimnasio, &tipo_leido, &entrenador_leido, &pokemon_leido, &gimnasio_leido);
                }
                agregar_entrenador(&gimnasio_actual, entrenador_actual);
            } else {
                leidos = leer_de_archivo (arch_gimnasio, &tipo_leido, &entrenador_leido, &pokemon_leido, &gimnasio_leido);
            }
        }
        agregar_gimnasio(gimnasios, gimnasio_actual);
    }

    fclose(arch_gimnasio);

}

/*************************************************************************************************/