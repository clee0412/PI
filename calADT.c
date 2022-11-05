// TAD de un calendario de eventos. Un evento consiste en su nombre y la fecha del mismo. 
// campos de fecha(date) : dia, mes, año
// calendario admite hasta un evento por fecha 

typedef struct tDate { 
  unsigned char day; 
  unsigned char month; 
  unsigned short year; 
} tDate; 

typedef struct tEvent { 
  char * eventName; 
  tDate date; 
} tEvent; 

typedef struct nodeCDT { 
  tEvent event; 
  struct node CDT * tail; 
} DNode; 

typedef struct calCDT { 
  DNode * first; 
  DNode * current; // para iterar 
  DNode * last; 
  size_t dim; // cantidad de eventos 
} calCDT; 

calADT newCal () { 
  return calloc(1, sizeof(calCDT)); 
}

/* agrega un evento al calendario. si ya existe un evento en el calendario para la fecha del evento la función no lo agrega y retorna 0. Si pudo agregar el evento retorna 1. Se asume que la fecha recibida es válida*/ 

int compare(char d1, char d2) { 
  return strcmp(d1, d2); 
}
int compareDate (tDate d1, tDate d2) { 
  if (d1.year == d2.year) 
    if (compare(d1.month, d2.month) == 0) 
      if (compare(d1.day, d2.day) == 0) 
        return 0; 
  return 1; 
}

DNode * addEventRec(DNode * first, tEvent event) { 
  * flag = 1; 
  if (first == NULL) {  // lo agrego al principio 
    DNode * newEvent = malloc(sizeof(DNode)); 
    newEvent -> event = event; 
    newEvent -> tail = NULL; 
    return newEvent; 
  }
  if (current->event.date < event.date) { 
    current->tail = addEventRec(current->tail, event); 
    return current; 
  }
  if (current->event.date == event.date) {
    flag = 0; 
    return NULL; 
  }
  DNode * newEvent = malloc(sizeof(DNode)); 
  newEvent->event = event; 
  newEvent->tail = first; 
  return newEvent; 
}

int addEvent(calADT cal, tEvent event) { 
  if (cal == NULL) 
    return 0; 
  int flag; 
  cal->first = addEventRec(cal->first, event, &flag); 
  cal->dim += flag; 
  return flag; 
}


void toBegin(calADT cal) { 
  if (cal == NULL) 
    return; 
  cal->current = cal->first; 
}

tEvent nextElement(calADT cal) { 
  if (cal == NULL || cal->current == NULL || cal->current->tail == NULL) 
    return NULL; // no hay siguiente elemento 
  return cal->current->tail->event; 
}

int hasNext(calADT cal) { 
  if (cal == NULL) 
    return 0; 
  tEvent aux = nextElement(cal); 
  if (aux != NULL) 
    return 1; 
  return 0; 
}









