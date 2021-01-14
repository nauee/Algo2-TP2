#include <stdio.h>
#include <stdlib.h>
#include "tdas/heap/heap.h"
#include "gimnasios/gimnasios.h"
#include "personaje/personaje.h"
#include "datos.h"

void mostrar_gimnasios (heap_t* gimnasios) {
    int tope = (*gimnasios).tope;
    for (int k = 0; k < tope; k++) {
        gimnasio_t gimnasio_actual = *(gimnasio_t*)heap_eliminar_raiz (gimnasios);
        printf("%s\n", gimnasio_actual.nombre);
        for (int i = 0; i < lista_elementos(gimnasio_actual.entrenadores); i++) {
            entrenador_t entrenador_actual = *(entrenador_t*)lista_elemento_en_posicion(gimnasio_actual.entrenadores, (size_t)i);
            printf("\t%s\n", entrenador_actual.nombre);
            for (int j = 0; j < lista_elementos(entrenador_actual.pokemones); j++) {
                pokemon_t pokemon_actual = *(pokemon_t*)lista_elemento_en_posicion(entrenador_actual.pokemones, (size_t)j);
                printf("\t\t%s\n", pokemon_actual.nombre);
            }
        }
    }
    printf("Hay %i gimnasio/s\n", tope);
}

void mostrar_personaje (personaje_t* personaje) {
    printf("Nombre: %s\n", (*personaje).nombre);
    printf("Pokemones para combatir:\n");
    for (int i = 0; i < lista_elementos((*personaje).pokemon_para_combatir); i++) {
        pokemon_t aux = *(pokemon_t*)lista_elemento_en_posicion((*personaje).pokemon_para_combatir,(size_t) i);
        printf("\t%s\n", aux.nombre);
    }
    printf("Pokemones obtenidos: \n");
    for (int i = 0; i < lista_elementos((*personaje).pokemon_obtenidos); i++) {
        pokemon_t aux = *(pokemon_t*)lista_elemento_en_posicion((*personaje).pokemon_obtenidos,(size_t) i);
        printf("\t%s\n", aux.nombre);
    }
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
    personaje_t* personaje = cargar_personaje("src/Personaje.txt");
    cargar_gimnasios("src/GimnasiosKanto.txt", gimnasios);
    mostrar_gimnasios(gimnasios);
    mostrar_personaje(personaje);
}