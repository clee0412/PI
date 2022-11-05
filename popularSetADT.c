#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "popularSetADT.h" 

#define BLOQUE 10 

typedef struct elemType { 
  int code;
  char name[20]; 
} elemType;

static int compare (elemType e1, elemType e2) { 
  return e1.code - e2.code; 
} 

typedef struct popularSetCDT * popularSetADT;

typedef struct popularSetCDT { 
  elemType * v; // vector de elementos 
  unsigned int size; // cantidad de elementos 
  unsigned int dim; // cantidad de espacio reservado 
  unsigned int iterador;
} popularSetCDT; 

popularSetADT newPopularSet() { 
  return calloc(1, sizeof(popularSetCDT));
}

unsigned int size (popularSetADT popularSet) {
  return popularSet->size;
} 

void toBegin(popularSetADT s) { 
  s->iterador = 0;
}

int hasNext(popularSetADT s) {
  return s->iterador < s->size; // retorna 1 si hay un siguiente elemento, 0 si iterador es mayor o igual a size, lo cual implica que no hay siguiente elemento
}

elemType next (popularSetADT s) { 
	if (!hasNext(s)) 
		exit (1); 
	return s->v[iterador+1];
}

void freeSet(popularSetADT set) {
	free(set->v);
	free(set);
}

unsigned int add(popularSetADT set, elemType elem) { 
	for (int i = 0; i < set->size; i++) 
		if (compare(set->vec[i], elem) == 0) // ya existe el elemento 
			return 0; // no lo agrega 
	// como no existe el elemento, lo agrega al principio
	if (set->dim % BLOQUE == 0) { // no hay mas espacio 
		set->v=realloc(set->v, sizeof(elemType)*(set->dim+BLOQUE)); 
		set->dim+=BLOQUE;
	}
	set->v[set->size] = elem;
	set->size++; 
	return 1;
}

static void swap(elemType * vec, size_t i) { 
	elemType aux = vec[i];
	vec[i] = vec[i-1];
	vec[i-1]=aux;
}

elemType * get (popularSetADT set, elemType elem) { 
	for (int i = 0; i < set->size; i++) 
		if (compare(set->v[i],elem) == 0) {
			elemType * aux = malloc(sizeof(elemType)); 
			*aux = set->v[i]; 
			if (i != 0)
				swap(set->v, i); 
			return aux;
		}
	return NULL; 
}
