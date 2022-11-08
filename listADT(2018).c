// TAD para listas de elementos no repetidos que permita recorrelo con dos criterios: en forma ascendente o por el orden de inserción de los elementos 

#include "listADT.h" 

typedef struct node { 
  elemType elem; 
  struct node * tailAsc; 
  struct node * tail; 
} TNode; 

typedef struct listCDT { 
  TNode * first; 
  TNode * current; 
  
  TNode * firstAsc; 
  TNode * firstCurrent; 
  
  TNode * lastAdded; // ??? 
} listCDT; 

listADT newList () { 
  return calloc(1, sizeof(listCDT)); 
}

static TList * addRec(TList list, elemType elem, listADT source) { 
  int c; 
  if (list == NULL || (c = compare(first->elem, elem)) > 0) {
    TList aux = malloc(sizeof(TNode)); 
    aux->elem = elem; 
    aux->tailAsc = NULL; 
    aux->tail = list; 
    
    if (source->lastAdded != NULL) // si por alguna razon no está seteado en NULL, el que sigue DEBE ser null por definición
      source -> lastAdded -> tail = aux; 
    else // no hay elementos 
      source->first = aux; 
    source->lastAdded = aux; // agrego en orden de inserción al final 
    
    return aux;
  }
  if (c < 0) 
    list->tail = addRec(list->tail, elem, source); 
  return list; 
}

void add(listADT list, elemType elem) { 
  list->first = addRec(list->first, elem, list); 
}       

void toBegin(listADT list) { 
  list->current = list->first; 
}

int hasNext(listADT list) { 
  return (list->current != NULL); 
}

// devuelve el elemento siguiente del iterador que recorre la lista en el orden de inserción 
// si no hay un elemento siguiente o no se invocó a toBegin aborta la ejecución 
elemType next(listADT list) { 
  if (!hasNext(list)) 
    exit (1); 
  TList aux = list->current; 
  list->current = list->current->tail; 
  return aux->elem; 
}

void toBeginAsc(listADT list) { 
  list->firstAsc = list->currentAsc; 
}

int hasNextAsc(listADT list) { 
  return (list->currentAsc != NULL); 
}

elemType nextAsc(listADT list) { 
  if (!hasNextAsc(list)) 
    exit (1); 
  TList aux = list->currentAsc; 
  list->currentAsc = list->currentAsc->tailAsc; 
  return aux->elem; 
}
