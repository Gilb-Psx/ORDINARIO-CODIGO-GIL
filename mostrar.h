#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcion simple para imprimir los datos de un nodo sin repetir codigo abajo
void imprimirNodo(struct Persona *aux) {
    printf("\nNombre: %s", aux->nombre);
    printf("\nEdad: %d", aux->edad);
    printf("\nGenero: %c", aux->genero);
    printf("\nFecha de Nacimiento: %s", aux->fn);

    // Valido si tiene datos de escuela guardados
    if (aux->ptrAlum != NULL) {
        printf("\nMatricula: %s, Carrera: %s, Semestre: %c, Correo: %s", 
               aux->ptrAlum->matricula, 
               aux->ptrAlum->carrera, 
               aux->ptrAlum->semestre, 
               aux->ptrAlum->correo);
    } else {
        printf("\nNo es estudiante.");
    }
    printf("\n-------------");
}

// Imprime toda la lista usando un puntero auxiliar para avanzar paso a paso
void MostrarTodas(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros.\n");
        return;
    }
    struct Persona *aux = ptr;
    printf("\n--- REGISTROS ---\n");
    while (aux != NULL) {
        imprimirNodo(aux);
        aux = aux->ptrSig; // Paso al siguiente de la lista
    }
}

// Revisa los nodos y los imprime solo si coinciden con la carrera que se busca
void MostrarPorCarrera(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros.\n");
        return;
    }
    char busqueda[50];
    int encontrados = 0;
    printf("Carrera a buscar: ");
    scanf("%s", busqueda);

    struct Persona *aux = ptr;
    printf("\n--- ALUMNOS DE %s ---\n", busqueda);
    while (aux != NULL) {
        if (aux->ptrAlum != NULL && strcasecmp(aux->ptrAlum->carrera, busqueda) == 0) {
            imprimirNodo(aux);
            encontrados++;
        }
        aux = aux->ptrSig;
    }
    if (encontrados == 0) printf("No se encontraron alumnos.\n");
}

// Revisa los nodos y los imprime solo si coinciden con el semestre buscado
void MostrarPorSemestre(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros.\n");
        return;
    }
    char busqueda[20];
    int encontrados = 0;
    printf("Semestre a buscar: ");
    scanf("%s", busqueda);

    struct Persona *aux = ptr;
    printf("\n--- ALUMNOS SEMESTRE %s ---\n", busqueda);
    while (aux != NULL) {
        if (aux->ptrAlum != NULL && strcasecmp(&aux->ptrAlum->semestre, busqueda) == 0) {
            imprimirNodo(aux);
            encontrados++;
        }
        aux = aux->ptrSig;
    }
    if (encontrados == 0) printf("No se encontraron alumnos.\n");
}

// Filtro doble usando && para que se tengan que cumplir la carrera y el semestre al mismo tiempo
void MostrarCarreraYSemestre(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros.\n");
        return;
    }
    char car[50], sem[20];
    int encontrados = 0;
    
    printf("Carrera: ");
    scanf("%s", car);
    
    printf("Semestre: ");
    scanf("%s", sem);

    struct Persona *aux = ptr;
    printf("\n--- ALUMNOS %s SEMESTRE %s ---\n", car, sem);
    while (aux != NULL) {
        if (aux->ptrAlum != NULL) {
            if (strcasecmp(aux->ptrAlum->carrera, car) == 0 && strcasecmp(&aux->ptrAlum->semestre, sem) == 0) {
                imprimirNodo(aux);
                encontrados++;
            }
        }
        aux = aux->ptrSig;
    }
    if (encontrados == 0) printf("No se encontraron alumnos.\n");
}

void BuscarPorNombre(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros.\n");
        return;
    }
    char busqueda[50];
    int encontrados = 0;
    printf("Nombre exacto: ");
    scanf(" ");
    fgets(busqueda, 50, stdin);
    busqueda[strcspn(busqueda, "\n")] = '\0';

    struct Persona *aux = ptr;
    printf("\n--- BUSQUEDA: %s ---\n", busqueda);
    while (aux != NULL) {
        if (strcasecmp(aux->nombre, busqueda) == 0) {
            imprimirNodo(aux);
            encontrados++;
        }
        aux = aux->ptrSig;
    }
    if (encontrados == 0) printf("No se encontro.\n");
}

// Como la matricula es unica, cuando encuentro una coincidencia pongo break para salirme del ciclo y no gastar tiempo
void BuscarPorMatricula(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros.\n");
        return;
    }
    char busqueda[20];
    int encontrados = 0;
    printf("Matricula: ");
    scanf("%s", busqueda);

    struct Persona *aux = ptr;
    printf("\n--- BUSQUEDA MATRICULA: %s ---\n", busqueda);
    while (aux != NULL) {
        if (aux->ptrAlum != NULL && strcasecmp(aux->ptrAlum->matricula, busqueda) == 0) {
            imprimirNodo(aux);
            encontrados = 1;
            break; // Salgo del ciclo porque ya lo encontre
        }
        aux = aux->ptrSig;
    }
    if (encontrados == 0) printf("No se encontro.\n");
}
