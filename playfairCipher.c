// 1) construye una matriz de 5x5 letras del alfabeto 
// en base a una palabra clave formada por letras sin repeticiones se llena la matriz comenzando por la esquina superior izquierda (posicion [0][0]) con las letras de la palabra clave 
// una vez que se completó la primer fila se continúa por la primer columna de la segunda fila y así hasta el final 
// una vez que se colocaron las letras de la palabra clave se completa el resto de la matriz con als letras del alfabeto inglés (excepto la 'j') que NO figuran en la palabra clave 

// escribir una función PLAYFAIR que reciba como único parámetro la palabra y devuelva una matriz de acuerdo a la definición previa 

// en caso de que la palabra clave fuera inválida (es vacía o no contiene solo minúsculas SIN repetir o contiene la 'j') la función playfair debe retornar NULL 

#include <stdio.h>
#include <stdlib.h>

#define N 5
#define CANTLETRAS ('z'-'a'+1)
#define GET_INDEX(letra) ((letra)-'a')
#define isLower(letra) ('a'<=(letra) && (letra) <= 'z')

void freeMat(char ** m, int dim) {
    for (int i = 0; i < dim; i++) {
        free(m[i]);
    }
    free(m);
}

char ** playfair(char * clave) {
    // inicio un vector en 0 para registrar si hay repeticiones
    char vec[CANTLETRAS] = {0};

    char ** m = calloc(N, sizeof(char**));
    int i, c;
    for (i = 0; clave[i] != '\0'; i++) {
        c = clave[i]; // copio la letra
        if (!isLower(c) || c == 'j' || vec[GET_INDEX(c)] == 1) {
            freeMat(m, N);
            return NULL;
        }
        if (i % N == 0) { // si no hay más espacio
            m[i/N] = malloc(N*sizeof(char));
        }
        vec[GET_INDEX(c)] += 1; // seteo a 1 todos los usados
        m[i/N][i%N] = c;
    }
    c = 'a';
    for (int k = i/N; k<N; k++) {
        for (int j = i%N; j <N; j++) {
            while (vec[GET_INDEX(c)] != 1 && c<='z') {
                c++;
            }
            m[k][j] = c;
        }
    }
    return m;
}

int main () {
    char ** m ;

    m = playfair("prueba");
    for (int i = 0; i <N; i++) {
        for (int j = 0; j < N; j++)
            putchar(m[i][j]);
        putchar('\n');
    }

    freeMat(m, N);
    return 0;
}
