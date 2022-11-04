arrayADT 

typedef struct node { 
	elemType elem; 
	char isUsed; // 1 si está ocupado, 0 si no 
} node; 

// typedef int (*compare) (elemType, elemType); -> en .h

struct arrayCDT { 
	node * vec; // vector de elementos 
	size_t dim; // cantidad de elementos presentes 
	size_t size; // cantidad de espacio reservado
	compare cmp; 
}; 

typedef struct arrayCDT; 

arrayADT newArray() { 
	return calloc(1, sizeof(arrayCDT)); 
} 

void freeArray(arrayADT v) { 
	free(v->vec); 
	free(v); 
} 

// guardo en el idx el elem aunque esté usado o no
// si no está ocupado, prendo isUsed
// si ya estaba ocupado directamente lo cambio
// si idx > size entonces tengo que hacer realloc 
void put(arrayADT v, size_t idx, elemType elem) { 
	if (idx >= size) {
		v->vec = realloc(v->vec, sizeof(v->vec[0])*(idx+1)); 
		for (i = size; i <= idx; i++) 
			v->vec[i].isUsed = 0; 
		v->size = idx+1; 
	}
	v->vec[idx].elem = elem;		
	if (v->vec[idx].isUsed == 0) {
		v->vec[idx].isUsed = 1;  
		v->dim++; 
	}
}

void putIfNotUsed(arrayADT v, size_t idx, elemType elem) {
	if (v->vec[idx].isUsed == 1) 
		return; 
	put(v, idx, elem);  
}


size_t size (const arrayADT v) {
	return v->size; 
}

elemType * get(arrayADT v, size_t idx) { 
	if (idx >= v->size || v->vec[idx].isUsed==0)
		return NULL; 
	elemType * aux = malloc(sizeof(elemType)); 
	* aux = v->vec[idx].elem; 
	return aux; 
}

void delete(arrayADT v, size_t idx) { 
	if (idx >= v->size || v->vec[idx].isUsed==0)
		return; 
	v->vec[idx].isUsed = 0; 
	v->dim--; 

}


void deleteAll(arrayADT v, elemType elem) { 
	for (int i = 0; i < size; i++) {
		if ((cmp(v->vec[i].elem == elem) = 0) { 
			v->vec[i].isUsed = 0; 
			v->dim--; 
		}	
	}
}
