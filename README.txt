*************************************************************** Nahuel Castro 106551 ****************************************************************

Acerca de la entrega:
    La entrega consiste en un juego sobre convertirse en maestro Pokemon, en el cual tendras que enfrentarte a los gimnasios con tu equipo de pokemones.

Linea de compilacion:
    Puede compilarse escribiendo make (compila con mis pruebas).
    En caso de querer ingresar la linea completa, es la siguiente:
    -> gcc juego.c tdas/*/*.c gimnasios/gimnasios.c batallas/batallas.c personaje/personaje.c interfaces/interfaces.c -g -std=c99 -Wall -Werror -Wconversion -o juego.

Linea de ejecucion:
    Puede ejecutarse escribiendo make ejecutar.
    En caso de querer ingresar la linea completa, es la siguiente:
    -> ./juego.

Lineas extras:
    -> Utilizando make probar puede ejecutar valgrind con el juego.


Aclaraciones sobre funcionamiento:
     -> Se utilizó un heap minimal para organizar los gimnasios de manera que el proximo gimnasio sea siempre el mas facil.
     -> Dentro de la estructura de gimnasios se utilizo una pila de entrenadores de manera que al leer el entrenador sea el primero en entrar y al batallar sea el ultimo en salir.
     -> Los pokemones de batalla de los entrenadores y del personaje estan guardados en listas para poder recorrerlos usando el iterador al momento de pelear.
     -> Los pokemones obtenidos del personaje estan guardados en una lista para facilitar la insercion de pokemones y para no tener un limite en la cantidad de pokemones.
     -> En caso de que el usuario no ingrese gimnasios o un personaje, el juego cargara automaticamente los predeterminados (los archivos de los predeterminados
        se encuentran dentro de la carpeta src)
     -> Si el usuario pierde en un gimnasio, los entrenadores vencidos no volveran a ser enfrentados.
     -> El juego no cargara ningun dato si no cumple con el formato siguiente:
         -> Gimnasios: G;nombre_gimnasio; dificultad; id_puntero_funcion
         -> Lideres: L;nombre_lider
         -> Entrenadores: E;nombre_entrenador
         -> Pokemones: P;nombre_pokemon2; velocidad; ataque; defensa
        Por lo que la ausencia de alguno de los datos incluidos en el formato hara que no se cargue esa linea.
        Ademas si alguno de los datos es invalido, por ejemplo una velocidad es negativa, tampoco se cargara esa linea.
        Tampoco se cargaran gimnasios vacios o sin lider, o entrenadores sin pokemones.
        Aun asi, se seguira leyendo el archivo para intentar cargar todo lo posible.
     -> Cada entrenador de los gimnasios tiene un maximo de 6 pokemones al igual que en los juegos originales.

*****************************************************************************************************************************************************