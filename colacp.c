#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"

// Macros con códigos de salida para las funsiones Insertar y Destriur.
#define FALSE      0
#define TRUE       1

/**
 Inicializa una cola con prioridad vacía.
 A todo efecto, la comparación de claves se realizará mediante la función fComparacion.
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
   Fución auxiliar ordena de manera que cada nodo tenga mayor prioridad que sus hijos, partiendo de una hoja insertada y recorriendo hacia arriba.
**/
void ordenarArriva(tNodo nodo,int (*fComparacion)(tEntrada,tEntrada)){

    if(nodo->padre!=NULL)
            //Si la prioridad del hijo es mayor a la del padre hago swap.
            if(fComparacion(nodo->entrada,nodo->padre->entrada)==1)
               {tEntrada aux=nodo->padre->entrada;
                nodo->padre->entrada=nodo->entrada;
                nodo->entrada=aux;}


  //Como hice swap entre nodo y su padre, nodo padre sería el "abuelo" es decir el padre del padre.
   if(nodo->padre!=NULL)
       ordenarArriva(nodo->padre,fComparacion);
}


/**
   Función auxiliar inserte en la ultima posicion disponible del heap en base a "n" que es la cantidad de elementos de la cola contando la inserción actual.
**/
 tNodo insertarAux(tColaCP cola, tNodo nodoNuevo,int n){
    tNodo pos;
    // Un elemento correponde a la raíz
    if( n == 1)
        return cola->raiz;
    else{
          // Utilizo cantidsad elementos para determinar si es hijo izquierdo o derecho.
          pos = insertarAux(cola,nodoNuevo, n/2);
          if(n == cola->cantidad_elementos)
             {
                // n par hijo izquierdo (ya considere en incremento de cantidad de elementos).
                if(n % 2 == 0)
                      pos->hijo_izquierdo = nodoNuevo;
                  else{
                      // n impar hijo derecho
                      pos->hijo_derecho = nodoNuevo;}
                      nodoNuevo->padre = pos;
             }
              else{
                   if(n % 2 == 0)
                        return pos->hijo_izquierdo;
                    else
                        return pos->hijo_derecho;

                  }
         }

return nodoNuevo;}


/**
 Inserta una entrada con clave y valor, en la cola con prioridad.
 Ordena las entradas de acuerdo a la función de comparación con la que se creó la cola con prioridad.
 Finaliza indicando CCP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/


int cp_insertar(tColaCP cola, tEntrada ent){
    // Inicialmente no inserté nada.
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
                 cola->raiz=nuevo;//La cola estaba vacía.
                 else{
                      insertarAux(cola,nuevo,cola->cantidad_elementos);
                      ordenarArriva(nuevo,cola->comparador);
                     }


            }

return salida;}

/**
 Función auxiliar, dados dos enteros determina y retorna el mayor.
**/
int max(int a, int b){
    int salida;
    if(a>b)
      salida=a;
    else salida=b;
return salida;}

/**
   Función auxiliar que retorna la profundidad del nodo.
**/

int profundidad(tColaCP cola,tNodo nodo){
    int salida;
      // Si es hoja profundidad es 0.
      if((nodo->hijo_izquierdo==NULL)&(nodo->hijo_derecho==NULL))
        salida=0;
      else
          //No es hoja.
          if((nodo->hijo_izquierdo!=NULL)&(nodo->hijo_derecho!=NULL))
            // La profundidad es uno más la mayor de las profundidades de sus sub árboles.
            salida=1+max(profundidad(cola,nodo->hijo_izquierdo),profundidad(cola,nodo->hijo_derecho));
            else
                // Un solo hijo, este solo puede ser izquierdo por porpiedades de heap.
                if(nodo->hijo_izquierdo!=NULL)
                    salida=1+(profundidad(cola,nodo->hijo_izquierdo));


return salida;}

/**
 Funcioón auxiliar de eliminar que retorna la hoja que se puede eliminar del heap sin incumplir las propiedades del mismo.
**/
tNodo encontrarHoja(tColaCP cola, tNodo nodo){
             tNodo salida;
             // Nodo es hoja.
             if((nodo->hijo_derecho==NULL)&(nodo->hijo_izquierdo==NULL))
                salida=nodo;
                else
                    //Tiene dos hijos
                    if(((nodo->hijo_derecho!=NULL)&(nodo->hijo_izquierdo!=NULL)))
                            {//Verifico la profundidad para mantener la propiedad de completitud del heap
                             if(profundidad(cola,nodo->hijo_izquierdo)==profundidad(cola,nodo->hijo_derecho))
                                salida=encontrarHoja(cola,nodo->hijo_derecho);
                                else salida=encontrarHoja(cola,nodo->hijo_izquierdo);}
                      else if(nodo->hijo_izquierdo!=NULL)
                              salida=encontrarHoja(cola,nodo->hijo_izquierdo);


  return salida;}

void OrdenarAbajo(tColaCP cola,tNodo nodo){
    // Este nodo corresponde al hijo de nodo que tenga mayor priaridad que nodo.
    tNodo mayorP;

    //Tiene dos hijos
    if((nodo->hijo_izquierdo!=NULL)&(nodo->hijo_derecho!=NULL))
      {
       //Comparo ambos hijos para quedarme con el menor(mayor prioridad).
       int comp1=cola->comparador(nodo->hijo_izquierdo->entrada,nodo->hijo_derecho->entrada);
       if(comp1==-1)
           //El derecho es el menor.
          {int comp2=cola->comparador(nodo->entrada,nodo->hijo_derecho->entrada);
             if(comp2==-1)
               mayorP=nodo->hijo_derecho;
               else mayorP=nodo;
          }
          else  //El izquiero es el menor.
                if(comp1==1)
                 {int comp3=cola->comparador(nodo->entrada,nodo->hijo_izquierdo->entrada);
                if(comp3==-1)
                    mayorP=nodo->hijo_izquierdo;
                   else mayorP=nodo;
                 }
         }
        else   //Tiene un solo hijo, por propiedades de heap este solo puede ser izquierdo.
              if(nodo->hijo_izquierdo!=NULL)
                {
                 int comp4=cola->comparador(nodo->entrada,nodo->hijo_izquierdo->entrada);
                 //Izquierdo es menor(mayor prioridad).
                 if(comp4==-1)
                    {mayorP=nodo->hijo_izquierdo;}
                 else mayorP=nodo;
                }
                else mayorP=nodo;


      if(mayorP != nodo)
        {//Hago el swap entre el nodo y su hijo de mayor prioridad y vuelvo a ordenar en caso de ser necesario.
        tEntrada entradaAux = nodo->entrada;
        nodo->entrada = mayorP->entrada;
        mayorP->entrada = entradaAux;
        OrdenarAbajo(cola,mayorP);
        }

}


/**
 Elimina la entrada con menor clave de la cola con prioridad.
 Finaliza indicando CCP_VACIA si la cola con prioridad no tiene elementos para eliminar.
**/
tEntrada cp_eliminar(tColaCP cola){

    //La cola esta vacía no se puede eliminar
    if(cola->cantidad_elementos==0)
       exit(CCP_VACIA);

    //Preparo la salida y decremento size de la cola.
    tEntrada salida=cola->raiz->entrada;
    cola->cantidad_elementos--;

    //Busco la hoja a liminar
    tNodo hoja=encontrarHoja(cola,cola->raiz);

    if(hoja!=cola->raiz)
        //Corto las referencia hacia la hoja.
       {if(hoja->padre->hijo_izquierdo==hoja)
          hoja->padre->hijo_izquierdo=NULL;
          else if(hoja->padre->hijo_derecho==hoja)
                  hoja->padre->hijo_derecho=NULL;

         //Hago swap entre la raíz y la hoja y reordeno el heap
         cola->raiz->entrada=hoja->entrada;
         OrdenarAbajo(cola,cola->raiz);}

//Libero el espacio ocupado por hoja.
free(hoja);

return salida;}


/**
 Retorna la cantidad actual de elementos almacenados en la cola con prioridad.
**/
int cp_size(tColaCP cola){
return cola->cantidad_elementos;}


/**
Función auxiliar para destruir recursivamente.
**/
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
 Las entradas son eliminados mediante la función fEliminar.
**/
 int cp_destruir(tColaCP * cola, void (*fEliminar)(tEntrada)){

         int size=(*cola)->cantidad_elementos;

        //Cheque que la cola tenga raíz antes de destruir todos sus nodos.
        if(size!=0)
            if((*cola)->raiz!=NULL)
                destruirAux((*cola)->raiz,fEliminar);

    //Se destruyeron los nodos, libero el espacio que ocupa la cola.
    free(*cola);

 return TRUE;}



