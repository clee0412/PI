// crear un TAD que maneje una cola de enteros 


typedef struct node { 
  elemType value; 
  struct node * next; 
} TNode; 

typedef struct queueCDT { 
  TNode * first; 
  TNode * last; 
} queueCDT; 

queueADT newQueue() { 
  return calloc(1, sizeof(queueCDT)); 
}

void freeRec(TNode * first) { 
  if (first == NULL) 
    return; 
  freeRec(first->next); 
  free(first); 
}

void freeQueue(queueADT q) { 
  freeRec(q->first); 
  free(q); 
}

void queue(queueADT q, elemType elem) { 
  TNode * aux = calloc(1, sizeof(TNode)); 
  aux -> value = elem; 
  if (isEmpty(queue)) { 
    q->first = aux; 
    q->last = aux; 
  } else { 
    q->last->next = aux; 
    q->last = aux; 
  }
  return; 
}

void dequeue(queueADT q, elemType * elem) { 
  if (!isEmpty(queue)) { 
    * elem = q->first->value; 
    TNode * currentFirst = q->first; 
    if (currentFirst == q->last) { // solo hay un elemento 
      q->first = q->last = NULL; 
    } else { 
      q->first = q->first->next; 
    }
    free(currentFirst); 
    return; 
  }

int isEmpty(queueADT q) { 
  return (q->first == NULL); 
}
