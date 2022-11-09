// Se desea implementar una colección que permita guardar elementos genéricos sin repeticiones. La colección se llamará rankingADT, ya que tiene la particularidad que tiene que servir para acceder fácilmente a los elementos que están al tope del ranking. Los elementos van "escalando posiciones" en el ranking a medida que son consultados.
// Si la colección tiene N elementos, se dice que el que está en el tope del ranking está en el puesto 1. El que está último en el ranking está en el puesto N del ranking.

 /* struct CDT 
   - elemType * 
   - size/dim
   - cmp 
   
   static swap 
   (bajar uno de ranking == sube el siguiente) 
   */ 

typedef int (*compare)(elemType e1, elemType e2); 

int compare (elemType e1, elemType e2) { 
  return e1-e2; 
}

typedef struct rankingCDT { 
  elemType * vec; 
  size_t size; 
  int cmp; 
} rankingCDT;

// crea un nuevo ranking
// recibe un vector con elementos, donde el primer elemento (elems[0]) está al tope del ranking (puesto 1), elems[1] está en el puesto 2, etc. 
// si dim es 0 significa que no hay elementos iniciales 
rankingADT newRanking(elemType elems[], size_t dim, int (*compare)(elemType source, elemType target)) {
  rankingADT new = malloc(sizeof(rankingCDT)); 
  new->size = dim; 
  new->cmp = compare; 
  if (dim > 0) { 
    new->vec = malloc(dim * sizeof(elemType)); 
    for (int i = 0; i < dim; i++) 
      new->vec[i] = elems[i]; 
  } else { 
    new->elems = NULL; 
  }
  return new; 
}

static int searchElem (rankingADT ranking, elemType elem, cmp compare) { 
  if (ranking->size == 0) 
    return -1; 
  for (int i = 0; i < ranking->size; i++) {
    if (compare(ranking->vec[i], elem) == 0)
      return i; 
    return -1; 
  }
}

static void swap (rankingADT ranking, size_t arriba, size_t abajo) { 
  elemType aux = ranking->vec[arriba]; 
  ranking->vec[arriba] = ranking->vec[abajo]; 
  ranking->vec[abajo] = aux; 
  return; 
}
//agrega un elemento en la posición más baja del ranking (al final), si no estaba 
// si el elemento estaba, es equivalente a accederlo, por lo que sube un puesto en el ranking 
void addRanking(rankingADT ranking, elemType elem) { 
  int i = searchElem(ranking, elem, ranking->cmp); 
  if (i == -1) { // agrego al final del vector 
    ranking->vec = realloc(ranking->vec, (++ranking->size)*sizeof(elemType)); 
    ranking->vec[ranking->size-1] = elem; 
    return; 
  } else if (i != 0) { // no es el primer elemento
    swap(ranking->vec[i], ranking->vec[i-1]); 
    return; 
  } else // es el primer elemento entonces no cambia nada 
    return; 
}

size_t size(const rankingADT ranking) { 
  return ranking->size; 
}

// si n es una posición válida del ranking, guarda en elem el elemento que está en el puesto n y retorna 1 
// si no hay elemento en la posición n, retorna 0 y no modifica * elem 
// este acceso también hace que el elemento suba un puesto en el ranking

int getByRanking(rankingADT ranking, size_t n, elemType * elem) { 
  if (ranking->size == 0 || n > ranking->size) 
    return 0; 
  * elem = ranking->vec[n-1]; 
  if (n > 1) 
    swap(ranking->vec[n-1], ranking->vec[n-2]); 
  return 1; 
}

/* top: entrada/salida
** Recibe cuántos elementos al tope del ranking se desean 
** Almacena cuántos pudo guardar (ver ejemplos)
** Si el ranking está vacío *top queda en cero y retorna NULL
*/

elemType * getTopRanking(const rankingADT ranking, size_t * top) { 
  size_t qty = ranking->size;  
  if (qty == 0) {
    * top = 0; 
    return new; 
  }
  if (*top > qty)
    *top = qty; 
  elemType * ans = malloc((*top)*sizeof(elemType)); 
  for (int i = 0; i < *top; i++) 
    ans[i] = ranking->vec[i]; 
  return ans; 
}

int contains(rankingADT ranking, elemType elem) { 
  int i = searchElem(ranking, elem); 
  if (i == -1) 
    return 0; 
  if (i != 0) {
    swap(ranking, i, i-1);
    return 1;
  }
  return 1; 
}

// baja una posición en el ranking para el elemento en la posición n 
void downByRanking(rankingADT ranking, size_t n) { 
  if (ranking->size == 0 || n < ranking->size) 
    return; 
  if (n > ranking->size) 
    swap(ranking, n, n-1); 
  // si ya es el último elemento no hago nada 
}

void freeRanking(rankingADT r) { 
  free(r->vec); 
  r->size = 0; 
  free(r); 
}
