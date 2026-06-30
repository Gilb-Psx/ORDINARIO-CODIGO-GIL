#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimirNodo(struct Persona *aux) {
    printf("\nNombre: %s", aux->nombre);
    printf("\nEdad: %d", aux->edad);
    printf("\nGenero: %s", aux->genero);
    printf("\nFecha de Nacimiento: %s", aux->fn);

    if (aux->ptrAlum != NULL) {
        printf("\n  [Alumno] Matricula: %s", aux->ptrAlum->matricula);
        printf(" | Carrera: %s", aux->ptrAlum->carrera);
        printf(" | Semestre: %s", aux->ptrAlum->semestre);
        printf(" | Correo: %s", aux->ptrAlum->correo);
    } else {
        printf("\n  [Particular] No es estudiante.");
    }
    printf("\n--------------------------------------------------");
}

// 1. TODAS: Muestra absolutamente todos los registros
void MostrarTodas(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros en la estructura.\n");
        return;
    }
    struct Persona *aux = ptr;
    printf("\n--- TODOS LOS REGISTROS ---\n");
    while (aux != NULL) {
        imprimirNodo(aux);
        aux = aux->ptrSig;
    }
}

// 2. CARRERA: Filtra y muestra solo los alumnos de una carrera específica
void MostrarPorCarrera(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros en la estructura.\n");
        return;
    }
    char busqueda[50];
    int encontrados = 0;
    printf("Ingrese la carrera a buscar: ");
    scanf(" ");
    fgets(busqueda, 50, stdin);
    busqueda[strcspn(busqueda, "\n")] = '\0';

    struct Persona *aux = ptr;
    printf("\n--- ALUMNOS EN LA CARRERA: %s ---\n", busqueda);
    while (aux != NULL) {
        // Validamos que sea alumno y que la carrera coincida
        if (aux->ptrAlum != NULL && strcasecmp(aux->ptrAlum->carrera, busqueda) == 0) {
            imprimirNodo(aux);
            encontrados++;
        }
        aux = aux->ptrSig;
    }
    if (encontrados == 0) printf("No se encontraron alumnos en esa carrera.\n");
}

// 3. SEMESTRE: Filtra y muestra solo los alumnos de un semestre específico
void MostrarPorSemestre(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros en la estructura.\n");
        return;
    }
    char busqueda[20];
    int encontrados = 0;
    printf("Ingrese el semestre a buscar: ");
    scanf("%s", busqueda);

    struct Persona *aux = ptr;
    printf("\n--- ALUMNOS DEL SEMESTRE: %s ---\n", busqueda);
    while (aux != NULL) {
        if (aux->ptrAlum != NULL && strcasecmp(aux->ptrAlum->semestre, busqueda) == 0) {
            imprimirNodo(aux);
            encontrados++;
        }
        aux = aux->ptrSig;
    }
    if (encontrados == 0) printf("No se encontraron alumnos en ese semestre.\n");
}

// 4. CARRERA Y SEMESTRE: Filtro doble
void MostrarCarreraYSemestre(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros en la estructura.\n");
        return;
    }
    char car[50], sem[20];
    int encontrados = 0;
    
    printf("Ingrese la carrera: ");
    scanf(" ");
    fgets(car, 50, stdin);
    car[strcspn(car, "\n")] = '\0';
    
    printf("Ingrese el semestre: ");
    scanf("%s", sem);

    struct Persona *aux = ptr;
    printf("\n--- ALUMNOS DE %s - SEMESTRE %s ---\n", car, sem);
    while (aux != NULL) {
        if (aux->ptrAlum != NULL && strcasecmp(aux->ptrAlum->carrera, car) == 0 && strcasecmp(aux->ptrAlum->semestre, sem) == 0) {
            imprimirNodo(aux);
            encontrados++;
        }
        aux = aux->ptrSig;
    }
    if (encontrados == 0) printf("No se encontraron alumnos con ambos criterios.\n");
}

// 5. NOMBRE: Busca una persona por coincidencia de nombre
void BuscarPorNombre(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros en la estructura.\n");
        return;
    }
    char busqueda[50];
    int encontrados = 0;
    printf("Ingrese el nombre exacto a buscar: ");
    scanf(" ");
    fgets(busqueda, 50, stdin);
    busqueda[strcspn(busqueda, "\n")] = '\0';

    struct Persona *aux = ptr;
    printf("\n--- RESULTADOS PARA EL NOMBRE: %s ---\n", busqueda);
    while (aux != NULL) {
        if (strcasecmp(aux->nombre, busqueda) == 0) {
            imprimirNodo(aux);
            encontrados++;
        }
        aux = aux->ptrSig;
    }
    if (encontrados == 0) printf("No se encontro ninguna persona con ese nombre.\n");
}

// 6. MATRICULA: Busca a un alumno por su identificador único
void BuscarPorMatricula(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros en la estructura.\n");
        return;
    }
    char busqueda[20];
    int encontrados = 0;
    printf("Ingrese la matricula a buscar: ");
    scanf("%s", busqueda);

    struct Persona *aux = ptr;
    printf("\n--- RESULTADOS PARA LA MATRICULA: %s ---\n", busqueda);
    while (aux != NULL) {
        if (aux->ptrAlum != NULL && strcasecmp(aux->ptrAlum->matricula, busqueda) == 0) {
            imprimirNodo(aux);
            encontrados = 1;
            break; // Como la matrícula es única, podemos terminar al hallarlo
        }
        aux = aux->ptrSig;
    }
    if (encontrados == 0) printf("No se encontro ningun alumno con esa matricula.\n");
}