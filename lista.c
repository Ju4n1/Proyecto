#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/**
 Inicializa una lista vac�a.
 Una referencia a la lista creada es referenciada en *L.
**/
void crear_lista(tLista * l) {

     // Reservo la memoria de la lista, y compruebo que la operaci�n se haya realizado sin error.
    (*l) = (tLista) malloc(sizeof(struct celda));
     if ((*l) == NULL)
        exit(LST_ERROR_MEMORIA);

     // Lista vac�a "centinela".
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}

/**
 Inserta el elemento E, en la posici�n P, en L.
 Con L = A,B,C,D y la posici�n P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e) {

	// Verifico que la posici�n sea v�lida, si se asume p siempre v�lida se puede obviar el chequeo.
	if (p==NULL)
        exit(LST_POSICION_INVALIDA);

    // Reservo la memoria que ocupara la nueva posici�n, y cheque que la operacion no termine en error.
    tPosicion posNuevaCelda = (tPosicion) malloc(sizeof(struct celda));
    if (posNuevaCelda == NULL)
        exit(LST_ERROR_MEMORIA);

	// Se asignan todos los valores correspondientes a la posici�n nueva.
    posNuevaCelda->elemento = e;
    posNuevaCelda->siguiente = p->siguiente;
    p->siguiente = posNuevaCelda;
}

/**
 Elimina el nodo que se encuentra en la posici�n P de L.
 El elemento almacenado en la posici�n P es eliminado mediante la funci�n fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)) {

    // Chequeo que posici�n a eliminar sea v�lida
    if(p->siguiente==NULL)
          exit(LST_POSICION_INVALIDA);

    else{

         // Esta es la posici�n que tengo que eliminar.
         tPosicion aux= p->siguiente;

         // Hago que la posici�n anterior apunte a la siguiente de la eliminada.
         p->siguiente = aux->siguiente;

        // Elimino el contenido de la posic�n con fEliminar y libero la memoria qye ocupa.
        fEliminar(aux->elemento);
        free(aux);}
}

/**
 Destruye la lista L, elimininando cada una de sus posiciones. Los elementos almacenados en las posiciones son eliminados
 mediante la funci�n fEliminar parametrizada.
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento)){

    // Primera posici�n con elemente en caso de que exista y un auxiliar para el ciclo.
    tPosicion pos =(*l)->siguiente;
    tPosicion aux;

	// Recorro la lista mientras tenga elementos.
    while(pos!= NULL){

         // Importante no perder la posici�n que destruir� en el pr�ximo ciclo.
		 aux=pos->siguiente;

         // Elimino el contenido y libero espacio ocupado.
         fEliminar(pos->elemento);
         free(pos);

		 // Ahora puedo destruir la siguiente posici�n.
         pos=aux;
                      }

// Cuando todas la posiciones est�n destruidas, libero la memeria de lista y corto su referencia.
free(*l);
*l = NULL;
}

/**
 Recupera y retorna el elemento en la posici�n P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
tElemento l_recuperar(tLista l, tPosicion p) {

      // Para poder recuperar la posici�n tiene que ser distinta de fin.
      if(p == l_fin(l))
          exit(LST_POSICION_INVALIDA);

// Posici�n indirecta siempre recupera el elemento siguite al de la posici�n pasada por par�metros.
return (p->siguiente)->elemento;}

/**
 Recupera y retorna la primera posici�n de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_primera(tLista l){

// Primera siempre es el centinela.
return l;}

/**
 Recupera y retorna la posici�n siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
tPosicion l_siguiente(tLista l, tPosicion p) {

     // Siguiente de fin no existe, se asume p v�lida.
    if(p==l_fin(l))
        exit(LST_NO_EXISTE_SIGUIENTE);

return p->siguiente;}

/**
 Recupera y retorna la posici�n anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
tPosicion l_anterior(tLista l, tPosicion p) {

    // Anterior a primera no existe.
    if(p==l_primera(l))
        exit(LST_NO_EXISTE_ANTERIOR);

    tPosicion pos = l;

    // Cuando el siguiente de pos es igual a p, pos es el anterior.
    while(pos->siguiente != p)
         pos = pos->siguiente;

return pos;}

/**
 Recupera y retorna la �ltima posici�n de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_ultima(tLista l) {

    tPosicion pos = l;

    // Cuando la lista no est� vacia puedo buscar ultima, sino primera=ultima=fin.
    if(l->siguiente!=NULL)

        // Cuando pos siguiente siguiente es nula, significa que estoy en la posicion que apunta a fin, en otras palabras estoy en �ltima.
        while(((pos->siguiente)->siguiente) != NULL)
              pos = pos->siguiente;


return pos;}

/**
 Recupera y retorna la posici�n fin de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_fin(tLista l) {
      // Importante pararse en primera porque si l est� vacia primera=fin.
      tPosicion pos = l;

      //Cuando pos siguiente es nula estoy en fin.
      while(pos->siguiente!=NULL)
            pos = pos->siguiente;

return pos;}

/**
 Funci�n que devuelve la longitud de la  lista.
**/
int l_longitud(tLista l) {
    // Inicialmente la lista esta vac�a.
    int contador = 0;

    // Posici�n para recorrer la lista contanto.
    tPosicion pos = l;
        while(pos->siguiente != NULL){
            pos = pos->siguiente;
            contador++;}

return contador;}








