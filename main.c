#include <stdio.h>
#include <stdlib.h>
#include "tdas/heap/heap.h"
#include "gimnasios/gimnasios.h"

void mostrar_gimnasios (heap_t* gimnasios) {
    int tope = (*gimnasios).tope;
    for (int k = 0; k < tope; k++) {
        gimnasio_t gimnasio_actual = *(gimnasio_t*)heap_eliminar_raiz (gimnasios);
        printf("%s\n", gimnasio_actual.nombre);
        for (int i = 0; i < lista_elementos(gimnasio_actual.entrenadores); i++) {
            entrenador_t aux = *(entrenador_t*)lista_elemento_en_posicion(gimnasio_actual.entrenadores, (size_t)i);
            printf("\t%s\n", aux.nombre);
            for (int j = 0; j < aux.cant_pokemones; j++) {
                printf("\t\t%s\n", aux.pokemones[j].nombre);
            }
        }
    }
    printf("Hay %i gimnasio/s\n", tope);
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

int main () {
    heap_t* gimnasios = heap_crear(comparador_gimnasios);
    cargar_gimnasios("src/GimnasiosKanto.txt", gimnasios);
    mostrar_gimnasios(gimnasios);
}