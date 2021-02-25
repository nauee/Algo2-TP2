#ifndef __INTERFACES_H__
#define __INTERFACES_H__

#include "../datos.h"

/*
*   Precondiciones: Debe recibir un personaje valido
*   Postcondiciones: Mostrara por pantalla la informacion del personaje.
*/
void mostrar_personaje (personaje_t personaje);

/*
*   Precondiciones: Debe recibir dos pokemones validos.
*   Postcondiciones: Mostrara por pantalla la informacion de la batalla entre los pokemones.
*/
void mostrar_batalla (pokemon_t pkm_1, pokemon_t pkm_2);

/*
*   Precondiciones: Debe recibir el nombre del pokemon ganador y perdedor y sus entrenadores, todos validos.
*   Postcondiciones: Mostrara por pantalla el pokemon ganador de la batalla.
*/
void mostrar_pokemon_ganador (char* pkm_ganador, char* pj_ganador, char* pkm_perdedor, char* pj_perdedor);

/*
*   Precondiciones: Debe recibir el nombre del entrenador ganador y del perdedor.
*   Postcondiciones: Mostrara por pantalla el entrenador ganador de la batalla.
*/
void mostrar_entrenador_ganador (char* ganador, char* perdedor);

/*
*   Precondiciones: Debe recibir un lider con sus estructuras validas.
*   Postcondiciones: Mostrara el menu para poder elegir un pokemon del lider.
*/
void mostrar_menu_elegir_pokemon_lider (entrenador_t lider) ;

/*
*   Precondiciones: Debe recibir un bool que indique si el jugador ya tomo un pokemon del lider o no.
*   Postcondiciones: Mostrara el menu que aparece luego de ganar un gimnasio.
*/
void mostrar_menu_victoria (bool tomo_pokemon_lider);

/*
*   Postcondiciones: Mostrara el menu que aparece luego de perder un gimnasio.
*/
void mostrar_menu_derrota ();

/*
*   Precondiciones: Debe recibir un personaje con sus estructuras validas, y un bool que indique si el jugador esta
*   ingresando el numero del primer pokemon o del segundo.
*   Postcondiciones: Mostrara por pantalla el menu donde aparece el equipo del personaje donde podra rearmarlo.
*/
void mostrar_menu_rearmar_equipo (personaje_t personaje, bool es_primer_pkm);

/*
*   Postcondiciones: Mostrara por pantalla que se ha ganado el gimnasio.
*/
void mostrar_victoria (char* nombre_personaje, char* nombre_gimnasio);

/*
*   Postcondiciones: Mostrara por pantalla que se ha perdido el gimnasio.
*/
void mostrar_derrota (char* nombre_personaje, char* nombre_gimnasio);

/*
*   Precondiciones: Debe recibir un gimnasio valido y una lista con los entrenadores que se hayan vencido.
*   Postcondiciones: Mostrara la informacion del gimnasio.
*/
void mostrar_gimnasio (gimnasio_t gimnasio, lista_t* entrenadores_vencidos);

/*
*   Precondiciones: Debe recibir un nombre de gimnasio valido.
*   Postcondiciones: Mostrara el menu que aparece luego de ganar un gimnasio.
*/
void mostrar_menu_gimnasio (char* nombre_gimnasio);

/*
*   Postcondiciones: Mostrara un mensaje de cargando
*/
void mostrar_cargando ();

/*
*   Postcondiciones: Mostrara por pantalla que se ha ganado el juego.
*/
void mostrar_victoria_juego ();

/*
*   Postcondiciones: Mostrara por pantalla que se ha perdido el juego.
*/
void mostrar_derrota_juego ();

/*
*   Precondiciones: Debe recibir un bool que indique si el jugador ya ha elegido un personaje.
*   Postcondiciones: Mostrara por pantalla el menu que aparece al comenzar el juego.
*/
void mostrar_menu_inicio(bool personaje_seleccionado);

/*
*   Precondiciones: Debe recibir el nombre del gimnasio a presentar valido. 
*   Postcondiciones: Mostrara por pantalla el proximo gimnasio al cual se enfrentara el jugador.
*/
void mostrar_presentacion_gimnasio (char* gimnasio);

#endif /* __INTERFACES_H__ */