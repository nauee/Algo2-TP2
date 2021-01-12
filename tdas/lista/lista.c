#include "lista.h"
#include <stdlib.h>

/******************************************************************************************** Lista crear ********************************************************************************************/

lista_t* lista_crear(){
    
    lista_t* lista = malloc (sizeof(lista_t));
    if (lista != NULL) {
        (*lista).cantidad = 0;
        (*lista).nodo_fin = NULL;
        (*lista).nodo_inicio = NULL;
    }
    return lista;

}

/****************************************************************************************** Lista insertar *******************************************************************************************/

int lista_insertar(lista_t* lista, void* elemento){

    if (!lista){
        return -1;
    }

    return lista_insertar_en_posicion(lista, elemento, (*lista).cantidad);
}

/************************************************************************************ Lista insertar en posicion *************************************************************************************/

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion) {
    
    if (!lista) {
        return -1;
    }

    nodo_t* nodo = malloc (sizeof(nodo_t));
    if (nodo == NULL) {
            return -1;
    }
    (*nodo).elemento = elemento;

    if (posicion > (*lista).cantidad) {
        posicion = (*lista).cantidad;
    }

    if ((*lista).cantidad == 0){
        (*lista).nodo_fin = nodo;
        (*lista).nodo_inicio = nodo;
    } else if (posicion == 0) {
        (*nodo).siguiente = (*lista).nodo_inicio;
        (*lista).nodo_inicio = nodo;
    } else if (posicion == (*lista).cantidad) {
        (*(*lista).nodo_fin).siguiente = nodo;
        (*nodo).siguiente = NULL;
        (*lista).nodo_fin = nodo;
    } else {
        int i = 0;
        nodo_t* aux = (*lista).nodo_inicio;
        while (i < posicion - 1) {
            aux = (*aux).siguiente;
            i++;
        }
        (*nodo).siguiente = (*aux).siguiente;
        (*aux).siguiente = nodo;
    }

    ((*lista).cantidad) ++;
    return 0;

}

/******************************************************************************************* Lista borrar ********************************************************************************************/

int lista_borrar(lista_t* lista){

    if (!lista){
        return -1;
    }

    return lista_borrar_de_posicion(lista, (*lista).cantidad - 1);

}

/************************************************************************************* Lista borrar en posicion **************************************************************************************/

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){

    if (!lista) {
        return -1;
    }

    if ((*lista).cantidad == 0){
        return -1;
    }

    if (posicion >= (*lista).cantidad) {
        posicion = (*lista).cantidad - 1;
    }

    if (posicion == 0){
        nodo_t* tmp = (*lista).nodo_inicio;
        (*lista).nodo_inicio = (*tmp).siguiente;
        free (tmp);
        (*lista).cantidad --;
        return 0;
    }

    int i = 0;
    nodo_t* prev = (*lista).nodo_inicio;
    nodo_t* aux = (*lista).nodo_inicio;

    while (i < posicion) {
        prev = aux;
        aux = (*aux).siguiente;
        i++;
    }

    (*prev).siguiente = (*aux).siguiente;
    free(aux);
    if (!(*prev).siguiente) {
        ((*lista).nodo_fin) = prev;
    }
    ((*lista).cantidad) --;

    return 0;
}

/************************************************************************************ Lista elemento en posicion *************************************************************************************/

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    
    if (!lista) {
        return NULL;
    }

    if (posicion >= (*lista).cantidad) {
        return NULL;
    }

    if (posicion == 0){
        return (*(*lista).nodo_inicio).elemento;
    } else if (posicion == ((*lista).cantidad - 1)) {
        return (*(*lista).nodo_fin).elemento;
    }

    int i = 0;
    nodo_t* aux = (*lista).nodo_inicio;
    while (i <= posicion - 1) {
        aux = (*aux).siguiente;
        i++;
    }
    return (*aux).elemento;
}

/******************************************************************************************* Lista ultimo ********************************************************************************************/

void* lista_ultimo(lista_t* lista){
    
    if (!lista) {
        return NULL;
    }
    
    return lista_elemento_en_posicion(lista, (*lista).cantidad - 1 );
    
}

/******************************************************************************************** Lista vacia ********************************************************************************************/

bool lista_vacia(lista_t* lista){
    
    if(!lista) {
        return true;
    }
    return (*lista).cantidad == 0;
}

/****************************************************************************************** Lista elementos ******************************************************************************************/

size_t lista_elementos(lista_t* lista){
    
    if (!lista) {
        return 0;
    } else {
        return (*lista).cantidad;
    }
}

/******************************************************************************************* Lista apilar ********************************************************************************************/

int lista_apilar(lista_t* lista, void* elemento){
    
    if (!lista){
        return -1;
    }

    return lista_insertar_en_posicion(lista, elemento, 0);

}

/***************************************************************************************** Lista desapilar *******************************************************************************************/

int lista_desapilar(lista_t* lista){
    
    if (!lista) {
        return -1;
    }

    return lista_borrar_de_posicion (lista, 0);

}

/******************************************************************************************* Lista tope **********************************************************************************************/

void* lista_tope(lista_t* lista){
    
    if (!lista) {
        return NULL;
    }

    return lista_elemento_en_posicion(lista, 0);

}

/***************************************************************************************** Lista encolar *********************************************************************************************/

int lista_encolar(lista_t* lista, void* elemento){
    
    if (!lista){
        return -1;
    }

    return lista_insertar_en_posicion (lista, elemento, (*lista).cantidad);
}

/*************************************************************************************** Lista desencolar ********************************************************************************************/

int lista_desencolar(lista_t* lista){
    
    if (!lista) {
        return -1;
    }

    return lista_borrar_de_posicion (lista, 0);
}

/***************************************************************************************** Lista primero *********************************************************************************************/

void* lista_primero(lista_t* lista){
    
    if (!lista) {
        return NULL;
    }

    return lista_elemento_en_posicion (lista, 0);

}

/**************************************************************************************** Lista destruir *********************************************************************************************/

void lista_destruir(lista_t* lista){
    
    if(!lista) {
        return;
    }
    size_t cantidad_a_borrar = (*lista).cantidad;
    for(int i = 0; i < cantidad_a_borrar; i++){
        lista_borrar_de_posicion(lista,0);
    }
    free(lista);
}

/************************************************************************************* Lista iterador crear ******************************************************************************************/

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    
    if (!lista) {
        return NULL;
    }

    lista_iterador_t* iterador = malloc (sizeof(lista_iterador_t));
    if (iterador){
        (*iterador).corriente = (*lista).nodo_inicio;
        (*iterador).lista = lista;
    }
    return iterador;

}

/******************************************************************************** Lista iterador tiene siguiente *************************************************************************************/

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    
    if(!iterador) {
        return false;
    }
    return (*iterador).corriente != NULL;

}

/************************************************************************************ Lista iterador avanzar *****************************************************************************************/

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    
    if(!iterador) {
        return false;
    }

    if(!lista_iterador_tiene_siguiente(iterador)){
        return false;
    } else {
        (*iterador).corriente = (*(*iterador).corriente).siguiente;
        if (!(*iterador).corriente){
            return false;
        } else {
            return true;
        }
    }

}

/************************************************************************************ Lista iterador avanzar *****************************************************************************************/

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    if(!iterador) {
        return NULL;
    }
    if(!(*iterador).corriente){
        return NULL;
    }

    return ((*(*iterador).corriente).elemento);
}

/*********************************************************************************** Lista iterador destruir *****************************************************************************************/

void lista_iterador_destruir(lista_iterador_t* iterador){
    
    free (iterador);

}

/*********************************************************************************** Lista con cada elemento *****************************************************************************************/

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    
    if(!lista || !funcion){
        return 0;
    }

    nodo_t* recorrido = (*lista).nodo_inicio;
    if(!recorrido) {
        return 0;
    }
    size_t cant_recorrida = 1;

    while (funcion((*recorrido).elemento, contexto) && (*recorrido).siguiente) {
        recorrido = (*recorrido).siguiente;
        cant_recorrida ++;
    }

    return cant_recorrida;

}

/*****************************************************************************************************************************************************************************************************/