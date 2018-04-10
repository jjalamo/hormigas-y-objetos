/*----------------------------------------*/
/*-------------ESTRUCTURAS--------------*/
/*----------------------------------------*/

/*------------ ESTRUCTURA OBJETO ---------------*/
struct objeto_rep {
  int color;
  int posx;
  int posy;
  struct objeto_rep *sig;
  struct objeto_rep *ant;
}; typedef struct objeto_rep *objeto;

/*--------- ESTRUCTURA LISTA DE OBJETOS -----------*/
struct lobjeto_rep {
  int nobjetos;
  struct objeto_rep *primero;
  struct objeto_rep *ultimo;
}; typedef struct lobjeto_rep *lobjeto;

/*-----------ESTRUCTURA HORMIGA --------------------*/
struct hormiga_rep {
  int posx;
  int posy;
  int color;
  struct hormiga_rep *sig;
  struct hormiga_rep *ant;
  struct objeto_rep *ob;
}; typedef struct hormiga_rep *hormiga;

/*--------- ESTRUCTURA LISTA DE HORMIGAS -----------*/
struct lhormiga_rep {
  int nhormigas;
  struct hormiga_rep *primero;
  struct hormiga_rep *ultimo;
}; typedef struct lhormiga_rep *lhormiga;
/*----------------------------------------*/



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
int consultar_color_hormiga(hormiga h);
void cambiar_color_hormiga(hormiga h, int color);
/*----------- PRIMITIVAS LISTA DE HORMIGAS -----------*/
lhormiga crear_listah ();
void destruir_listah (lhormiga *lh);
void meter_hormiga_listah (lhormiga lh, hormiga h);
hormiga sacar_hormiga_listah (lhormiga lh, int pos);
hormiga ver_hormiga_listah (lhormiga lh, int pos);
int numhormigas_listah (lhormiga lh);
int buscar_hormiga_listah (lhormiga lh, int px, int py);
/*----------------------------------------*/


