*************************************************** Nahuel Castro 106551 ***************************************************

Acerca de la entrega:
    La entrega consiste en un Arbol Binario de Busqueda (ABB), el cual esta implementado mediante nodos.
    Tambien contiene funcionalidades de iteradores.
    Cuenta con las siguientes funciones:
     -> arbol_crear
     -> arbol_insertar
     -> arbol_borrar
     -> arbol_buscar
     -> arbol_raiz
     -> arbol_vacio
     -> arbol_recorrido_inorden 
     -> arbol_recorrido_preorden
     -> arbol_recorrido_postorden
     -> arbol_destruir
     -> abb_con_cada_elemento (iterador interno)
    Ademas cuenta con pruebas para verificar el correcto funcionamiento del mismo.

Linea de compilacion:
    Puede compilarse escribiendo make (compila con mis pruebas) o make_minipruebas (compila con las minipruebas).
    En caso de querer ingresar la linea completa, es la siguiente:
    -> gcc abb.c pruebas.c -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o abb (para compilar con mis pruebas).
    -> gcc gcc abb.c abb_minipruebas.c -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -o minipruebas (para compilar con las minipruebas).

Linea de ejecucion:
    Puede ejecutarse escribiendo make ejecutar (ejecuta con mis pruebas) o make ejecutar_minipruebas (ejecuta con las minipruebas).
    En caso de querer ingresar la linea completa, es la siguiente:
    -> ./abb (ejecuta con mis pruebas).
    -> ./minipruebas (ejecuta con las minipruebas).

Lineas extras:
    -> Utilizando make probar o make probar_minipruebas puede ejecutar valgrind con mis pruebas o las minipruebas respectivamente.
    -> Utilizando make debug o make debug_minipruebas puede ejecutar gdb con mis pruebas o las minipruebas respectivamente.

Explicaciones:
    Explicar qué es un ABB y cómo se diferencia de un Árbol Binario.
        Un arbol binario es una estructura de datos, compuesta por nodos, en donde cada 
        nodo puede tener hasta 2 hijos (izquierdo y derecho). El nodo que no tiene padre,
        se lo conoce como nodo raiz, ademas los nodos que no tienen hijos se los conoce como
        nodos hoja. Un arbol binario de busqueda (ABB) es un tipo de arbol binario en donde
        todos los elementos almacenados en los nodos a la izquierda de cualquier nodo son menores que
        dicho nodo, y todos los elementos almacenados a la derecha son mayores que dicho nodo.
    Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuario no tenerla.
        La ventaja de tener esta funcion es que el usuario puede insertar cualquier dato en el arbol
        y no tiene que hacerse cargo de liberarlos antes de eliminarlos del arbol, simplemente la propia
        implementacion del arbol los libera en el momento de borrarlos. Sin esta funcion el arbol no podria liberar
        el dato porque no sabe como liberarlo.
    ¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique.
        Crear : O(1) simplemente reserva memoria para el arbol, por lo que es constante.
        Borrar : O(n), esta complejidad sera O(n) porque en el peor de los casos, el arbol
            degenerara en lista, por lo que deberemos recorrer los elementos linealmente
            para encontrar donde insertar.
            Si tomamos solo arboles balanceados, la complejidad se mantendra en O(logn)
            porque siempre dividimos el espacio de busqueda del elemento a borrar en 2.
        Busqueda : O(n), al igual que para borrar, en el peor de los casos el arbol degenerara
            en lista, por lo que deberemos recorrer los elementos linealmente. En el caso
            de arboles balanceados, la complejidad sera O(logn), porque siempre dividimos
            el espacio de busqueda en 2.
        Insertar : O(n), al igual que para borrar, en el peor de los casos el arbol degenerara
            en lista, por lo que deberemos recorrer los elementos linealmente para encontrar
            donde insertar. En el caso de arboles balanceados, la complejidad sera
            O(logn), porque siempre dividimos el espacio de busqueda del lugar donde insertar en 2.
        Ver raiz : O(1), simplemente vemos la raiz, la cual tenemos acceso a su direccion de memoria
            directamente en la estructura del arbol.
        Ver si esta vacio: O(1), simplemente es ver si la raiz existe, la cual tenemos acceso a su
            direccion de memoria directamente en la estructura del arbol.
        Recorrer: O(n), ya que se necesitan visitar todos los elementos del arbol.
        Destruir: O(n), ya que se necesitan visitar todos los elementos para poder eliminarlos.

****************************************************************************************************************************