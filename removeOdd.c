//función recursiva removeOdd que recibiendo únicamente una lista, elimine de la misma todos los elementos en posición impar (asumiento que el primer elemento está en la posición par 0). No utilizar funciones auxiliares 

// ejemplos 
// 1->2->3->4->5->NULL ----------------> 1->3->5->NULL 
//6->7->8->9->NULL --------------------> 6 -> 8-> NULL 
// 10->NULL ---------------------------> 10 -> NULL (sin cambios) 
// NULL -------------------------------> NULL (sin cambios) 

typedef struct node * TList; 

typedef struct node { 
  int elem; 
  struct node * tail; 
} TNode; 

TList removeOdd(TList list) { 
  if (list == NULL || list->tail == NULL) // solo tengo un elemento o ninguno 
    return list; 
  TList aux =  list->tail->tail; 
  free(list->tail); 
  list->tail = aux; 
  removeOdd(list->tail); 
  return list; 
}
