#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../heap.h"
#include "pa2m.h"

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

void probar_heap_crear () {
    pa2m_nuevo_grupo ("     Pruebas crear     ");
    heap_t* heap;
    pa2m_afirmar ((heap = heap_crear (NULL)) == NULL, "No se puede crear un heap sin comparador");
    pa2m_afirmar ((heap = heap_crear (comparador_manzanas)) != NULL, "Se puede crear un heap con comparador");
    pa2m_afirmar ((*heap).comparador == comparador_manzanas, "El comparador es el correcto");
    pa2m_afirmar ((*heap).elementos == NULL, "El vector de elementos apunta a NULL");
    pa2m_afirmar ((*heap).tope == 0, "El tope de elementos es 0");
    heap_destruir (heap);
}

void probar_heap_funcionalidad () {

    pa2m_nuevo_grupo ("     Pruebas de insercion     ");
    heap_t* heap = heap_crear (comparador_manzanas);
    manzana_t* manzana = crear_manzana (1, 34);
    pa2m_afirmar (heap_insertar (heap, manzana) == 0, "Puedo insertar un elemento en la raiz");
    manzana = crear_manzana (1, 98);
    pa2m_afirmar (heap_insertar (heap, manzana) == 0, "Puedo insertar un segundo elemento");
    manzana = crear_manzana (1, 65);
    pa2m_afirmar (heap_insertar (heap, manzana) == 0, "Puedo insertar un tercer elemento");
    manzana = crear_manzana (1, 15);
    pa2m_afirmar (heap_insertar (heap, manzana) == 0, "Puedo insertar un cuarto elemento");
    manzana = crear_manzana (1, 77);
    pa2m_afirmar (heap_insertar (heap, manzana) == 0, "Puedo insertar un quinto elemento");
    manzana = crear_manzana (1, 2);
    pa2m_afirmar (heap_insertar (heap, manzana) == 0, "Puedo insertar un sexto elemento");
    manzana = crear_manzana (1, 6);
    pa2m_afirmar (heap_insertar (heap, manzana) == 0, "Puedo insertar un septimo elemento");
    manzana = crear_manzana (1, 43);
    pa2m_afirmar (heap_insertar (heap, manzana) == 0, "Puedo insertar un octavo elemento");
    manzana = crear_manzana (1, 25);
    pa2m_afirmar (heap_insertar (heap, manzana) == 0, "Puedo insertar un noveno elemento");
    pa2m_afirmar (heap_insertar (NULL, manzana) == -1, "No puedo insertar en un heap nulo");
    int pesos_esperados [9] = {2, 25, 6, 34, 77, 65, 15, 98, 43};
    int pesos_insertados [9];
    for (int i = 0; i < 9; i++) {
        pesos_insertados[i] = (*(manzana_t*)((*heap).elementos[i])).peso;
    }
    bool todos_correctos = true;
    for (int i = 0; i < 9; i++) {
        if (pesos_esperados[i] != pesos_insertados[i]) todos_correctos = false;
    }
    pa2m_afirmar (todos_correctos, "Los elementos estan correctamente ubicados dentro del heap");

    pa2m_nuevo_grupo ("     Pruebas de eliminar y ver raiz     ");
    pa2m_afirmar ((* (manzana_t*) heap_ver_raiz (heap)).peso == 2, "La raiz es la manzana de peso 2");
    pa2m_afirmar (heap_eliminar_raiz (heap) == 0, "Puedo borrar la raiz");
    pa2m_afirmar ((* (manzana_t*) heap_ver_raiz (heap)).peso == 6, "Elimino la raiz y la nueva raiz es la manzana de peso 6");
    pa2m_afirmar (heap_eliminar_raiz (heap) == 0, "Puedo borrar la raiz");
    pa2m_afirmar ((* (manzana_t*) heap_ver_raiz (heap)).peso == 15, "Elimino la raiz y la nueva raiz es la manzana de peso 15");
    pa2m_afirmar (heap_eliminar_raiz (heap) == 0, "Puedo borrar la raiz");
    pa2m_afirmar ((* (manzana_t*) heap_ver_raiz (heap)).peso == 25, "Elimino la raiz y la nueva raiz es la manzana de peso 25");

    int pesos_esperados_2 [6] = {25, 34, 43, 98, 77, 65};
    for (int i = 0; i < 6; i++) {
        pesos_insertados[i] = (*(manzana_t*)((*heap).elementos[i])).peso;
    }
    todos_correctos = true;
    for (int i = 0; i < 6; i++) {
        if (pesos_esperados_2[i] != pesos_insertados[i]) todos_correctos = false;
    }
    pa2m_afirmar (todos_correctos, "Los elementos estan correctamente ubicados dentro del heap");

    pa2m_afirmar (heap_eliminar_raiz (heap) == 0, "Puedo borrar la raiz");
    pa2m_afirmar ((* (manzana_t*) heap_ver_raiz (heap)).peso == 34, "Elimino la raiz y la nueva raiz es la manzana de peso 34");
    pa2m_afirmar (heap_eliminar_raiz (heap) == 0, "Puedo borrar la raiz");
    pa2m_afirmar ((* (manzana_t*) heap_ver_raiz (heap)).peso == 43, "Elimino la raiz y la nueva raiz es la manzana de peso 43");
    pa2m_afirmar (heap_eliminar_raiz (heap) == 0, "Puedo borrar la raiz");
    pa2m_afirmar ((* (manzana_t*) heap_ver_raiz (heap)).peso == 65, "Elimino la raiz y la nueva raiz es la manzana de peso 65");
    pa2m_afirmar (heap_eliminar_raiz (heap) == 0, "Puedo borrar la raiz");
    pa2m_afirmar ((* (manzana_t*) heap_ver_raiz (heap)).peso == 77, "Elimino la raiz y la nueva raiz es la manzana de peso 77");
    pa2m_afirmar (heap_eliminar_raiz (heap) == 0, "Puedo borrar la raiz");
    pa2m_afirmar ((* (manzana_t*) heap_ver_raiz (heap)).peso == 98, "Elimino la raiz y la nueva raiz es la manzana de peso 98");
    pa2m_afirmar (heap_eliminar_raiz (heap) == 0, "Puedo borrar la raiz");
    pa2m_afirmar (heap_ver_raiz (heap) == NULL, "Elimino la raiz y ya no quedan elementos en el heap");
    pa2m_afirmar (heap_eliminar_raiz (heap) == -1, "No puedo borrar la raiz de un heap vacio");
    pa2m_afirmar (heap_ver_raiz (NULL) == NULL, "No puedo ver la raiz de un heap nulo");
    pa2m_afirmar (heap_eliminar_raiz (NULL) == -1, "No puedo borrar la raiz de un heap nulo");

}

int main () {
    probar_heap_crear ();
    probar_heap_funcionalidad ();
    pa2m_mostrar_reporte();
}