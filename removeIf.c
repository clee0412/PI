typedef struct node * TList; 

typedef struct node { 
	int elem; 
	struct node * tail; 
} TNode;

TList removeIf(TList list, int (*criterio)(int)) { 
	if (list == NULL) 
		return; 
	
	if (criterio(list->elem)) == 1) { 
		TList aux = list->tail;
		free(list);
		aux = removeIf(aux, criterio);
		return aux;
	} 
	
	list->tail = removeIf(list->tail); 
	return list; 
