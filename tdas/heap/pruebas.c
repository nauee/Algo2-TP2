#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct manzana{
    int peso;
    int color;
} manzana_t;

int comparador_manzanas (void* e1, void* e2) {
    if ((*(manzana_t*)e1).peso == (*(manzana_t*)e2).peso){
        return 0;
    } else if ((*(manzana_t*)e1).peso > (*(manzana_t*)e2).peso) {
        return -1;
    } else {
        return 1;
    }
}

manzana_t* crear_manzana (int color, int peso) {
    manzana_t* manzana = malloc (sizeof(manzana_t));
    if (!manzana) {
        return NULL;
    }
    (*manzana).color = color;
    (*manzana).peso = peso;
    return manzana;
}
/*
int main () {
    heap_t* heap = heap_crear (comparador_manzanas);
    manzana_t* m1 = crear_manzana (0, 15);
    manzana_t* m2 = crear_manzana (0, 21);
    manzana_t* m3 = crear_manzana (0, 13);
    manzana_t* m4 = crear_manzana (0, 18);
    manzana_t* m5 = crear_manzana (0, 12);
    manzana_t* m6 = crear_manzana (0, 1);
    manzana_t* m7 = crear_manzana (0, 5);
    manzana_t* m8 = crear_manzana (0, 66);
    heap_insertar (heap, m1);
    heap_insertar (heap, m2);
    heap_insertar (heap, m3);
    heap_insertar (heap, m4);
    heap_insertar (heap, m5);
    heap_insertar (heap, m6);
    heap_insertar (heap, m7);
    heap_insertar (heap, m8);
    manzana_t* retorno = heap_eliminar_raiz (heap);
    printf ("%i\n", (*retorno).peso);
    retorno = heap_eliminar_raiz (heap);
    printf ("%i\n", (*retorno).peso);
    retorno = heap_eliminar_raiz (heap);
    printf ("%i\n", (*retorno).peso);
    retorno = heap_eliminar_raiz (heap);
    printf ("%i\n", (*retorno).peso);
    retorno = heap_eliminar_raiz (heap);
    printf ("%i\n", (*retorno).peso);
    retorno = heap_eliminar_raiz (heap);
    printf ("%i\n", (*retorno).peso);
    retorno = heap_eliminar_raiz (heap);
    printf ("%i\n", (*retorno).peso);
    retorno = heap_eliminar_raiz (heap);
    printf ("%i\n", (*retorno).peso);
}*/