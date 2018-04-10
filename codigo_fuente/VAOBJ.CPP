#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <alloc.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include "c:\clase\ia\2004\haciendo\hob\objetos.cpp"

#define NEGRO 0
#define AZUL 1
#define VERDE 2
#define CYAN 3
#define ROJO 4
#define ROSA 5
#define MARRON 6
#define GRIS_CLARO 7
#define GRIS 8
#define AZUL_CLARO 9
#define VERDE_CLARO 10
#define CYAN_CLARO 11
#define ROJO_CLARO 12
#define ROSA_CLARO 13
#define AMARILLO 14
#define BLANCO 15

//****** ESTRUCTURAS *********
struct parametros_hob_rep {
  int objeto_rojo;
  int objeto_azul;
  int objeto_verde;
  int objeto_amarillo;
  int nhormigas;
}; typedef struct parametros_hob_rep parametros_hob;

//--------------------------------
//**************** CABECERAS DE FUNCIONES  ********************
void iniciar_modo_grafico();
int mostrar_menu();
void cuadrado(int x1, int y1, int x2, int y2, int color);
void iniciar_simulacion_hob(parametros_hob *p);
void dibujar_entorno_hob();
void dibujar_hormiga(int posx, int posy, int color);
void dibujar_objeto(int posx, int posy, int color);
void buscar_objeto_mismocolor(int pxh, int pyh, int *pxo, int *pyo,
				int color, lobjeto lo);
void buscar_posicion_libre(int px, int py, int *pxlib, int *pylib,
				lobjeto lo, lhormiga lh);
void buscar_objeto_alrededor(int px, int py, int *pxo, int *pyo, lobjeto lo);
int nobjetos_mismocolor (int px, int py, int color, lobjeto lo);
//*************************************************************


//********************* PROGRAMA PRINCIPAL ********************
void main(void) {
  int opcion;
  int fin;
  int px;
  int py;
  parametros_hob phob;

  clrscr();
  iniciar_modo_grafico();

//CREAR SIMULACION HORMIGAS Y OBJETOS
    clearviewport();
    setcolor(BLANCO);

    outtextxy(7,5,"NUMERO DE OBJETOS ROJOS: ");
    outtextxy(7,300,"Introduce un maximo de 500 Objetos Rojos.");
    fin=0;
    while(!fin) {
      gotoxy(30,1);
      printf("                   ");
      gotoxy(30,1);
      scanf("%d",&phob.objeto_rojo);
      if(phob.objeto_rojo<=500 && phob.objeto_rojo>=1) {
	fin=1;
      }
    }

    outtextxy(7,35,"NUMERO DE OBJETOS AZULES: ");
    setcolor(NEGRO);
    outtextxy(7,300,"Introduce un maximo de 500 Objetos Rojos.");
    setcolor(BLANCO);
    outtextxy(7,300,"Introduce un maximo de 500 Objetos Azules.");
    fin=0;
    while(!fin) {
      gotoxy(30,3);
      printf("                   ");
      gotoxy(30,3);
      scanf("%d",&phob.objeto_azul);
      if(phob.objeto_azul<=500 && phob.objeto_azul>=1) {
	fin=1;
      }
    }

    outtextxy(7,68,"NUMERO DE OBJETOS VERDES: ");
    setcolor(NEGRO);
    outtextxy(7,300,"Introduce un maximo de 500 Objetos Azules.");
    setcolor(BLANCO);
    outtextxy(7,300,"Introduce un maximo de 500 Objetos Verdes.");
    fin=0;
    while(!fin) {
      gotoxy(30,5);
      printf("                   ");
      gotoxy(30,5);
      scanf("%d",&phob.objeto_verde);
      if(phob.objeto_verde<=500 && phob.objeto_verde>=1) {
	fin=1;
      }
    }

    outtextxy(7,100,"NUMERO DE OBJETOS AMARILLOS: ");
    setcolor(NEGRO);
    outtextxy(7,300,"Introduce un maximo de 500 Objetos Verdes.");
    setcolor(BLANCO);
    outtextxy(7,300,"Introduce un maximo de 500 Objetos Amarillos.");
    fin=0;
    while(!fin) {
      gotoxy(30,7);
      printf("                   ");
      gotoxy(30,7);
      scanf("%d",&phob.objeto_amarillo);
      if(phob.objeto_amarillo<=500 && phob.objeto_amarillo>=1) {
	fin=1;
      }
    }

    outtextxy(7,132,"NUMERO DE HORMIGAS: ");
    setcolor(NEGRO);
    outtextxy(7,300,"Introduce un maximo de 500 Objetos Amarillos.");
    setcolor(BLANCO);
    outtextxy(7,300,"Introduce un maximo de 100 Hormigas.");
    fin=0;
    while(!fin) {
      gotoxy(30,9);
      printf("                   ");
      gotoxy(30,9);
      scanf("%d",&phob.nhormigas);
      if(phob.nhormigas<=100 && phob.nhormigas>=1) {
	fin=1;
      }
    }
    iniciar_simulacion_hob(&phob);

    restorecrtmode();
    clrscr();
}
//*************************************************************


//**************** DESARROLLO DE FUNCIONES  *******************
void iniciar_modo_grafico() {
  int DRIVER,MODO,codigoerror;

  DRIVER=VGA;
  MODO=VGAHI;
  initgraph(&DRIVER, &MODO, "");
  codigoerror = graphresult();

  if (codigoerror != grOk) {
    printf("Error al iniciar el modo grafico:\n %s\n", grapherrormsg(codigoerror));
    printf("\nPULSA UNA TECLA PARA TERMINAR");
    getch();
    exit(1);
  }
}

//-------------------------------------------------------------
void cuadrado(int x1, int y1, int x2, int y2, int color) {
  setcolor(color);
  line(x1,y1,x2,y1);
  line(x1,y1,x1,y2);
  line(x1,y2,x2,y2);
  line(x2,y1,x2,y2);
}
//-------------------------------------------------------------
void iniciar_simulacion_hob(parametros_hob *p) {
  lobjeto lo;
  lhormiga lh;
  int i;
  int valido;
  int px;
  int py;
  int pos;
  int fin;
  int movimiento;
  int retardo;
  int pxo;
  int pyo;
  int pxlib;
  int pylib;
  int hcargadas;
  int hdescargadas;
  int velocidad;
  int op;
  objeto aux;
  objeto oaux;
  hormiga aux2;


  randomize();
  clearviewport();
  dibujar_entorno_hob();
  lo=crear_listao();
  lh=crear_listah();

//generar los objetos rojos de forma aleatoria
  for (i=1;i<=p->objeto_rojo;i++) {
    aux=NULL;
    valido=0;
    while(!valido) {
      px=0;
      py=0;
      while(px==0) {
	px=rand() % 79;
      }
      while(py==0) {
	py=rand() % 40;
      }
      pos=buscar_objeto_listao(lo,px,py);
      if(pos==0) {
	valido=1;
      }
    }
    aux=crear_objeto(ROJO,px,py);
    meter_objeto_listao(lo,aux);
  }

//generar los objetos azules de forma aleatoria
  for (i=1;i<=p->objeto_azul;i++) {
    aux=NULL;
    valido=0;
    while(!valido) {
      px=0;
      py=0;
      while(px==0) {
	px=rand() % 79;
      }
      while(py==0) {
	py=rand() % 40;
      }
      pos=buscar_objeto_listao(lo,px,py);
      if(pos==0) {
	valido=1;
      }
    }
    aux=crear_objeto(AZUL,px,py);
    meter_objeto_listao(lo,aux);
  }


//generar los objetos verdes de forma aleatoria
  for (i=1;i<=p->objeto_verde;i++) {
    aux=NULL;
    valido=0;
    while(!valido) {
      px=0;
      py=0;
      while(px==0) {
	px=rand() % 79;
      }
      while(py==0) {
	py=rand() % 40;
      }
      pos=buscar_objeto_listao(lo,px,py);
      if(pos==0) {
	valido=1;
      }
    }
    aux=crear_objeto(VERDE,px,py);
    meter_objeto_listao(lo,aux);
  }


//generar los objetos amarillos de forma aleatoria
  for (i=1;i<=p->objeto_amarillo;i++) {
    aux=NULL;
    valido=0;
    while(!valido) {
      px=0;
      py=0;
      while(px==0) {
	px=rand() % 79;
      }
      while(py==0) {
	py=rand() % 40;
      }
      pos=buscar_objeto_listao(lo,px,py);
      if(pos==0) {
	valido=1;
      }
    }
    aux=crear_objeto(AMARILLO,px,py);
    meter_objeto_listao(lo,aux);
  }

//generar las hormigas de forma aleatoria
  for (i=1;i<=p->nhormigas;i++) {
    aux2=NULL;
    valido=0;
    while(!valido) {
      px=0;
      py=0;
      while(px==0) {
	px=rand() % 79;
      }
      while(py==0) {
	py=rand() % 40;
      }
      pos=buscar_objeto_listao(lo,px,py);
      if(pos==0) {
	pos=buscar_hormiga_listah(lh,px,py);
	if(pos==0) {
	  valido=1;
	}
      }
    }
    aux2=crear_hormiga(px,py);
    cambiar_color_hormiga(aux2,ROJO_CLARO);
    meter_hormiga_listah(lh,aux2);
  }

//mostrar en pantalla todos los objetos y hormigas iniciales
  for(i=1;i<=numobjetos_listao(lo);i++) {
    aux=ver_objeto_listao(lo,i);
    dibujar_objeto(consultar_posx_objeto(aux),consultar_posy_objeto(aux),
		   consultar_color_objeto(aux));
  }
  for(i=1;i<=numhormigas_listah(lh);i++) {
    aux2=ver_hormiga_listah(lh,i);
    dibujar_hormiga(consultar_posx_hormiga(aux2),consultar_posy_hormiga(aux2),
		    consultar_color_hormiga(aux2));
  }
  gotoxy(3,22);
  printf("%d",p->objeto_rojo);
  gotoxy(3,23);
  printf("%d",p->objeto_azul);
  gotoxy(3,24);
  printf("%d",p->objeto_verde);
  gotoxy(3,25);
  printf("%d",p->objeto_amarillo);

  gotoxy(12,22);//hormigas cargadas
  printf("%d",0);
  gotoxy(12,23);
  printf("%d",p->nhormigas);//hormigas descargadas


//comienza la simulacion
  gotoxy(18,24);
  printf("Pulsa C para comenzar");
  op=0;
  while( (op!='c') && (op!='C') ) {
    op=getch();
  }
  gotoxy(18,24);
  printf("                     ");
  fin=i=hcargadas=0;
  retardo=1;
  velocidad=9;
  hdescargadas=numhormigas_listah(lh);
  while(!fin) {
    delay(retardo);
    if(kbhit()) {
      op=getch();
      if( (op=='s') || (op=='S') ) {
	fin=1;
      }
      if( (op=='p') || (op=='P') ) {
	gotoxy(18,24);
	printf("Pulsa C para continuar");
	while( (op!='c') && (op!='C') ) {
	  op=getch();
	}
	gotoxy(18,24);
	printf("                      ");
      }
      if(op=='+') {
	retardo--;
	velocidad++;
	if(velocidad>10) {
	  velocidad=10;
	}
	if(retardo<0) {
	  retardo=0;
	}

	gotoxy(31,22);
	printf("   ");
	gotoxy(31,22);
	printf("%d",velocidad);

      }
      if(op=='-') {
	retardo++;
	velocidad--;
	if(velocidad<0) {
	  velocidad=0;
	}
	if(retardo>10) {
	  retardo=10;
	}

	gotoxy(31,22);
	printf("   ");
	gotoxy(31,22);
	printf("%d",velocidad);

      }
    }
    i++;
    if(i>numhormigas_listah(lh)) {
      i=1;
    }
    aux2=ver_hormiga_listah(lh,i);

    //la hormiga se mueve
    px=consultar_posx_hormiga(aux2);
    py=consultar_posy_hormiga(aux2);
    movimiento=rand() % 8;
    if(movimiento==0 || movimiento==3 || movimiento==5) {
      px=px-1;
    }
    if(movimiento==2 || movimiento==4 || movimiento==7) {
      px=px+1;
    }
    if(movimiento==0 || movimiento==1 || movimiento==2) {
      py=py-1;
    }
    if(movimiento==5 || movimiento==6 || movimiento==7) {
      py=py+1;
    }
    if(px<1) {
      px=1;
    }
    if(px>79) {
      px=79;
    }
    if(py<1) {
      py=1;
    }
    if(py>40) {
      py=40;
    }
    valido=buscar_hormiga_listah(lh,px,py);
    if(valido==0) {
      valido=buscar_objeto_listao(lo,px,py);
      if(valido==0) {
	dibujar_hormiga(consultar_posx_hormiga(aux2),consultar_posy_hormiga(aux2),
			NEGRO);
	cambiar_posicion_hormiga(aux2,px,py);
	dibujar_hormiga(px,py,consultar_color_hormiga(aux2));
      }
    }

    //comprobamos si la hormiga tiene un objeto
    oaux=ver_objeto_hormiga(aux2);
    if(oaux) {
      buscar_objeto_mismocolor(consultar_posx_hormiga(aux2),
		consultar_posy_hormiga(aux2), &pxo, &pyo,
		consultar_color_objeto(oaux),lo);
      if(pxo>-1) {
	buscar_posicion_libre(pxo,pyo,&pxlib,&pylib,lo,lh);
	oaux=descargar_objeto_hormiga(aux2);
	cambiar_posicion_objeto(oaux,pxlib,pylib);
	meter_objeto_listao(lo,oaux);
	dibujar_objeto(pxlib,pylib,consultar_color_objeto(oaux));
	cambiar_color_hormiga(aux2,ROJO_CLARO);
	hcargadas--;
	hdescargadas++;

	gotoxy(12,22);
	printf("     ");
	gotoxy(12,22);
	printf("%d",hcargadas);
	gotoxy(12,23);
	printf("     ");
	gotoxy(12,23);
	printf("%d",hdescargadas);


      }
    }else{
      buscar_objeto_alrededor(consultar_posx_hormiga(aux2),
		consultar_posy_hormiga(aux2), &pxo, &pyo,lo);
      if(pxo!=-1) {
	pos=buscar_objeto_listao(lo,pxo,pyo);
	oaux=sacar_objeto_listao(lo,pos);
	cargar_objeto_hormiga(aux2,oaux);
	dibujar_objeto(pxo,pyo,NEGRO);
	cambiar_color_hormiga(aux2,AMARILLO);
	hcargadas++;
	hdescargadas--;

	gotoxy(12,22);
	printf("     ");
	gotoxy(12,22);
	printf("%d",hcargadas);
	gotoxy(12,23);
	printf("     ");
	gotoxy(12,23);
	printf("%d",hdescargadas);

      }
    }
  }

  destruir_listao(&lo);
  destruir_listah(&lh);
}
//-------------------------------------------------------------
void dibujar_entorno_hob() {
  cuadrado(0,0,634,322,ROJO);
  dibujar_objeto(1,43,ROJO);
  dibujar_objeto(1,45,AZUL);
  dibujar_objeto(1,47,VERDE);
  dibujar_objeto(1,49,AMARILLO);
  dibujar_hormiga(10,43,AMARILLO);
  dibujar_hormiga(10,45,ROJO);

  gotoxy(20,22);
  printf("Velocidad:");
  gotoxy(31,22);
  printf("9");

  gotoxy(43,22);
  printf("S.. Salir");

  gotoxy(43,23);
  printf("P.. Pausa");

  gotoxy(43,24);
  printf("+.. + Velocidad");

  gotoxy(43,25);
  printf("-.. - Velocidad");
}
//-------------------------------------------------------------
void dibujar_hormiga(int posx, int posy, int color) {
  int x;
  int y;

    x=(((8*posx)-8)+1);
    y=(((8*posy)-8)+1);
    putpixel(x+1,y+1,color);
    putpixel(x+6,y+1,color);
    putpixel(x+1,y+2,color);
    putpixel(x+3,y+2,color);
    putpixel(x+4,y+2,color);
    putpixel(x+6,y+2,color);
    putpixel(x+2,y+3,color);
    putpixel(x+3,y+3,color);
    putpixel(x+4,y+3,color);
    putpixel(x+5,y+3,color);
    putpixel(x+2,y+4,color);
    putpixel(x+3,y+4,color);
    putpixel(x+4,y+4,color);
    putpixel(x+5,y+4,color);
    putpixel(x+1,y+5,color);
    putpixel(x+3,y+5,color);
    putpixel(x+4,y+5,color);
    putpixel(x+6,y+5,color);
    putpixel(x+1,y+6,color);
    putpixel(x+6,y+6,color);
}
//-------------------------------------------------------------
void dibujar_objeto(int posx, int posy, int color) {
  int x;
  int y;

    x=(((8*posx)-8)+1);
    y=(((8*posy)-8)+1);

    setcolor(color);
    line(x+1,y+1,x+6,y+1);
    line(x+1,y+2,x+6,y+2);
    line(x+1,y+3,x+6,y+3);
    line(x+1,y+4,x+6,y+4);
    line(x+1,y+5,x+6,y+5);
    line(x+1,y+6,x+6,y+6);
}
//-------------------------------------------------------------
void buscar_objeto_mismocolor(int pxh, int pyh, int *pxo, int *pyo,
				int color, lobjeto lo) {
  int fin;
  int i;
  int j;
  int pos;
  int px;
  int py;
  objeto o;

  fin=0;
  *pxo=*pyo=i=j=-1;
  while(!fin) {
    px=pxh+i;
    py=pyh+j;
    i++;
    if(i>1) {
      i=-1;
      j++;
    }
    if(j>1) {
      fin=1;
    }
    pos=buscar_objeto_listao(lo,px,py);
    if(pos) {
      o=ver_objeto_listao(lo,pos);
      if(color==consultar_color_objeto(o)) {
	*pxo=px;
	*pyo=py;
	fin=1;
      }
    }
  }
}
//-------------------------------------------------------------
void buscar_posicion_libre(int px, int py, int *pxlib, int *pylib,
				lobjeto lo, lhormiga lh) {
  int fin;
  int i;
  int j;
  int pos;

  fin=0;
  *pxlib=*pylib=-1;
  for(i=-1;(i<=1 && !fin);i++) {
    for(j=-1;(j<=1 && !fin);j++) {
      pos=buscar_objeto_listao(lo,px+i,py+j);
      if(!pos) {
	pos=buscar_hormiga_listah(lh,px+i,py+j);
	if(!pos) {
	  *pxlib=px+i;
	  *pylib=py+j;
	  fin=1;
	}
      }
    }
  }
}
//-------------------------------------------------------------
void buscar_objeto_alrededor(int px, int py, int *pxo, int *pyo, lobjeto lo){
  int fin;
  int i;
  int j;
  int pos;
  int nobjetos;
  objeto o;

  fin=0;
  *pxo=*pyo=-1;
  for(i=-1;(i<=1 && !fin);i++) {
    for(j=-1;(j<=1 && !fin);j++) {
      pos=buscar_objeto_listao(lo,px+i,py+j);
      if(pos) {
	o=ver_objeto_listao(lo,pos);
	nobjetos=nobjetos_mismocolor(px+i,py+j,consultar_color_objeto(o),lo);
	if(nobjetos<3) {
	  *pxo=px+i;
	  *pyo=py+j;
	  fin=1;
	}
      }
    }
  }
}
//-------------------------------------------------------------
int nobjetos_mismocolor (int px, int py, int color, lobjeto lo) {
  int nobjetos;
  int i;
  int j;
  int pos;
  objeto o;

  nobjetos=-1;
  for(i=-1;i<=1;i++) {
    for(j=-1;j<=1;j++) {
      pos=buscar_objeto_listao(lo,px+i,py+j);
      if(pos) {
	o=ver_objeto_listao(lo,pos);
	if(color==consultar_color_objeto(o)) {
	  nobjetos++;
	}
      }
    }
  }
  return(nobjetos);
}
//-------------------------------------------------------------
//*************************************************************
