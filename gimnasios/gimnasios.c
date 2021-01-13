#include "gimnasios.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/****************************************** Constantes *******************************************/

#define TAMANIO_BUFFER 1024
#define FORMATO_ENTRENADOR "%c;%[^\n]\n"
#define FORMATO_POKEMON "%c;%[^;];%i;%i;%i\n"
#define FORMATO_GIMNASIO "%c;%[^;];%i;%i\n"

/******************************************* Funciones *******************************************/

/*
*   Precondiciones: Debe recibir un archivo con el gimnasio abierto correctamente.
*   Postcondiciones: Leera una linea del archivo y la guardara en el dato correspondiente (entrenador, pokemon o gimnasio),
*   ademas guardara tambien que tipo de dato leyo (G, E, L, P).
*/
int leer_de_archivo (FILE* arch_gimnasio, char* tipo_leido, entrenador_t* entrenador_leido, pokemon_t* pokemon_leido, gimnasio_t* gimnasio_leido) {
    
    char buffer[TAMANIO_BUFFER];
    int leidos = 0;
    char* linea = fgets(buffer, TAMANIO_BUFFER, arch_gimnasio);
    if (!linea) {
        return -1;
    }

    if ((linea[0]) == 'E' || (linea[0]) == 'L') {
        leidos = sscanf(linea, FORMATO_ENTRENADOR, tipo_leido, (*entrenador_leido).nombre);
        (*entrenador_leido).es_lider = ((*tipo_leido) == 'L');
        (*entrenador_leido).cant_pokemones = 0;
    } else if ((linea[0]) == 'P') {
        leidos = sscanf(linea, FORMATO_POKEMON, tipo_leido, (*pokemon_leido).nombre, &((*pokemon_leido).velocidad), &((*pokemon_leido).ataque), &((*pokemon_leido).defensa));
    } else if ((linea[0]) == 'G') {
        leidos = sscanf(linea, FORMATO_GIMNASIO, tipo_leido, (*gimnasio_leido).nombre, &((*gimnasio_leido).dificultad), &((*gimnasio_leido).id_funcion_batalla));
        (*gimnasio_leido).entrenadores = lista_crear ();
    }
    
    return leidos;

}

/*
*   Precondiciones: Debe recibir un gimnasio valido con su pila de entrenadores inicializadas y un entrenador a agregar valido.
*   Postcondiciones: Agregara el entrenador a la pila de entrenadores dentro del gimnasio.
*/
void agregar_entrenador (gimnasio_t* gimnasio, entrenador_t entrenador_agregar) {
    
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

    gimnasio_t* gimnasio = calloc (1, sizeof(gimnasio_t));
    if (!gimnasio) {
        return;
    }
    gimnasio_t gimnasio_leido;
    entrenador_t entrenador_leido;
    pokemon_t pokemon_leido;
    char tipo_leido = ' ';
    int leidos = 0;
    leidos = leer_de_archivo (arch_gimnasio, &tipo_leido, &entrenador_leido, &pokemon_leido, &gimnasio_leido);
    if (tipo_leido != 'G') {
        return;
    }

    while (leidos != EOF) {
        gimnasio_t gimnasio_actual = gimnasio_leido;
        leidos = leer_de_archivo (arch_gimnasio, &tipo_leido, &entrenador_leido, &pokemon_leido, &gimnasio_leido);
        while (strcmp (gimnasio_leido.nombre, gimnasio_actual.nombre) == 0 && leidos != EOF) {
            entrenador_t entrenador_actual = entrenador_leido;
            leidos = leer_de_archivo (arch_gimnasio, &tipo_leido, &entrenador_leido, &pokemon_leido, &gimnasio_leido);
            while (strcmp (gimnasio_leido.nombre, gimnasio_actual.nombre) == 0 && strcmp (entrenador_leido.nombre, entrenador_actual.nombre) == 0 &&leidos != EOF){
                if (tipo_leido == 'P') {
                    entrenador_actual.pokemones[entrenador_actual.cant_pokemones] = pokemon_leido;
                    entrenador_actual.cant_pokemones ++;
                }
                leidos = leer_de_archivo (arch_gimnasio, &tipo_leido, &entrenador_leido, &pokemon_leido, &gimnasio_leido);
            }
            agregar_entrenador(&gimnasio_actual, entrenador_actual);
        }
        agregar_gimnasio(gimnasios, gimnasio_actual);
    }

}

/*************************************************************************************************/