#ifndef COLACP_H_INCLUDED
#define COLACP_H_INCLUDED

// Macros con códigos de finalización
#define CCP_ERROR_MEMORIA           10
#define CCP_VACIA					11

// Tipos de datos genéricos para las claves y valores.
typedef void * tClave;
typedef void * tValor;

// Structs para la manipulación de una cola con prioridad.
typedef struct entrada{
    tClave clave;
    tValor valor;
}* tEntrada;

typedef struct nodo{
    tEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
}* tNodo;

typedef struct cola_con_prioridad{
    unsigned int cantidad_elementos;
    tNodo raiz;
    int (*comparador)(tEntrada,tEntrada);
} * tColaCP;

// ---------------------------------------------------------------------------------------------
// Definición de prototipos y documentación de las funciones.
// ---------------------------------------------------------------------------------------------

/**
 Inicializa una cola con prioridad vacía.
 A todo efecto, la comparación de claves se realizará mediante la función fComparacion.
 Finaliza indicando CCP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
extern tColaCP crear_cola_cp(int (*fComparacion)(tEntrada,tEntrada));

/**
 Inserta una entrada con clave y valor, en la cola con prioridad.
 Ordena las entradas de acuerdo a la función de comparación con la que se creó la cola con prioridad.
 Finaliza indicando CCP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
extern int cp_insertar(tColaCP cola, tEntrada entr);

/**
 Elimina la entrada con menor clave de la cola con prioridad.
 Finaliza indicando CCP_VACIA si la cola con prioridad no tiene elementos para eliminar.
**/
extern tEntrada cp_eliminar(tColaCP cola);

/**
 Retorna la cantidad actual de elementos almacenados en la cola con prioridad.
**/
extern int cp_size(tColaCP cola);

/**
 Destruye la cola con prioridad, elimininando cada una de sus entradas.
 Las entradas son eliminados mediante la función fEliminar.
**/
extern int cp_destruir(tColaCP * cola, void (*fEliminar)(tEntrada));

#endif // COLACP_H_INCLUDED
