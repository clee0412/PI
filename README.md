# PI
Ejercicios de Programación Imperativa (cursada 2C 2022) 

rehacer: 
- playfair cipher 
- movetofrontADT
- diccADT
- addressBookADT
- socialADT; 


/** faltó en socialADT 
/* Retorna una copia de los nombres de las personas en orden alfabético.
** Para marcar el final, después del último nombre se coloca NULL
** Si no hay personas, retorna un vector que sólo tiene a NULL como
** elemento
 */
char ** persons(const socialADT soc) {
    char ** ans = malloc((soc->sizeP+1) * sizeof(char *));
    TPerson aux = soc->people;
    int k=0;
    while ( aux != NULL) {
        ans[k++] = copyStr(aux->name);
        aux = aux->next;
    }

    ans[k] = NULL;
    return ans;
}
**/ 

