#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"

// Macros con c�digos de salida para las funsiones Insertar y Destriur.
#define FALSE      0
#define TRUE       1

/**
 Inicializa una cola con prioridad vac�a.
 A todo efecto, la comparaci�n de claves se realizar� mediante la funci�n fComparacion.
 Finaliza indicando CCP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
tColaCP crear_cola_cp(int (*fComparacion)(tEntrada,tEntrada)){

    tColaCP cola=malloc(sizeof(struct cola_con_prioridad));// Reserva la memoria que va a utilizar la nueva cola.

    if(cola==NULL)//Comprueba que la memoria se haya resevado.
        exit(CCP_ERROR_MEMORIA);

    //seteo valores iniciales a la cola vacia
    cola->comparador=fComparacion;
    cola->cantidad_elementos=0;
    cola->raiz=NULL;


return cola;}

/**
 Inserta una entrada con clave y valor, en la cola con prioridad.
 Ordena las entradas de acuerdo a la funci�n de comparaci�n con la que se cre� la cola con prioridad.
 Finaliza indicando CCP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
int cp_insertar(tColaCP cola, tEntrada ent){

    int salida=FALSE;

    tNodo nuevo=malloc(sizeof(struct nodo));//Reservo la memoria para el nuevo nodo.
    if(nuevo==NULL)//Chequeo la operacion anterior.
       exit(CCP_ERROR_MEMORIA);
       else
           {//Seteo elementos del nuevo nodo.
            nuevo->entrada=ent;
            nuevo->hijo_derecho=NULL;
            nuevo->hijo_izquierdo=NULL;
            nuevo->padre=NULL;

            salida=TRUE; //Se creo correctamente, se va a insertar.
            cola->cantidad_elementos++;
            if(cola->cantidad_elementos==1)
                 cola->raiz=nuevo;//La cola estaba vac�a.
                 else{

                     }


            }

return salida;}

/**
 Retorna la cantidad actual de elementos almacenados en la cola con prioridad.
**/
int cp_size(tColaCP cola){
return cola->cantidad_elementos;}



 void destruirAux(tNodo nodo,void (*fEliminar)(tEntrada)){
    //Recorre recursivamente a la izquierda y derecha.
    if(nodo->hijo_izquierdo!=NULL)
        destruirAux(nodo->hijo_izquierdo,fEliminar);
    if(nodo->hijo_derecho!=NULL)
        destruirAux(nodo->hijo_derecho,fEliminar);

    //Vuelvo de la recursion eliminando la entrada y liberando el espacio de3l nodo.
    fEliminar(nodo->entrada);
    free(nodo);

 }


/**
 Destruye la cola con prioridad, elimininando cada una de sus entradas.
 Las entradas son eliminados mediante la funci�n fEliminar.
**/
 int cp_destruir(tColaCP * cola, void (*fEliminar)(tEntrada)){

        //Cheque que la cola tenga ra�z antes de destruir todos sus nodos.
        if((*cola)->raiz!=NULL)
             destruirAux((*cola)->raiz,fEliminar);
       //Se destruyeron los nodo libero el espacio que ocupa la cola.
       free(cola);

 return TRUE;}



