// escribir una función recursiva que, recibiendo únicamente una lista en forma NO descendente (ascendente o igual), elimine de LA MISMA elementos repetidos. No utilizar funciones auxiliares. 

typedef struct node * TList; 

typedef struct node { 
  int elem; 
  struct node * tail; 
} TNode; 

void eliminaRepetidos(TList list) { 
  if (list == NULL || list->tail == NULL) 
    return; 
  if (list->elem == list->tail->elem) {
    TList aux = list->tail->tail; 
    free(list->tail); 
    list->tail = aux;
    eliminaRepetidos(list); 
  }
  eliminaRepetidos(list->tail); 
}
