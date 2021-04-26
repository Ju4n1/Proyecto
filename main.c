#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "colacp.h"
#include "TCiudad.h"
#include <math.h>


float distancia(TCiudad c1, TCiudad c2){
//Recupero las coordenadas,
float x1=c1->pos_x;
float y1=c1->pos_y;
float x2=c2->pos_x;
float y2=c2->pos_y;
//Calculo la distancia mediante "Distancia Mahattan"
float dist=fabs(x2-x1)+fabs(y2-y1);

return dist;}

int fComparador(tEntrada e1,tEntrada e2){
int salida=0;

    int*c1=e1->clave;
    int *c2=e2->clave;

    if(*c1>*c2)
        salida=-1;
       else if(*c1<*c2)
               salida=1;
return salida;}

void fEliminarEntrada(tEntrada e){
free(e);}

void fEliminar(tElemento e){

   free(e);}

//la lista debe existir para mostrarla
void mostrar(tLista l){

    if(l_longitud(l)==0)
       printf("la lista esta vacia \n");
       else
           { tPosicion pos=l; //primer posicion no NULL de la lista
             while(pos!=l_fin(l)){

             int *salida= l_recuperar(l,pos);
             printf(" %d",*salida);
                   pos=pos->siguiente;}

           }

  printf("\n");}



void probarLista(){


tLista l;
crear_lista(&l);

printf("muestro la lista \n");

mostrar(l);

printf("muestro la longitud de l : %d\n ",l_longitud(l));


printf("inserto 1,2,3,5 en fin \n");

int *a1 =malloc(sizeof(int));
*a1=1;

l_insertar(l,l_primera(l),a1);

int *a2 =malloc(sizeof(int));
*a2=2;
l_insertar(l,l_fin(l),a2);

int *a3 =malloc(sizeof(int));
*a3=3;
l_insertar(l,l_fin(l),a3);

int *a5 =malloc(sizeof(int));
*a5=5;
l_insertar(l,l_fin(l),a5);

mostrar(l);

printf("muestro la longitud de l : %d\n ",l_longitud(l));

printf("inserto 4 en ultima \n");
int *a4 =malloc(sizeof(int));
*a4=4;
l_insertar(l,l_ultima(l),a4);

printf("muestro la longitud de l : %d\n ",l_longitud(l));

mostrar(l);

printf("inserto 9 en primera \n");
int *a9 =malloc(sizeof(int));
*a9=9;

l_insertar(l,l_primera(l),a9);

printf("muestro la longitud de l : %d\n ",l_longitud(l));

mostrar(l);

tPosicion pos=l;

printf(" muestro primera como l_primera(l)->elemento 'NULL': %d\n",pos->elemento);
int* sal=l_ultima(l)->elemento;
printf(" muestro ultima como l_ultima(l)->elemento : %d\n",*sal);

sal=l_fin(l)->elemento;
printf(" muestro fin como l_fin(l)->elemento : %d\n",*sal);

sal=l_recuperar(l,l_primera(l));
printf(" recupero primera: %d\n",*sal);

sal=l_recuperar(l,l_ultima(l));
printf(" recupero ultima: %d\n",*sal);

sal=l_recuperar(l,l_anterior(l,l_ultima(l)));
printf(" recupero anterior ultima '3' -> '4' : %d\n",*sal);

sal=l_recuperar(l,l_siguiente(l,l_primera(l)));
printf(" recupero siguiente a primera '9' -> '1' : %d\n",*sal);

printf(" elimino primera '9' :");

l_eliminar(l,l_primera(l),&fEliminar); printf("elimine");

mostrar(l);

printf(" elimino ultima '5' :");

l_eliminar(l,l_ultima(l),&fEliminar);

mostrar(l);

printf(" elimino 2 como siguiente de primera :");

l_eliminar(l,l_primera(l)->siguiente,&fEliminar);

mostrar(l);

sal=l_recuperar(l,l_ultima(l));
printf(" muestro recUltima fin: %d \n",*sal);

printf("destruyo la lista");

l_destruir(&l,&fEliminar);

}

void mostraCola(tColaCP cola){

   int *a=cola->raiz->entrada->valor;
   printf("%d \n",*a);

}





void probarCola(){
 tColaCP cola=crear_cola_cp(&fComparador);



tEntrada e1=malloc(sizeof(struct entrada));
int* c1=malloc(sizeof(int));
*c1=20;
int * v1 = malloc(sizeof(int));
*v1 =20;
e1->clave=c1;
e1->valor=v1;

tEntrada e2=malloc(sizeof(struct entrada));
int* c2=malloc(sizeof(int));
*c2=45;
int * v2 = malloc(sizeof(int));
*v2 =45;
e2->clave=c2;
e2->valor=v2;

tEntrada e3=malloc(sizeof(struct entrada));
int* c3=malloc(sizeof(int));
*c3=30;
int * v3 = malloc(sizeof(int));
*v3 =30;
e3->clave=c3;
e3->valor=v3;

tEntrada e4=malloc(sizeof(struct entrada));
int* c4=malloc(sizeof(int));
*c4=16;
int * v4 = malloc(sizeof(int));
*v4 =16;
e4->clave=c4;
e4->valor=v4;

tEntrada e5=malloc(sizeof(struct entrada));
int* c5=malloc(sizeof(int));
*c5=18;
int * v5 = malloc(sizeof(int));
*v5 =18;
e5->clave=c5;
e5->valor=v5;

tEntrada e6=malloc(sizeof(struct entrada));
int* c6=malloc(sizeof(int));
*c6=33;
int * v6 = malloc(sizeof(int));
*v6 =33;
e6->clave=c6;
e6->valor=v6;

tEntrada e7=malloc(sizeof(struct entrada));
int* c7=malloc(sizeof(int));
*c7=25;
int * v7 = malloc(sizeof(int));
*v7 =25;
e7->clave=c7;
e7->valor=v7;




cp_insertar(cola,e1);
cp_insertar(cola,e2);
cp_insertar(cola,e3);
cp_insertar(cola,e4);
cp_insertar(cola,e5);
cp_insertar(cola,e6);
cp_insertar(cola,e7);

printf(" comparo 20 y 45 : %d \n",fComparador(e1,e2));
printf(" comparo 45 y 20 : %d\n",fComparador(e2,e1));
printf("comparo 20 y 20 : %d\n",fComparador(e1,e1));
printf("comparo 16 y 20 : %d\n",fComparador(e4,e1));



tNodo h1=encontrarHoja(cola,cola->raiz);
int * h2=h1->entrada->clave;
printf("muestro hoja %d\n",*h2);

//printf("comparo 30 y 45 : %d\n",fComparador(cola->raiz->hijo_derecho->hijo_derecho->entrada,cola->raiz->hijo_izquierdo->hijo_izquierdo->entrada));

/*printf(" profundidad 16 deberia ser 2 y es: %d\n",profundidad(cola,cola->raiz));
printf(" profundidad 20 deberia ser 1 y es: %d\n",profundidad(cola,cola->raiz->hijo_derecho));
printf(" profundidad 25 deberia ser 0 y es: %d\n",profundidad(cola,cola->raiz->hijo_derecho->hijo_izquierdo));
printf(" profundidad 18 deberia ser 1 y es: %d\n",profundidad(cola,cola->raiz->hijo_izquierdo));
printf(" profundidad 45 deberia ser 0 y es: %d\n",profundidad(cola,cola->raiz->hijo_izquierdo->hijo_izquierdo));
printf(" profundidad 33 deberia ser 0 y es: %d\n",profundidad(cola,cola->raiz->hijo_izquierdo->hijo_derecho));
*/

/*
int *e=cp_eliminar(cola)->clave;
printf(" elimino %d\n",*e);

e=cp_eliminar(cola)->clave;
printf(" elimino %d\n",*e);

e=cp_eliminar(cola)->clave;
printf(" elimino %d\n",*e);

e=cp_eliminar(cola)->clave;
printf(" elimino %d\n",*e);

e=cp_eliminar(cola)->clave;
printf(" elimino %d\n",*e);

e=cp_eliminar(cola)->clave;
printf(" elimino %d\n",*e);


e=cp_eliminar(cola)->clave;
printf(" elimino %d\n",*e);
*/



int*a=cola->raiz->entrada->clave;
printf("                  %d\n",*a);

if(*a!=NULL)
a=(cola->raiz->hijo_izquierdo)->entrada->clave;
printf("      %d",*a);

if(*a!=NULL)
a=(cola->raiz->hijo_derecho)->entrada->clave;
printf("                        %d\n",*a);

if(*a!=NULL)
a=cola->raiz->hijo_izquierdo->hijo_izquierdo->entrada->clave;
printf("%d",*a);

if(*a!=NULL)
a=cola->raiz->hijo_izquierdo->hijo_derecho->entrada->clave;
printf("        %d",*a);

if(*a!=NULL)
a=cola->raiz->hijo_derecho->hijo_izquierdo->entrada->clave;
printf("            %d",*a);

a=cola->raiz->hijo_derecho->hijo_derecho->entrada->clave;
if(cola->raiz->hijo_derecho->hijo_derecho!=NULL)
printf("            %d\n",*a);


/*printf("\n profundidad 33 %d\n",profundidad(cola,cola->raiz->hijo_izquierdo));
printf("\n profundidad 45 %d\n",profundidad(cola,cola->raiz));

h1=encontrarHoja(cola,cola->raiz);
h2=h1->entrada->clave;
printf("muestro hoja %d\n",*h2);
*/

printf("\nLa longitud de la cola %d\n",cp_size(cola));

printf(" destruyo \n",cp_destruir(&cola,&fEliminarEntrada));

}

int main(){


//probarLista();

probarCola();




return 0;}
