#ifndef __GIMNASIOS_H__
#define __GIMNASIOS_H__

#include "../tdas/heap/heap.h"

/******************************************* Funciones *******************************************/

/*
*   Precondiciones: Debe recibir una ruta valida y un heap de gimnasios inicializado.
*   Postcondicones: Agregara al heap de gimnasios los gimnasios leidos en el archivo ubicado en la ruta.
*/
void cargar_gimnasios (char* ruta, heap_t* gimnasios);

#endif /*__GIMNASIOS_H__*/

/*************************************************************************************************/