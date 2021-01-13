#ifndef __GIMNASIOS_H__
#define __GIMNASIOS_H__

#include "../tdas/lista/lista.h"
#include "../tdas/heap/heap.h"

/****************************************** Constantes *******************************************/

#define MAX_NOMBRE 50
#define MAX_POKE_ENTRENADOR 6

/**************************************** Tipos de datos *****************************************/

typedef struct gimnasio {
    char nombre[MAX_NOMBRE];
    lista_t* entrenadores;
    int dificultad;
    int id_funcion_batalla;
} gimnasio_t;

typedef struct pokemon {
    char nombre[MAX_NOMBRE];
    int velocidad;
    int defensa;
    int ataque;
} pokemon_t;

typedef struct entrenador {
    char nombre[MAX_NOMBRE];
    pokemon_t pokemones[MAX_POKE_ENTRENADOR];
    int cant_pokemones;
    bool es_lider;
} entrenador_t;

/******************************************* Funciones *******************************************/

/*
*   Precondiciones: Debe recibir una ruta valida y un heap de gimnasios inicializado.
*   Postcondicones: Agregara al heap de gimnasios los gimnasios leidos en el archivo ubicado en la ruta.
*/
void cargar_gimnasios (char* ruta, heap_t* gimnasios);

#endif /*__GIMNASIOS_H__*/

/*************************************************************************************************/