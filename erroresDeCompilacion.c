#include <stdio.h>
#define DIM 20 

typedef struct {
  int a; 
	int b;
} Coordenada;

typedef Coordenada * PCoord; 

typedef struct { 
	char nombre1[DIM]; // como es estatico, tengo que usar strcpy 
	char * nombre2;
	Coordenada punto1; // uso un punto
	PCoord punto2; // uso -> 
} TipoX;

int main (void) { 
	TipoX var1;
	var1.nombre1= "nombre1"; // error de compilacion
	var1.nombre2 = "nombre2"; // NO tiene error 
	var1.punto1.a = 10; 
	var1.punto1.b = 30;  
	var1->punto2.a = 20; // error de compilacion
	var1.punto2->b = 50; // error de ejecucion 
	return 0;
}
