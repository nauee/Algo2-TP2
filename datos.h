#ifndef __DATOS_H__
#define __DATOS_H__

#include "tdas/lista/lista.h"

/****************************************** Constantes *******************************************/

#define MAX_NOMBRE 50

/***************************************** Tipos de datos ****************************************/

typedef struct gimnasio {
    char nombre[MAX_NOMBRE];
    lista_t* entrenadores; // Pila
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
    lista_t* pokemones; // Cola
    bool es_lider;
} entrenador_t;

typedef struct personaje {
    char nombre[MAX_NOMBRE];
    lista_t* pokemon_para_combatir; // Cola
    lista_t* pokemon_obtenidos; // Lista
} personaje_t;

#endif /* __DATOS_H__ */