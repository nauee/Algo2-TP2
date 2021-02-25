#ifndef __BATALLAS_H__
#define __BATALLAS_H__

#define GANO_PRIMERO 1
#define GANO_SEGUNDO -1

/*
 * Se deberan implementar las 5 funciones de batalla.
 * Las reglas para decidir al ganador las inventan ustedes
 * 
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 * 
 * No habran empates.
 */

/*
*   Precondiciones: Debe recibir dos pokemones validos.
*   Postcondiciones: Devolvera GANO_PRIMERO o GANO_SEGUNDO segun quien sea el ganador de la batalla determinado por la formula.
*   Formula: ((Ataque * 100) / Defensa * 25) + (Velocidad * 30)
*/
int funcion_batalla_1(void* pkm_1, void* pkm_2);

/*
*   Precondiciones: Debe recibir dos pokemones validos.
*   Postcondiciones: Devolvera GANO_PRIMERO o GANO_SEGUNDO segun quien sea el ganador de la batalla determinado por la formula.
*   Formula: ((Ataque * Velocidad * 5) / Defensa)
*/
int funcion_batalla_2(void* pkm_1, void* pkm_2);

/*
*   Precondiciones: Debe recibir dos pokemones validos.
*   Postcondiciones: Devolvera GANO_PRIMERO o GANO_SEGUNDO segun quien sea el ganador de la batalla determinado por la formula.
*   Formula: (Ataque / 5)
*/
int funcion_batalla_3(void* pkm_1, void* pkm_2);

/*
*   Precondiciones: Debe recibir dos pokemones validos.
*   Postcondiciones: Devolvera GANO_PRIMERO o GANO_SEGUNDO segun quien sea el ganador de la batalla determinado por quien sea mas rapido.
*/
int funcion_batalla_4(void* pkm_1, void* pkm_2);

/*
*   Precondiciones: Debe recibir dos pokemones validos.
*   Postcondiciones: Devolvera GANO_PRIMERO o GANO_SEGUNDO segun quien sea el ganador de la batalla determinado por la formula.
*   Formula: (Ataque + Defensa + Velocidad)
*/
int funcion_batalla_5(void* pkm_1, void* pkm_2);


#endif /* __BATALLAS_H__ */