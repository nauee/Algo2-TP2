#include "heap.h"
#include <stdlib.h>

/****************************************** Constantes *******************************************/

#define CORRECTO 0
#define ERROR -1

/******************************************* Funciones *******************************************/

/*
*	Precondiciones: Debera recibir una posicion en el vector de elementos valida.
*	Postcondiciones: Devolvera la posicion del padre.
*/
int posicion_padre (int n) {
    return (n-1)/2;
}

/*
*	Precondiciones: Debera recibir una posicion en el vector de elementos valida.
*	Postcondiciones: Devolvera la posicion del hijo derecho.
*/
int posicion_hijo_derecho (int n) {
    return 2*n+2;
}

/*
*	Precondiciones: Debera recibir una posicion en el vector de elementos valida.
*	Postcondiciones: Devolvera la posicion del hijo izquierdo.
*/
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

/*
*	Precondiciones: Debe recibir un vector de elementos y la posicion de los 2 elementos
*   a intercambiar.
*	Postcondiciones: Intercambiara de posicion los elementos indicados.
*/
void intercambiar (void** elementos, int e1, int e2) {
    void* aux = elementos[e1];
    elementos[e1] = elementos[e2];
    elementos[e2] = aux;
}

/*
*	Precondiciones: Debe recibir un heap valido y una posicion en el vector de elementos
*   valida.
*	Postcondiciones: Intercambiara el elemento en la posicion n con su padre en caso de
*   ser menor hasta que llegue a una posicion con un padre nulo o menor.
*/
void sift_up (heap_t* heap, int n) {
    
    if (!heap) {
        return;
    }

    if (n == 0) {
        return;
    }

    int padre = posicion_padre (n);

    if ((*heap).comparador ((*heap).elementos[padre], (*heap).elementos[n]) < 0) {
        intercambiar ((*heap).elementos, padre, n);
        sift_up (heap, padre);
    }

}

/*
*	Precondiciones: Debe recibir un heap valido y una posicion en el vector de elementos
*   valida.
*	Postcondiciones: Intercambiara el elemento en la posicion n con su hijo menor en caso
*   de ser mayor hasta que llegue a una posicion con ambos hijos mayores, o un hijo mayor
*   y uno nulo o ambos hijos nulos.
*/
void sift_down (heap_t* heap, int n) {

    if (!heap) {
        return;
    }

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
    void* tmp = realloc ((*heap).elementos, ((unsigned int)(*heap).tope) * sizeof(void*));
    if (!tmp) {
        return ERROR;
    }

    (*heap).elementos = tmp;
    (*heap).elementos[(*heap).tope - 1] = elemento;
    sift_up (heap, (*heap).tope - 1);
    return CORRECTO;
}

void* heap_ver_raiz (heap_t* heap) {
    if (!heap) {
        return NULL;
    }

    if ((*heap).tope == 0) {
        return NULL;
    }

    return (*heap).elementos[0];
}

int heap_eliminar_raiz (heap_t* heap) {
    
    if (!heap) {
        return ERROR;
    }
    
    if ((*heap).tope == 0) {
        return ERROR;
    }

    (*heap).elementos[0] = (*heap).elementos[(*heap).tope-1];
    ((*heap).tope) --;
    void* tmp = realloc ((*heap).elementos, (unsigned int)(*heap).tope * sizeof(void*));
    if (!tmp && (*heap).tope != 0) {
        return ERROR;
    }
    ((*heap).elementos) = tmp;
    sift_down (heap, 0);
    return CORRECTO;
}

void heap_destruir (heap_t* heap) {
    while ((*heap).tope > 0) {
        heap_eliminar_raiz (heap);
    }
    free (heap);
}

/*************************************************************************************************/