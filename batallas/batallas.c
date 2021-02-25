#include "batallas.h"
#include "../datos.h"

#define MAX_NOMBRE 25

int funcion_batalla_1(void* pkm_1, void* pkm_2) {
    
    pokemon_t pokemon_1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon_2 = *(pokemon_t*)pkm_2;

    int puntos_poke_1 = ((pokemon_1.ataque * 100) / (pokemon_1.defensa * 25)) + (pokemon_1.velocidad * 30);
    int puntos_poke_2 = ((pokemon_2.ataque * 100) / (pokemon_2.defensa * 25)) + (pokemon_2.velocidad * 30);

    if (puntos_poke_1 > puntos_poke_2) {
        return GANO_PRIMERO;
    } else if (puntos_poke_1 < puntos_poke_2) {
        return GANO_SEGUNDO;
    } else {
        if (pokemon_1.velocidad >= pokemon_2.velocidad) {
            return GANO_PRIMERO;
        } else {
            return GANO_SEGUNDO;
        }
    }

}

int funcion_batalla_2(void* pkm_1, void* pkm_2) {

    pokemon_t pokemon_1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon_2 = *(pokemon_t*)pkm_2;

    int puntos_poke_1 = ((pokemon_1.ataque * pokemon_1.velocidad * 5) / pokemon_1.defensa);
    int puntos_poke_2 = ((pokemon_2.ataque * pokemon_2.velocidad * 5) / pokemon_2.defensa);

    if (puntos_poke_1 > puntos_poke_2) {
        return GANO_PRIMERO;
    } else if (puntos_poke_1 < puntos_poke_2) {
        return GANO_SEGUNDO;
    } else {
        if (pokemon_1.velocidad >= pokemon_2.velocidad) {
            return GANO_PRIMERO;
        } else {
            return GANO_SEGUNDO;
        }
    }

}

int funcion_batalla_3(void* pkm_1, void* pkm_2) {

    pokemon_t pokemon_1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon_2 = *(pokemon_t*)pkm_2;

    int puntos_poke_1 = pokemon_1.ataque / 5;
    int puntos_poke_2 = pokemon_2.ataque / 5;

    if (puntos_poke_1 > puntos_poke_2) {
        return GANO_PRIMERO;
    } else if (puntos_poke_1 < puntos_poke_2) {
        return GANO_SEGUNDO;
    } else {
        if ((pokemon_1.defensa + pokemon_1.velocidad) >= (pokemon_2.defensa + pokemon_2.velocidad)) {
            return GANO_PRIMERO;
        } else {
            return GANO_SEGUNDO;
        }
    }

}

int funcion_batalla_4(void* pkm_1, void* pkm_2) {
    
    pokemon_t pokemon_1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon_2 = *(pokemon_t*)pkm_2;

    if ((pokemon_1.velocidad) > (pokemon_2.velocidad)) {
        return GANO_PRIMERO;
    } else if ((pokemon_1.velocidad) < (pokemon_2.velocidad)) {
        return GANO_SEGUNDO;
    } else {
        if ((pokemon_1.ataque) >= (pokemon_2.ataque)) {
            return GANO_PRIMERO;
        } else {
            return GANO_SEGUNDO;
        }
    }

}

int funcion_batalla_5(void* pkm_1, void* pkm_2) {

    pokemon_t pokemon_1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon_2 = *(pokemon_t*)pkm_2;

    int puntos_pokemon_1 = pokemon_1.ataque + pokemon_1.defensa + pokemon_1.velocidad;
    int puntos_pokemon_2 = pokemon_2.ataque + pokemon_2.defensa + pokemon_2.velocidad;

    if (puntos_pokemon_1 > puntos_pokemon_2) {
        return GANO_PRIMERO;
    } else if (puntos_pokemon_1 < puntos_pokemon_2) {
        return GANO_SEGUNDO;
    } else {
        if (pokemon_1.defensa >= pokemon_2.defensa) {
            return GANO_PRIMERO;
        } else {
            return GANO_SEGUNDO;
        }
    }

}