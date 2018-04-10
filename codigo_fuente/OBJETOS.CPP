#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "c:\clase\ia\2004\haciendo\hob\objetos.h"
/*----------------------------------------*/
/*----------- CABECERAS DE PRIMITIVAS -----------*/
/*----------------------------------------*/

/*---------- PRIMITIVAS OBJETOS -----------*/
objeto crear_objeto (int c, int px, int py);
void destruir_objeto (objeto *o);
void cambiar_posicion_objeto (objeto o, int px, int py);
int consultar_color_objeto (objeto o);
int consultar_posx_objeto (objeto o);
int consultar_posy_objeto (objeto o);

/*----------- PRIMITIVAS LISTA DE OBJETOS -----------*/
lobjeto crear_listao ();
void destruir_listao (lobjeto *lo);
void meter_objeto_listao (lobjeto lo, objeto o);
objeto sacar_objeto_listao (lobjeto lo, int pos);
objeto ver_objeto_listao (lobjeto lo, int pos);
int numobjetos_listao (lobjeto lo);
int buscar_objeto_listao (lobjeto lo, int px, int py);
/*----------------------------------------*/

/*---------- PRIMITIVAS HORMIGAS -----------*/
hormiga crear_hormiga (int px, int py);
void destruir_hormiga (hormiga *h);
void cambiar_posicion_hormiga (hormiga h, int px, int py);
int consultar_posx_hormiga (hormiga h);
int consultar_posy_hormiga (hormiga h);
void cargar_objeto_hormiga (hormiga h, objeto o);
objeto descargar_objeto_hormiga (hormiga h);
objeto ver_objeto_hormiga(hormiga h);
int consultar_color_hormiga (hormiga h);
void cambiar_color_hormiga (hormiga h, int color);
/*----------- PRIMITIVAS LISTA DE HORMIGAS -----------*/
lhormiga crear_listah ();
void destruir_listah (lhormiga *lh);
void meter_hormiga_listah (lhormiga lh, hormiga h);
hormiga sacar_hormiga_listah (lhormiga lh, int pos);
hormiga ver_hormiga_listah (lhormiga lh, int pos);
int numhormigas_listah (lhormiga lh);
int buscar_hormiga_listah (lhormiga lh, int px, int py);
/*----------------------------------------*/



/*----------------------------------------*/
/*----------- DESARROLLO DE PRIMITIVAS -----------*/
/*----------------------------------------*/

/*---------- PRIMITIVAS OBJETOS -----------*/

/*----------------------------------------*/
objeto crear_objeto (int c, int px, int py) {
  objeto nuev;

  nuev=(objeto) malloc (sizeof (struct objeto_rep));
  if (!nuev) {
    printf("\nERROR, crear_objeto: no hay memoria.");
    exit(1);
  }
  nuev->color=c;
  nuev->posx=px;
  nuev->posy=py;
  nuev->sig=nuev->ant=NULL;
  return(nuev);
}
/*----------------------------------------*/
void destruir_objeto (objeto *o) {
  if(!(*o)) {
    printf("\nError, destruir_objeto: el objeto no existe.");
    exit(1);
  }
  free(*o);
  (*o)=NULL;
}
/*----------------------------------------*/
void cambiar_posicion_objeto (objeto o, int px, int py) {
  if (!o) {
    printf("\nError, cambiar_posicion_objeto: no existe el objeto.");
    exit(1);
  }
  o->posx=px;
  o->posy=py;
}
/*----------------------------------------*/
int consultar_color_objeto (objeto o) {
  if (!o) {
    printf("\nError, consultar_color_objeto: no existe el objeto.");
    exit(1);
  }
  return(o->color);
}
/*----------------------------------------*/
int consultar_posx_objeto (objeto o) {
  if (!o) {
    printf("\nError, consultar_posx_objeto: no existe el objeto.");
    exit(1);
  }
  return(o->posx);
}
/*----------------------------------------*/
int consultar_posy_objeto (objeto o) {
  if(!o) {
    printf("\nError, consultar_posy_objeto: no existe el objeto.");
    exit(1);
  }
  return (o->posy);
}
/*----------------------------------------*/

/*----------- PRIMITIVAS LISTA DE OBJETOS -----------*/
lobjeto crear_listao () {
  lobjeto nuev;

  nuev=(lobjeto) malloc (sizeof(struct lobjeto_rep));
  if(!nuev) {
    printf("\nError, crear_listao: no hay memoria.");
    exit(1);
  }
  nuev->nobjetos=0;
  nuev->primero=nuev->ultimo=NULL;
  return(nuev);
}
/*----------------------------------------*/
void destruir_listao (lobjeto *lo) {
  int i;
  objeto aux;

  if (!(*lo)) {
    printf("\nError, destruir_listao: no existe la lista.");
    exit(1);
  }
  for (i=1;i<=(*lo)->nobjetos;i++) {
    aux=(*lo)->primero;
    (*lo)->primero=aux->sig;
    aux->sig=aux->ant=NULL;
    destruir_objeto(&aux);
  }
  aux=(*lo)->primero=(*lo)->ultimo=NULL;
  free(*lo);
  (*lo)=NULL;
}
/*----------------------------------------*/
void meter_objeto_listao (lobjeto lo, objeto o) {
  if(!lo) {
    printf ("\nError, meter_objeto_listao: no existe la lista.");
    exit(1);
  }
  if(!o) {
    printf("\nError, meter_objeto_listao: no existe el objeto.");
    exit(1);
  }
  if(lo->nobjetos==0) {
    o->sig=o->ant=NULL;
    lo->primero=lo->ultimo=o;
  }else{
    o->sig=NULL;
    o->ant=lo->ultimo;
    lo->ultimo->sig=o;
    lo->ultimo=o;
  }
  lo->nobjetos++;
}

/*----------------------------------------*/
objeto sacar_objeto_listao (lobjeto lo, int pos) {
  int i;
  objeto aux;

  if(!lo) {
    printf("\nError, sacar_objeto_listao: no existe la lista.");
    exit(1);
  }
  if( (pos<1)||(pos>lo->nobjetos) ){
    printf("\nError, sacar_objeto_listao: posicion invalida de objeto.");
    exit(1);
  }
  if(pos==lo->nobjetos) {
    aux=lo->ultimo;
    lo->ultimo=aux->ant;
    lo->ultimo->sig=aux->ant=aux->sig=NULL;
  }else{
    if(pos==1) {
      aux=lo->primero;
      lo->primero=aux->sig;
      lo->primero->ant=aux->ant=aux->sig=NULL;
    }else{
      aux=lo->primero;
      for(i=2;i<=pos;i++){
	aux=aux->sig;
      }
      aux->ant->sig=aux->sig;
      aux->sig->ant=aux->ant;
      aux->sig=aux->ant=NULL;
    }
  }
  lo->nobjetos--;
  return(aux);
}
/*----------------------------------------*/
objeto ver_objeto_listao (lobjeto lo, int pos) {
  int i;
  objeto aux;

  if(!lo) {
    printf("\nError, sacar_objeto_listao: no existe la lista.");
    exit(1);
  }
  if( (pos<1)||(pos>lo->nobjetos) ){
    printf("\nError, sacar_objeto_listao: posicion invalida de objeto.");
    exit(1);
  }
  if(pos==lo->nobjetos) {
    aux=lo->ultimo;
  }else{
    if(pos==1) {
      aux=lo->primero;
    }else{
      aux=lo->primero;
      for(i=2;i<=pos;i++){
	aux=aux->sig;
      }
    }
  }
  return(aux);
}
/*----------------------------------------*/
int numobjetos_listao (lobjeto lo) {
  if(!lo) {
    printf("\nError, numobjetos_listao: no existe la lista.");
    exit(1);
  }
  return(lo->nobjetos);
}
/*----------------------------------------*/
int buscar_objeto_listao (lobjeto lo, int px, int py) {
  int i;
  int pos;
  objeto aux;

  if(!lo) {
    printf("\nError, buscar_objeto_listao: no existe la lista.");
    exit(1);
  }
  pos=0;
  if (lo->nobjetos>0) {
    aux=lo->primero;
    for(i=1;(pos==0)&&(aux!=NULL);i++) {
      if( (aux->posx==px)&&(aux->posy==py) ){
	pos=i;
      }
      aux=aux->sig;
    }
  }
  return(pos);
}
/*----------------------------------------*/


/*---------- PRIMITIVAS HORMIGAS -----------*/

/*----------------------------------------*/
hormiga crear_hormiga (int px, int py) {
  hormiga nuev;

  nuev=(hormiga) malloc (sizeof (struct hormiga_rep));
  if (!nuev) {
    printf("\nERROR, crear_hormiga: no hay memoria.");
    exit(1);
  }
  nuev->posx=px;
  nuev->posy=py;
  nuev->sig=nuev->ant=NULL;
  nuev->ob=NULL;
  return(nuev);
}
/*----------------------------------------*/
void destruir_hormiga (hormiga *h) {
  if(!(*h)) {
    printf("\nError, destruir_hormiga: la hormiga no existe.");
    exit(1);
  }
  free(*h);
  (*h)=NULL;
}
/*----------------------------------------*/
void cambiar_posicion_hormiga (hormiga h, int px, int py) {
  if (!h) {
    printf("\nError, cambiar_posicion_hormiga: no existe la hormiga.");
    exit(1);
  }
  h->posx=px;
  h->posy=py;
}
/*----------------------------------------*/
int consultar_posx_hormiga (hormiga h) {
  if (!h) {
    printf("\nError, consultar_posx_hormiga: no existe la hormiga.");
    exit(1);
  }
  return(h->posx);
}
/*----------------------------------------*/
int consultar_posy_hormiga (hormiga h) {
  if (!h) {
    printf("\nError, consultar_posy_hormiga: no existe la hormiga.");
    exit(1);
  }
  return(h->posy);
}
/*----------------------------------------*/
void cargar_objeto_hormiga (hormiga h, objeto o) {
  if(!h) {
    printf("\nError, cargar_objeto_hormiga: no existe la hormiga."),
    exit(1);
  }
  if(!o) {
    printf("\nError, cargar_objeto_hormiga: no existe el objeto.");
    exit(1);
  }
  h->ob=o;
}
/*----------------------------------------*/
objeto descargar_objeto_hormiga (hormiga h) {
  objeto aux;

  if(!h) {
    printf("\nError, descargar_objeto_hormiga: no existe la hormiga.");
    exit(1);
  }
  aux=h->ob;
  h->ob=NULL;
  return(aux);
}
/*----------------------------------------*/
objeto ver_objeto_hormiga(hormiga h) {
  return(h->ob);
}
/*----------------------------------------*/
int consultar_color_hormiga(hormiga h) {
  if(!h) {
    printf("\nError, consultar_color_hormiga: no existe la hormiga.");
    exit(1);
  }
  return(h->color);
}
/*----------------------------------------*/
void cambiar_color_hormiga(hormiga h, int color) {
  if(!h) {
    printf("\nError, cambiar_color_hormiga: no existe la hormiga.");
    exit(1);
  }
  h->color=color;
}
/*----------------------------------------*/

/*----------- PRIMITIVAS LISTA DE HORMIGAS -----------*/

/*----------------------------------------*/
lhormiga crear_listah () {
  lhormiga nuev;

  nuev=(lhormiga) malloc (sizeof(struct lhormiga_rep));
  if(!nuev) {
    printf("\nError, crear_listah: no hay memoria.");
    exit(1);
  }
  nuev->nhormigas=0;
  nuev->primero=nuev->ultimo=NULL;
  return(nuev);
}
/*----------------------------------------*/
void destruir_listah (lhormiga *lh) {
  int i;
  hormiga aux;

  if (!(*lh)) {
    printf("\nError, destruir_listah: no existe la lista.");
    exit(1);
  }
  for (i=1;i<=(*lh)->nhormigas;i++) {
    aux=(*lh)->primero;
    (*lh)->primero=aux->sig;
    aux->sig=aux->ant=NULL;
    destruir_hormiga(&aux);
  }
  aux=(*lh)->primero=(*lh)->ultimo=NULL;
  free(*lh);
  (*lh)=NULL;
}
/*----------------------------------------*/
void meter_hormiga_listah (lhormiga lh, hormiga h) {
  if(!lh) {
    printf ("\nError, meter_hormiga_listah: no existe la lista.");
    exit(1);
  }
  if(!h) {
    printf("\nError, meter_hormiga_listah: no existe la hormiga.");
    exit(1);
  }
  if(lh->nhormigas==0) {
    h->sig=h->ant=NULL;
    lh->primero=lh->ultimo=h;
  }else{
    h->sig=NULL;
    h->ant=lh->ultimo;
    lh->ultimo->sig=h;
    lh->ultimo=h;
  }
  lh->nhormigas++;
}
/*----------------------------------------*/
hormiga sacar_hormiga_listah (lhormiga lh, int pos) {
  int i;
  hormiga aux;

  if(!lh) {
    printf("\nError, sacar_hormiga_listah: no existe la lista.");
    exit(1);
  }
  if( (pos<1)||(pos>lh->nhormigas) ){
    printf("\nError, sacar_hormiga_listah: posicion invalida de hormiga.");
    exit(1);
  }
  if(pos==lh->nhormigas) {
    aux=lh->ultimo;
    lh->ultimo=aux->ant;
    lh->ultimo->sig=aux->ant=aux->sig=NULL;
  }else{
    if(pos==1) {
      aux=lh->primero;
      lh->primero=aux->sig;
      lh->primero->ant=aux->ant=aux->sig=NULL;
    }else{
      aux=lh->primero;
      for(i=2;i<=pos;i++){
	aux=aux->sig;
      }
      aux->ant->sig=aux->sig;
      aux->sig->ant=aux->ant;
      aux->sig=aux->ant=NULL;
    }
  }
  lh->nhormigas--;
  return(aux);
}
/*----------------------------------------*/
hormiga ver_hormiga_listah (lhormiga lh, int pos) {
  int i;
  hormiga aux;

  if(!lh) {
    printf("\nError, sacar_hormiga_listah: no existe la lista.");
    exit(1);
  }
  if( (pos<1)||(pos>lh->nhormigas) ){
    printf("\nError, sacar_hormiga_listah: posicion invalida de hormiga.");
    exit(1);
  }
  if(pos==lh->nhormigas) {
    aux=lh->ultimo;
  }else{
    if(pos==1) {
      aux=lh->primero;
    }else{
      aux=lh->primero;
      for(i=2;i<=pos;i++){
	aux=aux->sig;
      }
    }
  }
  return(aux);
}
/*----------------------------------------*/
int numhormigas_listah (lhormiga lh) {
  if(!lh) {
    printf("\nError, numhormigas_listah: no existe la lista.");
    exit(1);
  }
  return(lh->nhormigas);
}
/*----------------------------------------*/
int buscar_hormiga_listah (lhormiga lh, int px, int py) {
  int i;
  int pos;
  hormiga aux;

  if(!lh) {
    printf("\nError, buscar_hormiga_listah: no existe la lista.");
    exit(1);
  }
  pos=0;
  if (lh->nhormigas>0) {
    aux=lh->primero;
    for(i=1;(pos==0)&&(aux!=NULL);i++) {
      if( (aux->posx==px)&&(aux->posy==py) ){
	pos=i;
      }
      aux=aux->sig;
    }
  }
  return(pos);
}
/*----------------------------------------*/

