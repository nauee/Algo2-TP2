#ifndef __HEAP_H__
#define __HEAP_H__

typedef int (*heap_comparador)(void*, void*);

typedef struct heap{
    void** elementos;
    int tope;
    heap_comparador comparador;
} heap_t;

heap_t* heap_crear (heap_comparador comparador);

int heap_insertar (heap_t* heap, void* elemento);

void* heap_eliminar_raiz (heap_t* heap);

void heap_eliminar (heap_t* heap);

#endif /* __HEAP_H__ */