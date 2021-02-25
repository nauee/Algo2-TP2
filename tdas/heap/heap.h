#ifndef __HEAP_H__
#define __HEAP_H__

typedef int (*heap_comparador)(void*, void*);

typedef struct heap{
    void** elementos;
    int tope;
    heap_comparador comparador;
} heap_t;

/*
*	Precondiciones: Debe recibir un comparador valido.
*	Postcondiciones: Creara el heap asignandole el comparador recibido.
*/
heap_t* heap_crear (heap_comparador comparador);

/*
*	Precondiciones: Debe recibir un heap valido y un elemento.
*	Postcondiciones: Insertara el elemento en el heap y devolvera -1 en caso de error
*   y 0 en caso de insertar correctamente.
*/
int heap_insertar (heap_t* heap, void* elemento);

/*
*	Precondiciones: Debe recibir un heap valido.
*	Postcondiciones: Devolvera la raiz del heap en caso de tener, o NULL en caso de que
*   el heap este vacio.
*/
void* heap_ver_raiz (heap_t* heap);

/*
*	Precondiciones: Debe recibir un heap valido.
*	Postcondiciones: Eliminara la raiz del heap y devolvera -1 en caso de error
*   y en 0 en caso de poder borrar correctamente.
*/
int heap_eliminar_raiz (heap_t* heap);

/*
*	Precondiciones: Debe recibir un heap valido.
*	Postcondiciones: Liberara la memoria reservada por el heap.
*/
void heap_destruir (heap_t* heap);

#endif /* __HEAP_H__ */