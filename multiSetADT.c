// multi-set es un conjunto de elementos sin orden pero donde cada elemento puede aparecer más de una vez

typedef struct node { 
  elemType elem; 
  size_t cant; 
  struct node * tail; 
} TNode; 

typedef struct multiSetCDT {
  TNode * first; 
  size_t size; // cuantos elementos distintos hay 
} multiSetCDT; 

multiSetADT newMultiSet() { 
  return calloc(1, sizeof(multiSetCDT)); 
}

// inserta un elemento. Retorna cuántas veces está elem en el conjunto luego de haberlo insertado (p.e. si es la primera inserción retorna 1) 

static TNode * addRec(TNode * first, elemType elem, int * sizeAux) { 
  int c; 
  if (first == NULL || (c = compare(first->elem, elem) > 0)) {
    TNode * new = malloc(sizeof(TNode)); 
    new -> elem = elem; 
    new -> cant = 1; 
    new -> tail = first; 
    *sizeAux = 1; 
    return new; 
  }
  if (c < 0)   
    first->tail = addRec(first->tail, elem, sizeAux); 
  // si ya existe el elemento solo incremento la cantidad 
  first->cant++; 
  return first; 
}

unsigned int add (multiSetADT multiSet, elemType elem) { 
  // como es una lista, me conviene usar una función recursiva 
  int sizeAux = 0; 
  multiSet->first = addRec(multiSet->first, elem, &sizeAux); 
  multiSet->size+=sizeAux; 
  return multiSet->first->cant; 
}

static TNode * belongs(TNode * first, elemType elem) { 
  int c; 
  if (first == NULL || (c = compare(first->elem, elem)) > 0) // nunca está 
    return NULL; 
  if (c < 0) 
    first->tail = belongs(first->tail, elem); 
  return first; 
}

unsigned int count(const multiSetADT multiSet, elemType elem) { 
  TNode * aux = belongs(multiSet->first, elem); 
  if (aux != NULL) 
    return aux->cant; 
  return 0; 
}

unsigned int size (multiSetADT multiSet) { 
  return multiSet->size; 
}

// type se refiere a si es remove o si es removeALL 
static TNode * removeRec(TNode * first, elemType elem, int type, int * noHayMas) { 
  int c; 
  if (first == NULL || (c = compare(first->elem, elem)) > 0) // nunca está 
    return first; // retorno la lista vacía o la misma lista sin haber removido nada 
  if (c == 0) { // encontré el elemento que tengo que remover 
    first->cant--; 
    if (first->cant == 0 || type == 1) { // si no quedaron más elementos o hay que hacer un REMOVEALL
      TNode * aux = first; 
      first = first->tail; 
      free(aux); 
      // falta retornar un flag que indique si se borraron todos los elementos así cambio size 
      *noHayMas = 1; 
    }
  }
  first->tail = removeRec(first->tail, elem, type); 
  return first; 
}

int remove(multiSetADT multiSet, elemType elem) {
  int noHayMas = 0; 
  multiSet->first = removeRec(multiSet->first, elem, 0, &noHayMas); 
  if (noHayMas == 1) 
    multiSet->size--; 
  return multiSet->first->cant; 
}

void removeAll(multiSetADT multiSet, elemType elem) { 
  int noHayMas = 1; 
  multiSet->first=removeRec(multiSet->first, elem, 1, &noHayMas); 
  multiSet->size--; 
  // remove el nodo 
}

// retorna un vector con los elementos que menos aparecen en el conjunto
// si el conj está vacío retorna NULL 
// en el parámetro de salida dim almacena la cantidad de elementos del vector 

elemType * minElements(const multiSetADT multiSet, int * dim) { 
  if (multiSet->first == NULL) 
    return NULL; 
  int i, minValue; 
  elemType * vec = NULL; 
  TNode * aux = multiSet->first; 
  for (i = 0, minValue = aux->cant; aux != NULL; aux=aux->tail) { 
    if (minValue > aux->cant) { 
      i = 0; 
      minValue = aux->cant; 
    }
    if (i % BLOQUE == 0) { 
      vec = realloc(vec, (i+BLOQUE)*sizeof(elemType)); 
      vec[i++]=aux->elem; 
    }
  }
  vec = realloc(vec, i*sizeof(elemType));
  *dim = i; 
  return vec; 
}
 
