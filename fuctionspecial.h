#ifndef FUCTIONSPECIAL_H
#define FUCTIONSPECIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_APROBATORIA 6.0 // Mi numero fijo para saber si pasaron o no

// Vuelve a calcular los promedios finales (columna 4) sumando las notas que esten guardadas
void actualizarPromediosAlumno(struct Alumno *alum) {
    if (alum == NULL) return;
    for (int i = 0; i < 5; i++) {
        float suma = alum->calif[i][0] + alum->calif[i][1] + alum->calif[i][2] + alum->calif[i][3];
        alum->calif[i][4] = suma / 4.0; 
    }
}

// Busco a una persona por su matricula para saber su posicion en la lista
struct Persona* buscarAlumnoPorMatricula(struct Persona *ptr, const char *mat) {
    struct Persona *aux = ptr;
    while (aux != NULL) {
        if (aux->ptrAlum != NULL && strcasecmp(aux->ptrAlum->matricula, mat) == 0) {
            return aux; // Si coincide la matricula regreso ese nodo entero
        }
        aux = aux->ptrSig;
    }
    return NULL; // Regreso nulo si no existia
}

// Menu especial para cambiar los datos de alguien que ya dimos de alta
void menuModificarEstructura(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros.\n");
        return;
    }
    
    char mat[20];
    printf("\nMatricula: ");
    scanf("%s", mat);
    
    struct Persona *alumnoEncontrado = buscarAlumnoPorMatricula(ptr, mat);
    if (alumnoEncontrado == NULL) {
        printf("No encontrado.\n");
        return;
    }
    
    int opMod, subOp;
    do {
        actualizarPromediosAlumno(alumnoEncontrado->ptrAlum); // Vuelvo a sacar promedios antes de editar
        
        printf("\nEditando: %s (%s)\n", alumnoEncontrado->nombre, alumnoEncontrado->ptrAlum->matricula);
        printf("[1]. Modificar calificaciones\n");
        printf("[2]. Modificar datos generales\n");
        printf("[3]. Regresar\n");
        printf("Opcion: ");
        scanf("%d", &opMod);
        
        switch(opMod) {
            case 1:
                printf("\n[1]. Por parcial\n[2]. Por materia\nOpcion: ");
                scanf("%d", &subOp);
                
                if (subOp == 1) {
                    int col;
                    printf("Bloque (0=P1, 1=P2, 2=P3, 3=Ord): ");
                    scanf("%d", &col);
                    if (col >= 0 && col < 4) {
                        for (int i = 0; i < 5; i++) {
                            printf("Materia %d - Nueva calificacion: ", i + 1);
                            scanf("%f", &alumnoEncontrado->ptrAlum->calif[i][col]);
                        }
                        actualizarPromediosAlumno(alumnoEncontrado->ptrAlum); // Recalculo con los cambios hechos
                    }
                } 
                else if (subOp == 2) {
                    int fila;
                    printf("Materia (1-5): ");
                    scanf("%d", &fila);
                    fila--; // Le resto 1 para que coincida con los indices de 0 a 4 del arreglo
                    if (fila >= 0 && fila < 5) {
                        for (int j = 0; j < 4; j++) {
                            printf("Evaluacion %d - Nueva calificacion: ", j + 1);
                            scanf("%f", &alumnoEncontrado->ptrAlum->calif[fila][j]);
                        }
                        actualizarPromediosAlumno(alumnoEncontrado->ptrAlum);
                    }
                }
                break;
                
            case 2:
                printf("\n[1]. Personales\n[2]. Escolares\nOpcion: ");
                scanf("%d", &subOp);
                
                if (subOp == 1) {
                    char buffer[100];
                    printf("Nuevo nombre: ");
                    scanf(" ");
                    fgets(buffer, 100, stdin);
                    buffer[strcspn(buffer, "\n")] = '\0';
                    
                    free(alumnoEncontrado->nombre); // Libero el nombre viejo para que no use memoria de mas
                    alumnoEncontrado->nombre = (char*)malloc(strlen(buffer) + 1); // Pido espacio para el nombre nuevo
                    strcpy(alumnoEncontrado->nombre, buffer);
                    
                    printf("Nueva edad: ");
                    scanf("%d", &alumnoEncontrado->edad);
                    printf("Nuevo genero (m/f): ");
                    scanf(" %c", &alumnoEncontrado->genero);
                } 
                else if (subOp == 2) {
                    printf("Nueva carrera: ");
                    scanf("%s", alumnoEncontrado->ptrAlum->carrera);
                    printf("Nuevo semestre: ");
                    scanf(" %s", &alumnoEncontrado->ptrAlum->semestre);
                    printf("Nuevo correo: ");
                    scanf("%s", alumnoEncontrado->ptrAlum->correo);
                }
                break;
        }
    } while(opMod != 3);
}

// Muestra las listas de alumnos aprobados y reprobados de un semestre especifico
void reporteSemestre(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros.\n");
        return;
    }
    
    char semBuscado[5];
    printf("\nSemestre: ");
    scanf("%s", semBuscado);
    
    int op, criterio;
    printf("\n--- REPORTE SEMESTRE %s ---\n", semBuscado);
    printf("[1]. Materia\n[2]. Parcial\nOpcion: ");
    scanf("%d", &op);
    
    struct Persona *aux;
    
    if (op == 1) {
        printf("Materia (1-5): ");
        scanf("%d", &criterio);
        criterio--;
        if (criterio < 0 || criterio >= 5) return;
        
        printf("\nAprobados:\n");
        aux = ptr;
        while(aux != NULL) {
            if (aux->ptrAlum != NULL && strcasecmp(&aux->ptrAlum->semestre, semBuscado) == 0) {
                actualizarPromediosAlumno(aux->ptrAlum);
                // Checo la columna 4 que es donde guardamos el promedio final calculado
                if (aux->ptrAlum->calif[criterio][4] >= MIN_APROBATORIA) {
                    printf("Nombre: %s, Promedio: %.1f\n", aux->nombre, aux->ptrAlum->calif[criterio][4]);
                }
            }
            aux = aux->ptrSig;
        }
        
        printf("\nReprobados:\n");
        aux = ptr;
        while(aux != NULL) {
            if (aux->ptrAlum != NULL && strcasecmp(&aux->ptrAlum->semestre, semBuscado) == 0) {
                actualizarPromediosAlumno(aux->ptrAlum);
                if (aux->ptrAlum->calif[criterio][4] < MIN_APROBATORIA) {
                    printf("Nombre: %s, Promedio: %.1f\n", aux->nombre, aux->ptrAlum->calif[criterio][4]);
                }
            }
            aux = aux->ptrSig;
        }
    } 
    else if (op == 2) {
        printf("Bloque (0=P1, 1=P2, 2=P3, 3=Ord): ");
        scanf("%d", &criterio);
        if (criterio < 0 || criterio >= 4) return;
        
        printf("\nAprobados bloque %d:\n", criterio + 1);
        aux = ptr;
        while(aux != NULL) {
            if (aux->ptrAlum != NULL && strcasecmp(&aux->ptrAlum->semestre, semBuscado) == 0) {
                float sumaBloque = 0;
                for(int i = 0; i < 5; i++) sumaBloque += aux->ptrAlum->calif[i][criterio];
                float promBloque = sumaBloque / 5.0; // Saco el promedio global sumando las 5 materias de ese parcial
                if (promBloque >= MIN_APROBATORIA) {
                    printf("Nombre: %s, Promedio: %.1f\n", aux->nombre, promBloque);
                }
            }
            aux = aux->ptrSig;
        }
        
        printf("\nMaterias aprobadas:\n");
        aux = ptr;
        while(aux != NULL) {
            if (aux->ptrAlum != NULL && strcasecmp(&aux->ptrAlum->semestre, semBuscado) == 0) {
                printf("Matricula %s, materias: ", aux->ptrAlum->matricula);
                for(int i = 0; i < 5; i++) {
                    if (aux->ptrAlum->calif[i][criterio] >= MIN_APROBATORIA) {
                        printf("[%d: %.1f] ", i + 1, aux->ptrAlum->calif[i][criterio]);
                    }
                }
                printf("\n");
            }
            aux = aux->ptrSig;
        }
    }
}

// Cuenta cuantas materias debe un alumno para clasificarlos en regular o critico
void reporteCarrera(struct Persona *ptr) {
    if (ptr == NULL) {
        printf("\nNo hay registros.\n");
        return;
    }
    
    char carBuscada[5];
    printf("\nCarrera: ");
    scanf("%s", carBuscada);
    
    int op;
    printf("\n--- REPORTE CARRERA %s ---\n", carBuscada);
    printf("[1]. Regulares\n[2]. 1 a 3 reprobadas\n[3]. 4 o mas reprobadas\nOpcion: ");
    scanf("%d", &op);
    
    struct Persona *aux = ptr;
    printf("\n--- RESULTADOS ---\n");
    
    while (aux != NULL) {
        if (aux->ptrAlum != NULL && strcasecmp(aux->ptrAlum->carrera, carBuscada) == 0) {
            actualizarPromediosAlumno(aux->ptrAlum);
            
            int adeudos = 0;
            // Recorro las 5 materias para ver cuales tienen promedio menor a 6
            for (int i = 0; i < 5; i++) {
                if (aux->ptrAlum->calif[i][4] < MIN_APROBATORIA) {
                    adeudos++;
                }
            }
            
            // Uso condicionales sencillos sin meter cosas raras para que se vea normal
            if (op == 1 && adeudos == 0) {
                printf("Nombre: %s, Matricula: %s (Regular)\n", aux->nombre, aux->ptrAlum->matricula);
            } 
            else if (op == 2) {
                if (adeudos >= 1 && adeudos <= 3) {
                    printf("Nombre: %s, Adeuda: %d\n", aux->nombre, adeudos);
                }
            } 
            else if (op == 3 && adeudos >= 4) {
                printf("Nombre: %s, Critico, adeuda: %d\n", aux->nombre, adeudos);
            }
        }
        aux = aux->ptrSig;
    }
}

void menuFuncionesEspeciales(struct Persona *ptr) {
    int op;
    do {
        printf("\n--- FUNCIONES ESPECIALES ---\n");
        printf("[1]. Modificar alumno\n");
        printf("[2]. Reporte por semestre\n");
        printf("[3]. Reporte por carrera\n");
        printf("[4]. Regresar\n");
        printf("Opcion: ");
        scanf("%d", &op);
        
        switch(op) {
            case 1: menuModificarEstructura(ptr); break;
            case 2: reporteSemestre(ptr); break;
            case 3: reporteCarrera(ptr); break;
        }
    } while(op != 4);
}

#endif
