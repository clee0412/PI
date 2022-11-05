//Crear un TAD que maneje palabras (taller 12 PI) 
#define LOWERTOUPPER(x) ((x - 'a') + 'A')

typedef struct palabraCDT { 
  char * letras; // arreglo dinámico
  int len; 
} palabraCDT; 

palabraADT crearPalabra(palabraADT p) { 
  return calloc(1, sizeof(palabraCDT)); 
}

void freePalabra(palabraADT p) { 
  if (p->len == 0) 
    return; 
  free(p->letras); 
  free(p); 
  p->len = 0; 
}

void mostrar(palabraADT p) { 
  if (p->len == 0) 
    return; 
  for (int i = 0; i < p->len; i++) 
    puts("%c", p->letras[i++]); 
}

palabraADT agregarLetra(palabraADT p, char letra) { 
  p->letras=realloc(p->letras, p->len+1); 
  p->letras[p->len] = letra; 
  p->len++; 
  return p; 
}

palabraADT concatenar(palabraADT p1, palabraADT p2) { 
}

palabraADT pasarAMayusculas(palabraADT p) {
  if (p->len == 0) 
    return p; 
  for (int i = 0; i < p->len; i++) {
    if (p->letras[i] >='a' && p->letras[i]<='z') { 
      p->letras[i] = LOWERTOUPPER(p->letras[i]); 
    }
  }
  return p; 
}
