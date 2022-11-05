typedef TNode * TList; 

typedef struct node {
	int elem;
	struct node * tail; 
} TNode; 

TList inter(TList l1, TList l2) { 
	if (l1 == NULL || l2 == NULL) 
		return NULL; 
	
	if (l1->elem < l2-> elem) 
		return inter(l1->tail, l2); 
	if (l1->elem > l2->elem) 
		return inter(l1, l2->tail); 
	// si llego hasta aca es porque l1 == l2 
	// entonces creo la lista y voy agregando los elementos 
	TList aux = malloc(sizeof(TNode)); 
	aux->elem = l1->elem; 
	aux->tail = inter(l1->tail, l2->tail); 
	return aux; 
}
