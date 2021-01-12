#include "heap.h"
#include <stdlib.h>

#define CORRECTO 0
#define ERROR -1

int posicion_padre (int n) {
    return (n-1)/2;
}

int posicion_hijo_derecho (int n) {
    return 2*n+2;
}

int posicion_hijo_izquierdo (int n) {
    return 2*n+1;
}

heap_t* heap_crear (heap_comparador comparador) {
    
    if (!comparador) {
        return NULL;
    }

    heap_t* heap = calloc (1,sizeof(heap_t));
    if (!heap) {
        return NULL;
    }
    (*heap).comparador = comparador;
    return heap;
}

void intercambiar (void** elementos, int e1, int e2) {
    void* aux = elementos[e1];
    elementos[e1] = elementos[e2];
    elementos[e2] = aux;
}

void sift_up (heap_t* heap, int n) {
    if (n == 0) {
        return;
    }

    int padre = posicion_padre (n);

    if ((*heap).comparador ((*heap).elementos[padre], (*heap).elementos[n]) < 0) {
        intercambiar ((*heap).elementos, padre, n);
        sift_up (heap, padre);
    }

}

void sift_down (heap_t* heap, int n) {
    int hijo_izquierdo = posicion_hijo_izquierdo(n);
    int hijo_derecho = posicion_hijo_derecho(n);
    int hijo_menor = hijo_izquierdo;

    if (hijo_izquierdo >= (*heap).tope){
        return;
    }

    if (hijo_derecho < (*heap).tope) {
        if ((*heap).comparador((*heap).elementos[hijo_derecho], (*heap).elementos[hijo_izquierdo]) > 0) {
            hijo_menor = hijo_derecho;
        }
    }

    if ((*heap).comparador((*heap).elementos[hijo_menor], (*heap).elementos[n]) > 0) {
        intercambiar ((*heap).elementos, n, hijo_menor);
        sift_down (heap, hijo_menor);
    }

}

int heap_insertar (heap_t* heap, void* elemento) {

    if (!heap) {
        return ERROR;
    }

    ((*heap).tope) ++;
    void* tmp = realloc ((*heap).elementos, ((*heap).tope) * sizeof(void*));
    if (!tmp) {
        return ERROR;
    }

    (*heap).elementos = tmp;
    (*heap).elementos[(*heap).tope - 1] = elemento;
    sift_up (heap, (*heap).tope - 1);
    return CORRECTO;
}

void* heap_eliminar_raiz (heap_t* heap) {
    
    if (!heap) {
        return NULL;
    }
    
    if ((*heap).tope == 0) {
        return NULL;
    }

    void* valor = (*heap).elementos[0];
    (*heap).elementos[0] = (*heap).elementos[(*heap).tope-1];
    ((*heap).tope) --;
    void* tmp = realloc ((*heap).elementos, (*heap).tope * sizeof(void*));
    if (!tmp) {
        return valor;
    }
    sift_down (heap, 0);
    return valor;
}