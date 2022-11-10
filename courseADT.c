typedef struct student { 
	char * nameStudent; 
	struct student * tail; 
} tStudent; 

typedef struct course { 
	char * nameCourse; 
	tStudent * firstStudent; 
	size_t cod; // o sino hago que el codigo de la materia sea
				// la posición dentro del vector 
} tCourse; 


typedef struct courseCDT {
	tCourse * coursesVec; // arreglo dinámico de las materias
	// razones por las cuales elegir un vector: 
		- nunca se agregan más clases (hay un qty definido y no 
		se puede agrandar
		- la operación más común es la búsqueda de la materia 
		para la inserción del alumno en dicha materia 
		por lo tanto es mejor realizar una búsqueda binaria
		a partir de una ordenación alfabética de las materias 
	tStudent * iterStudent; 
	size_t qty; // cantidad de materias 
	size_t iter; // iterador 
}



courseADT newCourseADT(size_t qty) { 
	courseADT new = calloc(1,sizeof(courseCDT)); 
	new->qty = qty; 
	new->coursesVec = calloc(qty, sizeof(tCourse)); 
	for (int i = 0; i < qty; i++) 
		new->coursesVec[i].nameCourse = ""; 
	return new; 
}	


void freeCourseADT(course ADT course) {
	if (course->qty == 0) 
		return; 
	for (int i = 0; i < qty; i++) {	
		freeStudent(course->coursesVec[i].firstStudent); 
		free(course->coursesVec[i]); 
	}
	course->qty = 0; 
}

void freeStudent(tStudent * first) { 
	if (first == NULL) 
		return; 
	freeStudent(first->tail); 
	free(first); 
}

//validar código

#define CODE_MULT 10

//formato del código de una materia 
// el primer número indica la cantidad de alumnos 
// debe ser múltiplo de 100 
static int validarCodigo(size_t code, size_t cantCourses) { 
	if (code % CODE_MULT != 0) // si el código no es múltiplo de 10
		return 0; 
	int aux = code/CODE_MULT; 
	return aux <= cantCourses; 
}

#define TO_POS(X) (((X) / CODE_MULT) -1)

// si el codigo de la materia es válido, cambia el nombre de la misma
// retorna 1 si el codigo de la materia es valido, 0 si no 
int setSubject(courseADT course, size_t subject, char * name) {
	if (!validarCodigo(subject, course->qty)) 
		return 0; 
	course->coursesVec[TO_POS(subject)].nameCourse = name; 
	return 1; 
}


/* Agrega un alumno a una materia especificada por el codigo
 * Si el codigo es invalido o el alumno ya esta en la materia
 * retorna 0 , si no retorna 1
 */
int addStudent(courseADT course , size_t subject , char * student) {
	if (!validarCodigo(subject, course->qty)) 
		return 0; 
	int flag = 0; 
	tStudent * first = course->coursesVec[TO_POS(subject)].firstStudent;
	first = addStudentRec(first, student, &flag); 
	return flag; 
}

static tStudent * addStudentRec(tStudent * first, char * student, int * flag) { 
	int c; 
	if (first == NULL || (c = strcmp(first->nameStudent, student)) > 0) {
		tStudent * aux = malloc(sizeof(tStudent)); 
		aux->nameStudent = student; 
		aux->tail = first; 
		* flag = 1; 
		return aux; 
	}	
	if (c < 0) 
		first->tail = addStudentRec(first->tail, student, flag); 
	return first; 
}



/* Agrega un alumno a todas las materias en las que no estaba
 * ya inscripto
 * retorna la cantidad de materias a las que fue agregado
 */
int addStudentToAll(courseADT course, char * student) { 
	if (course->qty == 0) 
		return 0; 
	int flag; 
	int ans = 0; 
	for (int i = 0; i < course->qty; i++) { 
		flag = 0; 
		course->coursesVec[i].firstStudent = addStudentRec(
			course->coursesVec[i].firstStudent, student, &flag); 
		ans += flag; 
	}
	return ans; 
			
}


/* Permite iterar sobre todas las materias , ubicandose en la primer
 materia */
void toBegin(courseADT course) {
	course->iter = 0; 	
}


//parar copiar: 

#define BLOQUE 10 

static char * copy(const char * source) {
	char * target = NULL; 	
	int dim = 0; 
	for (int i = 0; source[i]!= 0; i++) {
		if (dim % BLOQUE == 0) 
			target = realloc(target, (dim+BLOQUE)); 
		target[dim++] = source[i]; 
	}
	target = realloc(target, dim+1); 
	target[dim] = '\0'; 
	return target; 
} 

/* Retorna una copia del nombre de la siguiente materia
 * Si no hay mas materias para recorrer retorna NULL
 */
char * next(courseADT course) { 
	if (course->iter == course->qty) 
		return NULL; 
	char * new = copy(course->coursesVec[course->iter].nameCourse);
	course->iter++;  
	return new; 
}


/* Se ubica al principio de una materia, en base al codigo de la misma
 * Si el codigo es valido retorna una copia del nombre de la materia
 * Si el codigo es invalido retorna NULL
 * Al pedir los alumnos, lo hace en orden alfabetico
 */
char * toBeginForSubject(courseADT course , size_t subject) { 
	if (!validarCodigo(subject, course->qty))
		return NULL; 
	char * copia = copy(course->coursesVec[TO_POS(subject)].courseName); 
	course->iterStudent = course->coursesVec[TO_POS(subject)].firstStudent;
	return copia; 
}


/* Retorna 1 si hay algun alumno mas por recorrer en la materia*/
int hasNextForSubject(courseADT course) {
	return (course->iterStudent != NULL); 
}

/* Retorna una copia del nombre del siguiente alumno de la materia,
 * por orden alfabetico.
 * Si no hay mas alumnos en la materia aborta la ejecucion
 */
char * nextForSubject(courseADT course) { 
	if (!hasNextForSubject(course)) 
		exit (1);
	char * copia = copy(course->iterStudent.nameStudent); 
	course->iterStudent = course->iterStudent++;
	return copia; 


}
