typedef struct node * TList; 

typedef struct node { 
  int elem; 
  struct node * tail; 
} TNode; 

// Escribir una función recursiva SUBLIST que recibe únicamente los parámetros: LIST, FROM, TO y retorna una NUEVA LISTA que están entre las posiciones FROM y TO INCLUSIVE. El primer elemento está en la posición 0. 

TList sublist(TList list, unsigned int from, unsigned int to) { 
  if (list == NULL || from < 0 || to < from) 
    return NULL; 
  if (from > 0) 
    return sublist(list->tail, from-1, to-1); 
  // si from == 0
  TList aux = malloc(sizeof(TNode)); 
  aux->elem = list->elem; 
  aux->tail = sublist(list->tail, from, to-1); 
  return aux; 
}


0 -> 1 -> 2 -> 3 -> 4 -> NULL 

  sublist(list, 1, 3) 
  aux = sublist(list->tail, 2, 3); --> aux = sublist(list->tail, 3, 3); = NULL
  
  si from == 0 
