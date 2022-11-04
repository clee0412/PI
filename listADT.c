// LISTADT 

typedef struct { 
	double key; 
	char * text; 
} elemType; 

typedef struct node { 
	elemType elem; 
	struct node * tail; 
} TNode; 

typedef TNode * TList; 

typedef struct listCDT {
	TList first; 
	TList next; 
	size_t size; // cantidad de nodos 
	compare cmp; 	
}

typedef int (*compare) (elemType e1, elemType e2) { 
	if (e1.key > e2.key) 
		return 1; 
	if (e1.key < e2.key) 
		return -1; 
	return 0; 
}

listADT newList(compare cmp) { 
	listADT aux = calloc(1, sizeof(listCDT)); 
	aux->cmp = cmp; 
	return aux; 
}

void freeRec(TList first) {
	if (first == NULL) 
		return; 
	freeRec(first->tail); 
	free(first); 
}
void freeList(listADT list) { 
	freeRec(list->first); 
	free(list); 
}

size_t size(const listADT list) { 
	return list->size; 
}


static int belongsRec(TList first, elemType elem, compare cmp) { 
	int c; 
	if (first == NULL || (c = cmp(first->elem, elem)) > 0) 
		return 0; // nunca va a estar elem 
	if (c == 0) 
		return 1; 
	first->tail = belongsRec(first->tail, elem, cmp); 
}


int belongs (const listADT list, elemType elem) { 
	return belongsRec(list->first, elem, list->cmp); 
}

//flag guarda 1 si se insertó, 0 si no 

static TList addRec(TList first, elemType elem, compare cmp, int * flag) {
	int c; 
	if (first == NULL || (c=cmp(first->elem, elem) > 0) {	
		TList aux = malloc(sizeof(TNode)); 
		aux -> elem = elem; 
		aux->tail = first; 
		*flag = 1; 
		return aux; 
	}
	if (c < 0) 
		first->tail = addRec(first->tail, elem, cmp, flag); 
	return first; 
}

int add (listADT list, elemType elem) { 
	int flag = 0; 
	list->first = addRec(list->first, elem, list->cmp, &flag);
	list->size+=flag;   
	return flag; 
}

int indexOfRec(TList first, elemType elem, compare cmp, int index) {
	int c; 
	if (first == NULL || (c = cmp(first->elem, elem)) > 0) 
		return -1; 
	if (c == 0) 
		return index;  
	return (first->tail, elem, cmp, index+1); 
}


int indexOf(const listADT list, elemType elem) { 
	int index = 0; 
	return indexOfRec(list->first, elem, list->cmp, index); 
}

elemType * getRec(TList first, unsigned int idx, int idxActual=0) {
	
	if (first == NULL) // no hay elementos 
		return NULL; 
	
	if (idx == idxActual) {
		elemType * aux = first->elem; 
		return aux; 
	}
	
	return getRec(first->tail, idx, idxActual+1); 

elemType get (const listADT list, unsigned int idx) { 
	if (idx > list->size-1) // list->size-1 es el ultimo elemento	
		exit (1);
	 
	int idxActual = 0; 
	
	elemType * aux = getRec(list->first, idx, idxActual); 
	if (aux == NULL) 
		exit (1); 
	return aux; 
		
}
