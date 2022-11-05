// guarda coleccion de elementos no repetidos 
// los elementos mas populares (los que mas se consultan) estan al principio de la coleccion
// de esta forma sera mas rapido acceder a los elementos que mas veces se consulten 
// ESTO implica que hay mucho movimiento --> capaz conviene usar vectores 
// cuando se inserta un elemento no repetido se lo inserta al FINAL 
// cuando se consulta un elemento, es enviado al principio de la coleccion 

/* 
EN .H
typedef ... elemType; 
static int compare (elemType e1, elemType e2)
	....
*/

typedef struct node { 
	elemType elem; 
	struct node * tail; 
} TNode; 

typedef struct moveToFrontCDT { 
	TNode * first; 
	TNode * next; 
	size_t size;
	TNode * last; // este no entiendo para que se necesita 
}

moveToFrontADT newMoveToFront() { 
	return calloc(1, sizeof(moveToFrontCDT)); 
} 

unsigned int size(moveToFrontADT m) { 
	return m->size; 
} 

void toBegin(moveToFrontADT m) { 
	m->next = m->first;
}

int hasNext(moveToFrontADT m) { 
	return m->next != NULL; 
} 

elemType next(moveToFrontADT m) { 
	if (!hasNext(m)) 
		exit(1); 
	elemType aux = m->next->elem;
	m->next = m->next->tail;
	return aux;
} 

static TNode * addRec(TNode * first, elemType elem, int * flag) { // agrego el elemento al final
	int c;
	if (first == NULL || (c=compare(first->elem, elem)) > 0) { 
		TNode * aux = malloc(sizeof(TNode)); 
		aux->elem = elem; 
		aux->tail = first; 
		*flag = 1;
		return aux; 
	} 
	if (c < 0) 
		first->tail = addRec(first->tail, elem, flag); 
	return first;
} 
		
unsigned int add(moveToFrontADT m, elemType elem) { 
	int flag = 0: 
	m->last = addRec(m->first, elem, &flag); 
	m->size+=flag;
	return flag; 
} 

static elemType * getRec(TNode * first, elemType elem) { 
	int c;
	if (first==NULL || (c=compare(first->elem, elem)) > 0) 
		return NULL; 
	if (c == 0) { 
		elemType * aux = malloc(sizeof(elemType)); 
		*aux = first->elem; 
		// ahora debo ubicar first al principio de la lista 
	

// retorna una copia del elemento. si no existe retorna NULL
// para saber si el elemento esta, usa la funcion compare 
// si el elemento estaba lo ubica al principio (si no era el primero) 
elemType * get(moveToFrontADT m, elemType elem) { 
	elemType * aux = getRec(m->first, elem); 
	
	return aux;
}
	


	
	
