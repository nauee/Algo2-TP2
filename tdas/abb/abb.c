#include "abb.h"
#include <stdio.h>

#define NINGUNO 0
#define IZQUIERDO -1
#define DERECHO 1

/******************************************************************************************** Arbol_crear ********************************************************************************************/

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    
    if (!comparador) {
        return NULL;
    }

    abb_t* arbol = malloc (sizeof(abb_t));
    if (!arbol) {
        return NULL;
    }

    (*arbol).nodo_raiz = NULL;
    (*arbol).comparador = comparador;
    (*arbol).destructor = destructor;
    return arbol;

}

/****************************************************************************************** Arbol_insertar *******************************************************************************************/

/*
*   Precondiciones: Debe recibir un elemento del mismo tipo que el arbol.
*   Postcondiciones: Devolvera la direccion de memoria de un nuevo nodo con el elemento recibido.
*/
nodo_abb_t* crear_nodo (void* elemento) {

    nodo_abb_t* nodo = calloc (1, sizeof(nodo_abb_t));
    if (!nodo) {
        return NULL;
    } else {
        (*nodo).elemento = elemento;
        return nodo;
    }

}

/*
*   Precondiciones: Debe recibir un nodo valido (distinto de NULL), un elemento del mismo tipo que el resto, y una funcion para comparar dichos elementos.
*   Postcondiciones: Devolvera 0 en caso de poder insertar el elemento o -1 en caso contrario.
*/
int arbol_insertar_aux (nodo_abb_t* nodo_actual, void* elemento, abb_comparador comparador) {
    
    int comparacion = comparador (elemento, (*nodo_actual).elemento);

    if (comparacion > 0){
        if (!(*nodo_actual).derecha){
            nodo_abb_t* nodo = crear_nodo (elemento);
            if(!nodo){
                return -1;
            }
            (*nodo_actual).derecha = nodo;
            return 0;
        } else {
            return arbol_insertar_aux ((*nodo_actual).derecha, elemento, comparador);
        }
    } else {
        if (!(*nodo_actual).izquierda){
            nodo_abb_t* nodo = crear_nodo (elemento);
            if(!nodo){
                return -1;
            }
            (*nodo_actual).izquierda = nodo;
            return 0;
        } else {
            return arbol_insertar_aux ((*nodo_actual).izquierda, elemento, comparador);
        }
    }

}

int arbol_insertar(abb_t* arbol, void* elemento){
    if (!arbol) {
        return -1;
    }

    if(!(*arbol).nodo_raiz) {
        nodo_abb_t* nodo = crear_nodo (elemento);
        if(!nodo){
            return -1;
        }
        (*arbol).nodo_raiz = nodo;
        return 0;
    }

    return arbol_insertar_aux ((*arbol).nodo_raiz, elemento, (*arbol).comparador);

}

/******************************************************************************************* Arbol_borrar ********************************************************************************************/

/*
*   Precondiciones: Debe recibir un nodo_borrar valido (sin hijos y != NULL), y un arbol valido.
*   Postcondiciones: Borrara el nodo recibido.
*/
void borrar_nodo_hoja (nodo_abb_t* padre, nodo_abb_t* nodo_borrar, abb_t* arbol) {
    
    if((*arbol).destructor){
        (*arbol).destructor ((*nodo_borrar).elemento);
    }
    free (nodo_borrar);
    if (!padre) {
        (*arbol).nodo_raiz = NULL;
    } else {
        if ((*padre).izquierda == nodo_borrar){
            (*padre).izquierda = NULL;
        } else {
            (*padre).derecha = NULL;
        }
    }
}

/*
*   Precondiciones: Debe recibir un nodo_borrar valido (solo un hijo y != NULL), y un arbol valido.
*   Postcondiciones: Borrara el nodo recibido.
*/
void borrar_nodo_un_hijo (nodo_abb_t* padre, nodo_abb_t* nodo_borrar, abb_t* arbol) {
    
    int lado_hijo;
    if (!padre) {
        lado_hijo = NINGUNO;
    } else if ((*padre).izquierda == nodo_borrar) {
        lado_hijo = IZQUIERDO;
    } else {
        lado_hijo = DERECHO;
    }

    nodo_abb_t* aux = (*nodo_borrar).izquierda;
    if (!aux) aux = (*nodo_borrar).derecha;
    if ((*arbol).destructor) {
        (*arbol).destructor ((*nodo_borrar).elemento);
    }
    free (nodo_borrar);

    if (lado_hijo == NINGUNO){
        (*arbol).nodo_raiz = aux;
    } else if (lado_hijo == IZQUIERDO){
        (*padre).izquierda = aux;
    } else {
        (*padre).derecha = aux;
    }
}

/*
*   Precondiciones: Debe recibir un nodo_actual valido (!= NULL).
*   Postcondiciones: Devolvera el puntero al padre del nodo que es predecesor inorden.
*/
nodo_abb_t* buscar_padre_predecesor_inorden (nodo_abb_t* padre, nodo_abb_t* nodo_actual) {
    
    if (!(*nodo_actual).derecha) {
        return padre;
    }
    return buscar_padre_predecesor_inorden (nodo_actual,(*nodo_actual).derecha);
}

/*
*   Precondiciones: Debe recibir un nodo_borrar valido (dos hijos y != NULL), y un arbol valido.
*   Postcondiciones: Borrara el nodo recibido.
*/
void borrar_nodo_dos_hijos (nodo_abb_t* padre, nodo_abb_t* nodo_borrar, abb_t* arbol) {
    
    int lado;
    nodo_abb_t* padre_reemplazo = buscar_padre_predecesor_inorden (NULL, (*nodo_borrar).izquierda);
    nodo_abb_t* reemplazo;

    if (!padre) {
        lado = NINGUNO;
    } else if ((*padre).izquierda == nodo_borrar) {
        lado = IZQUIERDO;
    } else {
        lado = DERECHO;
    }

    if (!padre_reemplazo) {
        reemplazo = (*nodo_borrar).izquierda;
        (*reemplazo).derecha = (*nodo_borrar).derecha;
    } else {
        reemplazo = (*padre_reemplazo).derecha;
        (*padre_reemplazo).derecha = (*reemplazo).izquierda;
        (*reemplazo).izquierda = (*nodo_borrar).izquierda;
        (*reemplazo).derecha = (*nodo_borrar).derecha;
    }
    if (!padre) {
        (*arbol).nodo_raiz = reemplazo;
    } else {
        if (lado == IZQUIERDO) {
            (*padre).izquierda = reemplazo;
        } else {
            (*padre).derecha = reemplazo;
        }
    }

    if ((*arbol).destructor) {
        (*arbol).destructor ((*nodo_borrar).elemento);
    }
    free (nodo_borrar);

}

/*
*   Precondiciones: Debe recibir un nodo_actual valido (!= NULL) y un elemento que sea del mismo tipo que el resto de elementos.
*   Postcondiciones: Devolvera 0 en caso de poder borrar el elemento y -1 en caso contrario.
*/
int arbol_borrar_aux (nodo_abb_t* padre, nodo_abb_t* nodo_actual, void* elemento, abb_t* arbol){

    if(!nodo_actual){
        return -1;
    }

    int comparacion = (*arbol).comparador (elemento, (*nodo_actual).elemento);
    if (comparacion == 0){
        if (!(*nodo_actual).izquierda && !(*nodo_actual).derecha){
            borrar_nodo_hoja(padre, nodo_actual, arbol);
        } else if (((*nodo_actual).izquierda && !(*nodo_actual).derecha) || (!(*nodo_actual).izquierda && (*nodo_actual).derecha)){
            borrar_nodo_un_hijo (padre, nodo_actual, arbol);
        } else {
            borrar_nodo_dos_hijos (padre, nodo_actual, arbol);
        }
        return 0;
    } else if (comparacion < 0){
        return arbol_borrar_aux (nodo_actual, (*nodo_actual).izquierda, elemento, arbol);
    } else {
        return arbol_borrar_aux (nodo_actual, (*nodo_actual).derecha, elemento, arbol);
    }

}

int arbol_borrar(abb_t* arbol, void* elemento){
    if (!arbol || !elemento) {
        return -1;
    }

    return arbol_borrar_aux (NULL, (*arbol).nodo_raiz, elemento, arbol);

}

/******************************************************************************************* Arbol_buscar ********************************************************************************************/

/*
*   Precondiciones: Debe recibir un elemento del mismo tipo que el resto de elementos, y una funcion para compararlos.
*   Postcondiciones: Devolvera el puntero al elemento buscado.
*/
void* arbol_buscar_aux (nodo_abb_t* nodo_actual, void* elemento, abb_comparador comparador) {
    
    if (!nodo_actual){
        return NULL;
    }
    int comparacion = comparador (elemento, (*nodo_actual).elemento);
    if (comparacion == 0){
        return (*nodo_actual).elemento;
    } else if (comparacion > 0){
        return arbol_buscar_aux ((*nodo_actual).derecha, elemento, comparador);
    } else {
        return arbol_buscar_aux ((*nodo_actual).izquierda, elemento, comparador);
    }
    
}

void* arbol_buscar(abb_t* arbol, void* elemento){
    if(!arbol || !elemento){
        return NULL;
    }
    return arbol_buscar_aux ((*arbol).nodo_raiz, elemento, (*arbol).comparador);
}

/******************************************************************************************** Arbol_raiz *********************************************************************************************/

void* arbol_raiz(abb_t* arbol){
    
    if (!arbol){
        return NULL;
    }
    if (!(*arbol).nodo_raiz){
        return NULL;
    }
    return (*(*arbol).nodo_raiz).elemento;

}

/******************************************************************************************* Arbol_vacio *********************************************************************************************/

bool arbol_vacio(abb_t* arbol){
    if (!arbol) {
        return true;
    }
    return !(*arbol).nodo_raiz;
}

/****************************************************************************************** Arbol_recorrido ******************************************************************************************/

/*
*   Precondiciones: Debe recibir un nodo_actual valido (!= NULL), un array valido con su respectivo tamaño, y un recorrido valido (INORDEN, PREORDEN o POSTORDEN).
*   Postcondiciones: Recorrera el arbol de la forma recibida y escribira los elementos dentro del array.
*/
void arbol_recorrido_aux (nodo_abb_t* nodo_actual, void** array, size_t tamanio_array, size_t* contador, int recorrido) {

    if (*contador == tamanio_array){
        return;
    }

    if (recorrido == ABB_RECORRER_PREORDEN){
        array[*contador] = (*nodo_actual).elemento;
        (*contador) ++;
    }

    if ((*nodo_actual).izquierda) {
        arbol_recorrido_aux ((*nodo_actual).izquierda, array, tamanio_array, contador, recorrido);
    }

    if (*contador == tamanio_array){
        return;
    }

    if (recorrido == ABB_RECORRER_INORDEN){
        array[*contador] = (*nodo_actual).elemento;
        (*contador) ++;
    }

    if ((*nodo_actual).derecha) {
        arbol_recorrido_aux ((*nodo_actual).derecha, array, tamanio_array, contador, recorrido);
    }

    if (*contador == tamanio_array){
        return;
    }

    if (recorrido == ABB_RECORRER_POSTORDEN){
        array[*contador] = (*nodo_actual).elemento;
        (*contador) ++;
    }

}

/*
*   Precondiciones: Debe recibir un arbol valido (!= NULL), un array valido con su respectivo tamaño, y un recorrido valido (INORDEN, PREORDEN o POSTORDEN).
*   Postcondiciones: Devolvera la cantidad de elementos recorridos, ademasd de escribir los elementos dentro del array.
*/
size_t arbol_recorrido (abb_t* arbol, void** array, size_t tamanio_array, int recorrido){
    if(!arbol){
        return 0;
    }

    if(!(*arbol).nodo_raiz){
        return 0;
    }

    size_t cantidad = 0;
    arbol_recorrido_aux((*arbol).nodo_raiz, array, tamanio_array, &cantidad, recorrido);
    return cantidad;
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
    return arbol_recorrido (arbol, array, tamanio_array, ABB_RECORRER_INORDEN);
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
    return arbol_recorrido (arbol, array, tamanio_array, ABB_RECORRER_PREORDEN);
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
    return arbol_recorrido (arbol, array, tamanio_array, ABB_RECORRER_POSTORDEN);
}

/****************************************************************************************** Arbol_destruir *******************************************************************************************/

/*
*   Precondiciones: Debe recibir un nodo_valido (!= NULL)
*   Postcondiciones: Liberara todos los nodos y los elementos dentro de ellos (en caso de ser necesario).
*/
void arbol_destruir_aux (nodo_abb_t* nodo_actual, abb_liberar_elemento destructor) {
    if ((*nodo_actual).izquierda){
        arbol_destruir_aux((*nodo_actual).izquierda, destructor);
    }
    if ((*nodo_actual).derecha) {
        arbol_destruir_aux((*nodo_actual).derecha, destructor);
    }
    if (destructor) {
        destructor ((*nodo_actual).elemento);
    }
    free (nodo_actual);
}

void arbol_destruir(abb_t* arbol){

    if (!arbol){
        return;
    }
    
    if ((*arbol).nodo_raiz){
        arbol_destruir_aux ((*arbol).nodo_raiz, (*arbol).destructor);
    }

    free (arbol);
    return;
}

/************************************************************************************** Abb_con_cada_elemento ****************************************************************************************/

/*
*   Precondiciones: Debe recibir un nodo_actual valido (!= NULL), un recorrido valido (INORDEN, PREORDEN o POSTORDEN), y una funcion para recorrerlos.
*   Postcondiciones: Recorrera los elementos del arbol de la manera indicada hasta que la funcion recibida devuelva true.
*/
void abb_con_cada_elemento_aux (nodo_abb_t* nodo_actual, int recorrido, bool (*funcion)(void*, void*), void* extra, size_t* contador, bool *puede_seguir){
    
    if (recorrido == ABB_RECORRER_PREORDEN && *puede_seguir){
        (*contador) ++;
        if (funcion ((*nodo_actual).elemento, extra)){
            *puede_seguir = false;
            return;
        }
    }

    if ((*nodo_actual).izquierda) {
        abb_con_cada_elemento_aux((*nodo_actual).izquierda, recorrido, funcion, extra, contador, puede_seguir);
    }

    if (recorrido == ABB_RECORRER_INORDEN && *puede_seguir){
        (*contador) ++;
        if (funcion ((*nodo_actual).elemento, extra)){
            *puede_seguir = false;
            return;
        }
    }

    if ((*nodo_actual).derecha) {
        abb_con_cada_elemento_aux((*nodo_actual).derecha, recorrido, funcion, extra, contador, puede_seguir);
    }

    if (recorrido == ABB_RECORRER_POSTORDEN && *puede_seguir){
        (*contador) ++;
        if (funcion ((*nodo_actual).elemento, extra)){
            *puede_seguir = false;
            return;
        }
    }
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
    
    if (!arbol) {
        return 0;
    }
    if (!(*arbol).nodo_raiz) {
        return 0;
    }
    if (!funcion) {
        return 0;
    }
    if (recorrido != ABB_RECORRER_INORDEN && recorrido != ABB_RECORRER_POSTORDEN && recorrido != ABB_RECORRER_PREORDEN){
        return 0;
    }

    size_t cantidad = 0;
    bool puede_seguir = true;
    abb_con_cada_elemento_aux((*arbol).nodo_raiz, recorrido, funcion, extra, &cantidad, &puede_seguir);
    return cantidad;

}

/*****************************************************************************************************************************************************************************************************/