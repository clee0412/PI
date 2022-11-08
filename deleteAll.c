// recibe únicamente dos listas de enteros ordenados en forma ascendente (sin repetidos) y elimine de la primera lista los elementos que pertenezcan a la segunda lista 

// retorna la misma lista 

TList deleteAll (TList l1, TList l2) { 
  if (l1 == NULL || l2 == NULL) 
    return l1; 
  
  if (l1->elem > l2->elem) 
    return deleteAll(l1, l2->tail); 
  
  if (l2->elem > l1->elem) 
    return deleteAll(l1->tail, l2); 
  
  // si son iguales lo elimino 
  TList aux = l1->tail; 
  free(l1); 
  l1->tail = aux; 
  return aux; 

}
