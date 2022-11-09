// Se desea crear un TAD que dé soporte para almacenar y recuperar frases, donde cada frase tiene asociada una clave numérica (un valor entero positivo). Las claves son únicas (no puede haber dos frases con la misma clave, aunque sí podría pasar que dos claves tengan la misma frase).
// No hay un límite previsto para la longitud de cada frase, pueden ser unos pocos o miles de caracteres.


typedef struct phrase { 
  char * phrase; 
  size_t len; 
} phrase; 


typedef struct phrasesCDT { 
  phrase * phrases; // vector de frases porque hay mucha búsqueda de clave 
  size_t keyFrom; 
  size_t keyTo; 
  size_t size; // cantidad de frases almacenadas 
} phrasesCDT; 

phrasesADT newPhrasesADT(size_t keyFrom, size_t keyTo) { 
  if (keyFrom < 0 || keyTo < keyFrom) 
    return NULL; 
  phrasesADT new = malloc(sizeof(phrasesCDT)); 
  new->keyFrom = keyFrom; 
  new->keyTo = keyTo; 
  new->size = 0; 
  new->phrases = calloc(keyTo-keyFrom+1, sizeof(phrase)); // OJO!!! hay la cnatidad de espacio a reservar está dado (keyTo-keyFrom+1) por lo que no necesito usar bloques ni un dim aparte 
  return new; 
}

void freePhrases(phrasesADT ph) { // pueden no estar en espacio contiguo 
  int dim = ph->keyTo-ph->keyFrom+1; 
  for (int i = 0; i < dim; i++) 
    free(ph->phrases[i].phrase); 
  free(ph->phrases); 
  ph->size = 0; // en las rtas no hacen esto, y no entiendo por qué (siento que es necesario poner size a 0) 
  free(ph); 
}

#define BLOCK 20 (dim máx para empezar para el len de la frase) 

static char * copy(char * s, const char * phrase, size_t * len) { 
  char * ans = s; 
  
  size_t reserved = * len; 
  int i; 
  for (i = 0; phrase[i] != 0; i++) { 
    if (i == reserved) {
      reserved+=BLOCK; 
      ans = realloc(ans, reserved); 
    }
    ans[i] = phrase[i]; 
  }
  ans = realloc(ans, i+1); 
  ans[i] = 0; 
  *len = i; 
  return ans; 
  
  }
}
  
//agrega una frase. si la clave key es inválida retorna 0, sino retorna 1 
//si ya hay una frase asociada a la clave, actualiza la frace almacenada, reemplazandola por el parámetro phrase (es decir, no hay que actualizar ph->size pero sí ph->phrases[i].len)
int put(phrasesADT ph, size_t key, const char * phrase) { 
  if (key < ph->keyFrom || key > ph->keyTo) 
    return 0; 
  
  int pos = key-keyFrom;
  if (ph->phrases[pos].phrase == NULL) 
    ph->size++; 
  ph->phrases[pos].phrase = copy(ph->phrases[pos].phrase, phrase, &(ph->phrases[pos].len)); 
  return 1;
}

// retorna una copia de la frase asociada a la clave key. si no hay frase asociada a la clave key retorna NULL, lo mismo si la clave es inválida 

char * get(const phrasesADT ph, size_t key) { 
  int pos = key-ph->keyFrom; 
  if (key < ph->keyFrom || key > ph->keyTo || ph->phrases[pos].phrase == NULL) 
    return NULL; 
  char * ans = malloc(sizeof(ph->phrases[pos].len+1)); 
  strcpy(ans, ph->phrases[pos].phrase); 
  return ans; 
}

// funcion auxiliar para usar tanto en concat como en concatALL 

static char * copyPhrases(phrase v[], size_t from, size_t to) { 
  // tenemos la longitud de cada frase, podemos hacer reallocs por cada frase y strcpy de cada una 
  char * ans = NULL; 
  size_t total = 0; 
  for (int i = from; i <= to; i++) { 
    size_t add = v[i].len; 
    if (add > 0) { // hay un string 
      ans = realloc(ans, total + add + 1); 
      strcpy(ans+total, v[i].phrase); 
      total += add; 
    }
  }
  if (total == 0) { 
    ans = malloc(1); 
    *ans = 0; 
  }
  return ans; 
}

// retorna un string con todas las frases concatenadas. SI no hay frases retorna un string vacío. 

char * concatAll(const phrasesADT ph) { 
  if (ph->size == 0) 
    return 0; // retorna un string vacío 
  char * ans = malloc(sizeof()); 
  for (i = 0; i < keyTo-keyFrom+1; i++) { 
    
  }
}

char * concatAll(const phrasesADT ph) {
    return copyPhrases(ph->phrases, 0, ph->keyHigh - ph->keyLow);
}

char * concat(const phrasesADT ph, size_t from, size_t to) {
    if ( from < ph->keyLow || to > ph->keyHigh || from > to) {
        return NULL;
    }
    return copyPhrases(ph->phrases, from - ph->keyLow, to - ph->keyLow);
}
