// cola de elementos con ITERADOR 

// se agregan unas funciones para poder iterar 

typedef struct node { 
  elemType elem; 
  struct node * tail; 
} TNode; 

typedef struct queueCDT { 
  TNode * first; 
  TNode * last; 
  TNode * iterador; // next ?? 
} queueCDT; 

queueADT newQueue(void) { 
  return calloc(1, sizeof(queueCDT)); 
}

int isEmpty(queueADT q) { 
  return (q->first == NULL); 
}

//agrega un elemento al final de la cola 
void queue(queueADT q, elemType elem) { 
  TNode * aux = calloc(1, sizeof(TNode)); 
  aux -> elem= elem; 
  if (isEmpty(queue)) { // solo hay un elemento
    q->first = q->last = aux; 
    q->last->next = NULL; 
  } else { 
    q->last->next = q->last;
    q->last = aux; 
  }
  return; 
}

//remueve un elemento del princpio de la cola y lo deja en out 
void dequeue(queueADT q, elemType * out) { 
  if (!isEmpty(queue)) {
    * out = q->first->elem;
    TNode * aux = q->first;
    if (q -> first == q -> last) { 
      q -> first = q -> last = NULL; 
    } else { 
      q -> first = q -> first -> next;
    }
    free(aux); 
    return;
  }
}

void toBegin(queueADT q) { 
  q->iterador = q -> first; 
}

int hasNext(queueADT q) { 
  return q->iterador != NULL; 
}

elemType next (queueADT q) { 
  if (!hasNext(q)) 
    exit (1);
  elemType aux = q->iterador->elem; 
  q->iterador = q->iterador->next; 
  return aux; 
}
