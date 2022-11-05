// se desea mantener una lista de contactos (addressBook) 
// por cada contacto se guarda únicamente su nombre y número de teléfono 
// cada contacto estará dentro de un grupo, y cada grupo se identifica por su nombre 
// no puede haber dos grupos con el mismo nombre, sin diferencia entre mayúsculas y minúsculas (el grupo "personal" es el mismo que "Personal"
// dentro de un grupo no puede haber dos contactos con el mismo nombre (tampoco diferencia entre mayúsculas y minúsculas), pero sí puede repetirse entre DISTINTOS GRUPOS 

typedef struct contacto { 
  char * num; 
  char * tel; 
  struct contacto * nextContacto; 
} tContacto; 

typedef struct grupo { 
  char * nombre; 
  tContacto * primerContacto; 
  struct grupo * nextGrupo; 
} tGrupo; 

typedef struct addressBookCDT { 
  tGrupo * primerGrupo; 
  tGrupo * currentGrupo; 
  tContacto * currentContacto; 
} addressBookCDT; 

addressBookADT newAddressBook() { 
  return calloc(1, sizeof(addressBookCDT)); 
}

int compare (char * c1, char * c2) { 
  return strcmp(c1, c2); 
}

// --------------------------------------------------------------------------------------------------------
/* Almacena un nuevo grupo. Si el grupo existe, no hace nada.
** No diferencia entre minúsculas y mayúsculas */

tGrupo * addGroupRec(tGrupo group, char * groupName, int * flag) { 
  int c; 
  if (group == NULL || (c = strcasecmp(group->nombre, groupName))>0) {
    // lo agrego al principio
    tGrupo * aux = calloc(1, sizeof(tGrupo)); 
    aux->name = malloc(strlen(groupName)+1); 
    strcpy(aux->name, groupName); 
    aux->nextGrupo = group; 
    * flag = 1; 
    return aux; 
  }
  if (c<0) 
    group->nextGrupo = addGroupRec(group->nextGrupo, groupName, flag); 
  // y si ya existe no agrega y retorna directamente 
  return group; 
}

int addGroup(addressBookADT a, const char * groupName) { 
  char flag = 0; 
  a->primerGrupo = addGroupRec(a->primerGrupo, groupName, &flag); 
  return flag;
}

//----------------------------------------------------------------------------------------------------------------------------

tContact addContactRec(TGrupo group, tContact contact, int * flag) { 
  int c; 
  if (group == NULL || (c = strcasecmp(group->firstContact.nom, contact->name)) > 0) { 
    tContact aux = calloc(1, sizeof(tContact)); 
    aux->nom = malloc(strlen(contact->nom)+1); // * char que como es 1 no lo pongo 
    strcpy(aux->nom, contact->nom); 
    aux->tel = malloc(strlen(contact->tel)+1); 
    strcpy(aux->tel, contact->tel); 
    aux->nextContact = group->firstContacto; 
    * flag = 1; 
    return aux; 
  }
  if (c < 0) 
    group->firstContact = addContactRec(group, contact, flag); 
  return group->firstContact; 
}

tContacto buscarGrupo(TGrupo * group, char * groupName, tContact contact, int * flag) { 
  int c; 
  if (group == NULL || (c=strcasecmp(group->name, groupName)) > 0 ) {
    return NULL; // no existe el grupo por lo tanto no se agrega
    * flag = 0; 
  }
  if (c < 0) 
    group->nextGrupo = buscarGrupo(group->nextGrupo, groupName, contact); 
  // si existe el grupo entonces veo si existe el contacto 
  group->primerContacto = addContactRec(TGrupo * group, tContact contact, &flag); 
  return group->primerContacto; 
}
/* Si existe un grupo de nombre groupName, agrega el contacto contact a la agenda
** Si el grupo no existe, no hace nada
** Si ya había un contacto con el mismo nombre en ese grupo, no lo agrega */
int addContact(addressBookADT a, const char * groupName, tContact contact) {
  int flag = 0; 
  a->primerContacto = buscarGrupo(a->primerGrupo, groupName, contact, &flag); 
  return flag; 
}

// -----------------------------------------------------------------------------------------

addressBookCDT * buscarGrupo(addressBookCDT * grupo, const char * groupName) { 
  int c; 
  if (grupo == NULL || (c = strcasecmp(grupo->name, groupName)) > 0) 
    return NULL; 
  if (c == 0) 
    return grupo; 
  return buscarGrupo(group->nextGrupo, groupName)); 
}

/*
** Permite iterar por todos los contactos de la agenda
** QUE PERTENEZCAN AL GRUPO INDICADO por parámetro en toBegin
** El orden es alfabético por nombre del contacto.*/
void toBeginForGroup(addressBookADT a, const char * groupName) {
  addressBookCDT * aux = buscarGrupo(a->currentGrupo, groupName); 
  if (aux != NULL) { 
    a->currentContact = aux->primerContacto; 
  } else { 
    a->currentContact = NULL; 
  }
}
int hasNextForGroup(addressBookADT a) {
  return a->currentCurrent != NULL; 
}

/* Retorna un contacto, aborta si no hay siguiente */
tContact nextForGroup(addressBookADT a) { 
  if (!hasNextForGroup(a)) 
    exit (1); 
  tContact aux = a->currentContact; 
  a->currentContact = a->currentContact->nextPerson; 
  return aux; 
}
/*
** Permite iterar por todos los grupos de la agenda
** El orden es alfabético por nombre del grupo.*/
void toBegin(addressBookADT a) { 
  a->currentGroup = a -> firstGroup; 
}

int hasNext(addressBookADT a) { 
  return a->currentGroup != NULL; 
}

char * next(addressBookADT a) { 
  if (!hasNext(a)) 
    exit (1); 
  
  char * aux = malloc((strlen(a->currentGroup->name)+1)*sizeof(char)); 
  strcpy(aux, a->currentGroup->name); 
  a->currentGroup = a->currentGroup->nextGroup; 
  return aux; 
}
}
