*************************************************************** Nahuel Castro 106551 ****************************************************************

Acerca de la entrega:
    La entrega consiste en una implementacion de un heap utilizando su representacion como vector.
    Cuenta con las siguientes funciones:
     -> heap_crear
     -> heap_insertar
     -> heap_ver_raiz
     -> heap_eliminar_raiz
     -> heap_destruir

Linea de compilacion:
    -> gcc heap.c testing/pruebas.c -o test -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 (para compilar con mis pruebas).

Linea de ejecucion:
    -> ./test (ejecuta con mis pruebas).

Aclaraciones sobre funcionamiento:
     -> El heap necesita un comparador para comparar los elementos que se le inserten.
     -> El heap no libera la memoria reservada por los elementos que se le inserten, solo libera la memoria reservada por el heap para funcionar,
        el usuario debera liberar los elementos que ingrese en caso de ser necesario.

*****************************************************************************************************************************************************