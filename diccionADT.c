#include <string.h>

#define LETRAS ('z'-'a'+1) // 26 letras 


typedef struct palabra { 
  char * palabra; 
  char * significado;  
} tPalabra; 

typedef struct listaPalabras {
  tPalabra * lista; 
  size_t cant; 
} tListaPalabras; 

typedef struct diccioCDT { 
  tListaPalabras inicial[LETRAS]; 
} diccioCDT; 
  
typedef int compare (char * p1, char * p2) { 
  return strcmp(p1,p2); 
}

diccioADT creaDiccionario(void) { 
  diccioADT aux = malloc(sizeof(diccioCDT)); 
  int i;
  for (i = 0; i < LETRAS; i++) { 
    aux->inicial[i].lista = NULL; 
    aux->inicial[i].cant = 0; 
  }
  return aux; 
}

// es lo mismo que hacer return calloc(1, sizeof(diccioCDT)); 

void liberaDiccionario(diccioADT dic) { 
  for (int i = 0; i < LETRAS; i++) { 
    for (int j = 0; j < dic->inicial[i].cant; j++) {
      free(dic->inicial[i].lista[j].palabra); 
      free(dic->inicial[i].lista[j].significado); 
    } 
    free(dic->inicial[i].lista); 
  }
  free(dic); 
}

int agregaPalabra(diccioADT dic, char * palabra, char * significado) {
  int indice, total, ubic; 
  int lenPal = strlen(palabra); 
  int lenSign = strlen(significado); 
  if (lenPal > MAXWIDTH || lenSign > MAXSIGNIFICADO) { 
    return ERROR_LEN; 
  }
  indice = tolower(palabra[0])-'a'; 
  for (int i = 0; i < dic->inicio[indice].cant; i++) {
    int c; 
    if (c=compare(dic->inicio[indice].lista[i].palabra, palabra) == 0) 
      return ERROR_REPE;
    // si no encuentra la palabra entonces la tiene que agregar 
    // primero armo espacio
    total = dic->inicial[indice].cant; 
    dic->inicio[indice].lista = realloc(dic->inicio[indice].lista, sizeof(tPalabra)*(1+total)); 
    // agrego palabra 
    dic->inicial[indice].lista[total].palabra = malloc(lenPal+1); 
    strcpy(dic->inicial[indice].lista[total].palabra, palabra);                                
    // agrego significado 
    dic->inicial[indice].lista[total].significado = malloc(lenSign+1); 
    strcpy(dic->inicial[indice].lista[total].significado, significado);
    dic->inicio[indice].cant += 1; 
    return 1; 
  } 
}
