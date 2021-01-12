#ifndef __GIMNASIOS_H__
#define __GIMNASIOS_H__

#include "../tdas/lista/lista.h"
#include "../tdas/heap/heap.h"

typedef struct gimnasio {
    lista_t* entrenadores;
    int dificultad;
    int id_funcion_batalla;
} gimnasio_t;

void cargar_gimnasio (char* ruta, heap_t* gimnasios);

#endif __GIMNASIOS_H__