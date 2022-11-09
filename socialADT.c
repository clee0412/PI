#define MAX 20 

typedef struct related { 
  char name[MAX]; 
  struct person * tail; 
} tRelated; 

typedef struct person { 
  char name[MAX]; 
  tRelated * firstR; 
  size_t cantR; 
  struct person * nextP; 
} tPerson; 

typedef struct socialCDT { 
  tPerson * p; 
  size_t cantP; 
} socialCDT; 

const char * copyStr(const char * s) { 
  char * aux = malloc(strlen(s)+1); 
  return strcpy(aux, s); 
}

int compare (char * s1, char * s2) {
  return strcmp(s1, s2); 
}

socialADT newSocial { 
  return calloc(1, sizeof(socialCDT)); 
}

void freeRelated(tRelated * r) { 
  if (r == NULL) 
    return; 
  freeRelated(r->nextR); 
  free(r); 
}

void freePerson(tPerson * p) {
  if (p == NULL) 
    return; 
  freeRelated(p->firstR); 
  freePerson(p->nextP); 
  free(p); 
}

void freeSocial(socialADT soc) { 
  freePerson(soc->p); 
  free(soc); 
}

static tPerson * addPersonRec (tPerson * person, const char * name) {
  int c; 
  if (person == NULL || (c = compare(person->name, name)) > 0) { // agrego a la persona 
    tPerson * auxP = malloc(sizeof(tPerson)); 
    strncpy(auxP->name, name, MAX); 
    auxP->cantR = 0; 
    auxP->firstR = NULL; 
    auxP->name[MAX] = 0; // si strncpy copia la cantidad justa, no agrega ceros por lo tanto hay que agregarlos nosotros 
    auxP->nextP = person; 
    *ok = 1; // se pudo agregar 
    return auxP; 
  }
  if (c < 0) 
    person->nextP = addPersonRec(person->nextP, name, ok); 
  return person; 
}
void addPerson(socialADT soc, const char * name) { 
  int ok = 0; 
  soc->p = addPersonRec(soc->people, name, &ok); 
  if (ok) 
    soc->sizeP++; 
}

static tRelated * addRelatedRec(tRelated first, char * name, int * ok) { 
  int c; 
  if (first == NULL || (c = compare(first->name, name)) >= 0) {
    tRelated * auxR = malloc(sizeof(tRelated)); 
    strncpy(auxR->name, name, MAX); 
    auxR->name[MAX] = 0; 
    auxR->tail = first; 
    * ok = 1; 
    return auxR; 
  }
  // if c < 0 
  first->nextR = addRelatedRec(first->nextR, name, ok);
  return first; 
}

static tPerson * addAux(tPerson person, const char * name, const char * related) { 
  int c;
  int ok = 0; 
  if (person == NULL || (c = compare(person->name, name)) > 0) {
    return person; 
  } 
  if (c < 0) 
    person->nextP = addAux(person->nextP, name, related); 
  // si c == 0 
  person->firstR = addRelatedRec(person->firstR, related, &ok); 
  return person; 
}

void addRelated(socialADT soc, const char * name, const char * related) { 
  int ok = 0; 
  soc->p = addAux(soc->p, name, related, &ok);
  if (ok) 
    soc->p->cantR++; 
}

static tPerson * findPerson (tPerson * first, const char * name) { 
  tPerson * aux = first; 
  while (aux != NULL) {
    int c = strcmp(aux->name, name); 
    if (c == 0) 
      return aux; 
    if (c < 0) 
      return NULL; 
    aux = aux->nextP; 
  }
  return NULL; 
}

char ** related (const socialADT soc, const char * person ) { 
  char ** ans; 
  tPerson * auxP = findPerson(soc->p, person); 
  int i = 0; 
  if (aux != NULL) {
    ans = malloc((auxP->cantR + 1)*sizeof(char*)); 
    tRelated * auxR = auxP->firstR; 
    while(auxR != NULL) {
      ans[i++] = copyStr(auxR->name); 
      auxR = auxR->nextR; 
    }
  }
  else 
    ans = malloc(sizeof(char *)); 
  ans[i] = NULL; 
  return ans; 
    
}
