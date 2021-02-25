#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "gimnasios/gimnasios.h"
#include "personaje/personaje.h"
#include "batallas/batallas.h"
#include "interfaces/interfaces.h"

/****************************************** Constantes *******************************************/

#define GANO 1
#define PELEANDO 0
#define PERDIO -1
#define REINTENTAR -2
#define MAX_FUNCIONES 5
#define AMARILLO "\033[1;33m"
#define NORMAL "\033[0m \033[39m"
#define MAX_LINEA 66
#define MAX_LINEA_MENU 100
#define MAX_RUTA 100

/******************************************* Funciones *******************************************/

/*
*	Postcondiciones: Limpiara el buffer de entrada del programa.
*/
void limpiar_buffer (){
	char c;
	while ((c = (char) getchar()) != '\n' && c != EOF);
}

/*
*	Precondiciones: Debe recibir dos punteros a gimnasios validos.
*	Postcondiciones: Devolvera 0 si los gimnasios son iguales, -1 si el gimnasio1 es mas dificil y 1 si el gimnasio2 es mas dificil.
*/
int comparador_gimnasios (void* gimnasio1, void* gimnasio2) {
    if ((*(gimnasio_t*)gimnasio1).dificultad == (*(gimnasio_t*)gimnasio2).dificultad) {
        return 0;
    } else if ((*(gimnasio_t*)gimnasio1).dificultad > (*(gimnasio_t*)gimnasio2).dificultad) {
        return -1;
    } else {
        return 1;
    }
}

/*
*	Precondiciones: Debe recibir un vector de punteros a funciones de batalla vacio.
*	Postcondiciones: Asignara las diferentes funciones de batalla al vector.
*/
void asignar_funciones_batalla (int (*funciones_batalla[MAX_FUNCIONES]) (void*, void*)) {
	funciones_batalla [0] = funcion_batalla_1;
	funciones_batalla [1] = funcion_batalla_2;
	funciones_batalla [2] = funcion_batalla_3;
	funciones_batalla [3] = funcion_batalla_4;
	funciones_batalla [4] = funcion_batalla_5;
}

/*
*	Precondiciones: Debe recibir un pokemon valido.
*	Postcondiciones: Aumentara en 1 todas las stats del pokemon, siempre y cuando sea posible.
*/
void aumentar_stats (pokemon_t* pokemon) {
	if ((*pokemon).puntos_de_mejora > 0) {
		((*pokemon).velocidad) ++;
		((*pokemon).ataque) ++;
		((*pokemon).defensa) ++;
		((*pokemon).puntos_de_mejora) --;
	}
}

/*
*	Precondiciones: Debe recibir un entrenador y un personaje validos, un id_funcion_batalla valido (entre 1 y 5) y un bool que
*	indique si se esta simulando el juego o no.
*	Postcondiciones: Enfrentara al entrenador y devolvera true si se gano el combate y false en caso contrario.
*/
bool enfrentar_entrenador (entrenador_t* entrenador, personaje_t* personaje, int id_funcion_batalla, bool es_simulacion) {
	int estado_batalla = PELEANDO;
	lista_iterador_t* it_entrenador = lista_iterador_crear ((*entrenador).pokemon);
	lista_iterador_t* it_personaje = lista_iterador_crear ((*personaje).pokemon_para_combatir);
	int (*funciones_batalla[MAX_FUNCIONES]) (void*, void*);
	asignar_funciones_batalla (funciones_batalla);
	while (estado_batalla == PELEANDO) {

		mostrar_batalla (*(pokemon_t*)lista_iterador_elemento_actual (it_personaje), *(pokemon_t*)lista_iterador_elemento_actual (it_entrenador));
		if (funciones_batalla [id_funcion_batalla - 1] (lista_iterador_elemento_actual (it_personaje), lista_iterador_elemento_actual (it_entrenador)) == GANO_PRIMERO) {
			mostrar_pokemon_ganador ((*(pokemon_t*)lista_iterador_elemento_actual (it_personaje)).nombre, (*personaje).nombre, (*(pokemon_t*)lista_iterador_elemento_actual (it_entrenador)).nombre, (*entrenador).nombre);
			lista_iterador_avanzar (it_entrenador);
			aumentar_stats ((pokemon_t*) lista_iterador_elemento_actual (it_personaje));
		} else {
			mostrar_pokemon_ganador ((*(pokemon_t*)lista_iterador_elemento_actual (it_entrenador)).nombre, (*entrenador).nombre, (*(pokemon_t*)lista_iterador_elemento_actual (it_personaje)).nombre, (*personaje).nombre);
			lista_iterador_avanzar (it_personaje);
		}

		if (!es_simulacion) {
			printf(AMARILLO" Presiona ENTER para continuar "NORMAL);
			getchar ();
		} else {
			sleep (2);
		}
		system ("clear");
		
		if (!lista_iterador_tiene_siguiente (it_entrenador)) {
			estado_batalla = GANO;
			mostrar_entrenador_ganador ((*personaje).nombre, (*entrenador).nombre);
			if (!es_simulacion) {
				printf(AMARILLO" Presiona ENTER para continuar "NORMAL);
				getchar ();
			} else {
				sleep (2);
			}
			system ("clear");
		} else if (!lista_iterador_tiene_siguiente (it_personaje)) {
			estado_batalla = PERDIO;
			mostrar_entrenador_ganador((*entrenador).nombre, (*personaje).nombre);
			if (!es_simulacion) {
				printf(AMARILLO" Presiona ENTER para continuar "NORMAL);
				getchar ();
			} else {
				sleep (2);
			}
			system ("clear");
		}

	}
	lista_iterador_destruir (it_entrenador);
	lista_iterador_destruir (it_personaje);
	return (estado_batalla == GANO);
}

/*
*	Precondiciones: Debe recibir un personaje y un lider validos.
*	Postcondiciones: Permitira al jugador elegir un pokemon del lider para "pedirlo prestado".
*/
void elegir_pokemon_lider (personaje_t* personaje, entrenador_t* lider) {
	int opcion_seleccionada = 0;
	mostrar_menu_elegir_pokemon_lider(*lider);
	scanf (" %i", &opcion_seleccionada);
	while (opcion_seleccionada < 0 || opcion_seleccionada >= lista_elementos ((*lider).pokemon)) {
		printf("               Esa opcion no es valida               ");
		printf("\n                          ");
		scanf (" %i", &opcion_seleccionada);
	}
	
	lista_insertar ((*personaje).pokemon_obtenidos, lista_elemento_en_posicion ((*lider).pokemon, (size_t) opcion_seleccionada));
	lista_borrar_de_posicion ((*lider).pokemon, (size_t) opcion_seleccionada);
}

/*
*	Precondiciones: Debe recibir un personaje con sus estructuras validas.
*	Postcondiciones: Permitira al jugador rearmar su equipo.
*/
void rearmar_equipo (personaje_t* personaje) {
	int pos_pkm_1;
	int pos_pkm_2;
	mostrar_menu_rearmar_equipo(*personaje, true);
	scanf (" %i", &pos_pkm_1);
	while (pos_pkm_1 < 0 || pos_pkm_1 > lista_elementos ((*personaje).pokemon_obtenidos)) {
		printf("               Esa opcion no es valida               ");
		printf("\n                         ");
		scanf (" %i", &pos_pkm_1);
	}
	limpiar_buffer ();
	if (pos_pkm_1 == 0) return;

	mostrar_menu_rearmar_equipo(*personaje, false);
	scanf (" %i", &pos_pkm_2);
	while (pos_pkm_2 < 0 || pos_pkm_2 > lista_elementos ((*personaje).pokemon_obtenidos)) {
		printf("               Esa opcion no es valida               ");
		printf("\n                         ");
		scanf (" %i", &pos_pkm_2);
	}
	limpiar_buffer ();
	if (pos_pkm_2 == 0) return;

	pokemon_t* pkm_1 = (pokemon_t*) lista_elemento_en_posicion ((*personaje).pokemon_obtenidos, (size_t) pos_pkm_1 - 1);
	pokemon_t* pkm_2 = (pokemon_t*) lista_elemento_en_posicion ((*personaje).pokemon_obtenidos, (size_t) pos_pkm_2 - 1);
	pokemon_t aux = *pkm_1;
	*pkm_1 = *pkm_2;
	*pkm_2 = aux;
	rearmar_equipo (personaje);

}

/*
*	Precondiciones: Debe recibir un personaje y un lider validos, un nombre de gimnasio valido, un bool que indique si
*	se esta simulando el juego, y un bool que indique si el jugador ya tomo un pokemon del lider.
*	Postcondiciones: Permitira al usuario elegir que hacer luego de ganar un gimnasio, las opciones seran:
*	elegir un pokemon del lider, rearmar el equipo, o continuar con el juego.
*/
void ganar_gimnasio (personaje_t* personaje, entrenador_t* lider, char* nombre_gimnasio, bool es_simulacion, bool tomo_pokemon_lider) {
	if (es_simulacion) {
		mostrar_victoria((*personaje).nombre, nombre_gimnasio);
		return;
	}
	char opcion_seleccionada = ' ';
	mostrar_victoria((*personaje).nombre, nombre_gimnasio);
	mostrar_menu_victoria(tomo_pokemon_lider);
	scanf (" %c", &opcion_seleccionada);
	while (opcion_seleccionada != 'T' && opcion_seleccionada != 'C' && opcion_seleccionada != 'N') {
		printf("                                            Esa opcion no es valida                                             ");
		printf("\n                                                  ");
		scanf (" %c", &opcion_seleccionada);
	}
	limpiar_buffer ();
    if (opcion_seleccionada == 'T') {
        elegir_pokemon_lider (personaje, lider);
		ganar_gimnasio (personaje, lider, nombre_gimnasio, es_simulacion, true);
    } else if (opcion_seleccionada == 'C') {
        rearmar_equipo (personaje);
		ganar_gimnasio (personaje, lider, nombre_gimnasio, es_simulacion, tomo_pokemon_lider);
    } else if (opcion_seleccionada == 'N') {
		return;
	}
}

/*
*	Precondiciones: Debe recibir un personaje valido, un nombre de gimnasio valido, y un bool que indique si se esta
*	simulando el juego.
*	Postcondiciones: Permitira al usuario elegir que hacer luego de perder un gimnasio, las opciones seran:
*	rearmar el equipo, reintentar el gimnasio, o finalizar el juego.
*/
int perder_gimnasio (personaje_t* personaje, char* nombre_gimnasio, bool es_simulacion) {
	if (es_simulacion) {
		mostrar_derrota ((*personaje).nombre, nombre_gimnasio);
		return PERDIO;
	}
	char opcion_seleccionada = ' ';
	mostrar_derrota ((*personaje).nombre, nombre_gimnasio);
	mostrar_menu_derrota();
	scanf (" %c", &opcion_seleccionada);
	while (opcion_seleccionada != 'C' && opcion_seleccionada != 'R' && opcion_seleccionada != 'F') {
		printf("                                            Esa opcion no es valida                                             ");
		printf("\n                                                  ");
		scanf (" %c", &opcion_seleccionada);
	}
	limpiar_buffer();
    if (opcion_seleccionada == 'C') {
		rearmar_equipo (personaje);
		return perder_gimnasio (personaje, nombre_gimnasio, es_simulacion);
    } else if (opcion_seleccionada == 'R'){
		return REINTENTAR;
	} else {
        return PERDIO;
    }
}

void menu_gimnasio (gimnasio_t gimnasio, lista_t* entrenadores_vencidos, personaje_t* personaje) {
	char opcion_seleccionada = ' ';
	mostrar_menu_gimnasio(gimnasio.nombre);
	scanf (" %c", &opcion_seleccionada);
	while (opcion_seleccionada != 'E' && opcion_seleccionada != 'G' && opcion_seleccionada != 'C' && opcion_seleccionada != 'B') {
		printf("                                            Esa opcion no es valida                                             ");
		printf("\n                                                        ");
		scanf (" %c", &opcion_seleccionada);
	}
	limpiar_buffer();
	if (opcion_seleccionada == 'E') {
		mostrar_personaje (*personaje);
		menu_gimnasio (gimnasio, entrenadores_vencidos, personaje);
	} else if (opcion_seleccionada == 'G') {
		mostrar_gimnasio (gimnasio, entrenadores_vencidos);
		menu_gimnasio (gimnasio, entrenadores_vencidos, personaje);
	} else if (opcion_seleccionada == 'C') {
		rearmar_equipo (personaje);
		menu_gimnasio (gimnasio, entrenadores_vencidos, personaje);
	} else if (opcion_seleccionada == 'B'){
		return;
	}
}

void liberar_entrenadores_vencidos (lista_t* entrenadores_vencidos) {
	while (lista_elementos(entrenadores_vencidos) > 0) {
		entrenador_t* entrenador_borrar = (entrenador_t*) lista_primero (entrenadores_vencidos);
		while (!lista_vacia ((*entrenador_borrar).pokemon)){
            free ((lista_primero((*entrenador_borrar).pokemon)));
            lista_borrar_de_posicion((*entrenador_borrar).pokemon, 0);
		}
		lista_destruir ((*entrenador_borrar).pokemon);
		free (entrenador_borrar);
		lista_borrar_de_posicion (entrenadores_vencidos, 0);
	}
	lista_destruir (entrenadores_vencidos);
}

int enfrentar_gimnasio (gimnasio_t* gimnasio, personaje_t* personaje, bool es_simulacion) {
	int estado_batalla = PELEANDO;
	lista_t* entrenadores_vencidos = lista_crear ();
	entrenador_t* proximo_entrenador = (entrenador_t*) lista_tope ((*gimnasio).entrenadores);
	if (!enfrentar_entrenador (proximo_entrenador, personaje, (*gimnasio).id_funcion_batalla, es_simulacion)){
		estado_batalla = PERDIO;
	}
	while (estado_batalla == PELEANDO) {
		lista_apilar (entrenadores_vencidos, proximo_entrenador);
		lista_desapilar ((*gimnasio).entrenadores);
		proximo_entrenador = (entrenador_t*) lista_tope ((*gimnasio).entrenadores);
		if (!proximo_entrenador) {
			estado_batalla = GANO;
		}
		if (proximo_entrenador) {
			if (!es_simulacion) {
				menu_gimnasio ((*gimnasio), entrenadores_vencidos, personaje);
			}
			if (!enfrentar_entrenador (proximo_entrenador, personaje, (*gimnasio).id_funcion_batalla, es_simulacion)){
				estado_batalla = PERDIO;
			}
		}
	}

	if (estado_batalla == GANO) {
		ganar_gimnasio (personaje, (entrenador_t*)(lista_tope (entrenadores_vencidos)), (*gimnasio).nombre, es_simulacion, false);
		liberar_entrenadores_vencidos (entrenadores_vencidos);
	} else {
		estado_batalla = perder_gimnasio (personaje, (*gimnasio).nombre, es_simulacion);
	}

	return estado_batalla;
}

void eliminar_gimnasio (heap_t* gimnasios) {
	gimnasio_t* gimnasio_borrar = (gimnasio_t*) heap_ver_raiz (gimnasios);
	lista_destruir ((*gimnasio_borrar).entrenadores);
	free (gimnasio_borrar);
	heap_eliminar_raiz (gimnasios);
} 

void enfrentar_gimnasios (heap_t* gimnasios, personaje_t* personaje, bool es_simulacion) {
	system("clear");
	int estado_batalla = PELEANDO;
	gimnasio_t* proximo_gimnasio = (gimnasio_t*) heap_ver_raiz (gimnasios);
	if (proximo_gimnasio) {
		mostrar_presentacion_gimnasio ((*proximo_gimnasio).nombre);
		estado_batalla = enfrentar_gimnasio (proximo_gimnasio, personaje, es_simulacion);
		if (estado_batalla == GANO) {
			estado_batalla = PELEANDO;
		}
	}
    while (estado_batalla == PELEANDO || estado_batalla == REINTENTAR) {
		mostrar_cargando ();
		if (estado_batalla == PELEANDO) {
			eliminar_gimnasio (gimnasios);
		} else {
			estado_batalla = PELEANDO;
		}
		proximo_gimnasio = (gimnasio_t*) heap_ver_raiz (gimnasios);
		if (!proximo_gimnasio) {
			estado_batalla = GANO;
		}
		if (proximo_gimnasio) {
			mostrar_presentacion_gimnasio ((*proximo_gimnasio).nombre);
			estado_batalla = enfrentar_gimnasio (proximo_gimnasio, personaje, es_simulacion);
			if (estado_batalla == GANO) {
				estado_batalla = PELEANDO;
			}
		}
    }
	if (estado_batalla == PERDIO) {
		mostrar_derrota_juego ();
	} else if (estado_batalla == GANO) {
		mostrar_victoria_juego ();
	}
}

void jugar_juego (heap_t* gimnasios, personaje_t** personaje, bool es_simulacion) {
	if (!(*personaje)) {
		*personaje = cargar_personaje ("src/Personaje.txt");
	}
	if (!(heap_ver_raiz (gimnasios))) {
		cargar_gimnasios ("src/GimnasiosKanto.txt", gimnasios);
	}
    enfrentar_gimnasios (gimnasios, *personaje, es_simulacion);
}

personaje_t* crear_entrenador (personaje_t* personaje) {
	char ruta[MAX_RUTA];
	printf ("Inserte la ruta del personaje: ");
	scanf (" %[^\n]", ruta);
	limpiar_buffer ();
	return cargar_personaje (ruta);
}

void agregar_nuevo_gimnasio (heap_t* gimnasios) {
	char ruta[MAX_RUTA];
	printf ("Inserte la ruta del gimnasio: ");
	scanf ("%s", ruta);
	cargar_gimnasios (ruta, gimnasios);
}

void menu_inicio(heap_t* gimnasios, personaje_t** personaje){
	
	char opcion_seleccionada = ' ';
	bool personaje_seleccionado = (*personaje != NULL);
	mostrar_menu_inicio (personaje_seleccionado);
	scanf (" %c", &opcion_seleccionada);
	while (opcion_seleccionada != 'I' && opcion_seleccionada != 'S' && opcion_seleccionada != 'E' && opcion_seleccionada != 'A') {
		printf("               Esa opcion no es valida               ");
		printf("\n                          ");
		scanf (" %c", &opcion_seleccionada);
	}
	limpiar_buffer();
    if (opcion_seleccionada == 'I') {
        jugar_juego (gimnasios, personaje, false);
    } else if (opcion_seleccionada == 'S') {
        jugar_juego (gimnasios, personaje, true);
    } else if (opcion_seleccionada == 'E') {
        (*personaje) = crear_entrenador (*personaje);
		if (*personaje == NULL) {
			printf ("Ha ocurrido un ERROR al seleccionar tu personaje, presiona ENTER para continuar\n");
			getchar ();
		}
		menu_inicio (gimnasios, personaje);
    } else if (opcion_seleccionada == 'A') {
        agregar_nuevo_gimnasio (gimnasios);
		menu_inicio (gimnasios, personaje);
    }
}

void liberar_datos (heap_t* gimnasios, personaje_t* personaje) {
	while ((heap_ver_raiz(gimnasios) != NULL)) {
		eliminar_gimnasio (gimnasios);
	}
	heap_destruir (gimnasios);

	while (lista_elementos ((*personaje).pokemon_obtenidos) > 0) {
		free (lista_primero((*personaje).pokemon_obtenidos));
		lista_borrar_de_posicion((*personaje).pokemon_obtenidos, 0);
	}
	lista_destruir ((*personaje).pokemon_para_combatir);
	lista_destruir ((*personaje).pokemon_obtenidos);
	free (personaje);

}

int main () {
	heap_t* gimnasios = heap_crear (comparador_gimnasios);
	personaje_t* personaje = NULL;
    menu_inicio(gimnasios, &personaje);
	liberar_datos (gimnasios, personaje);
    return 0;
}

/*************************************************************************************************/