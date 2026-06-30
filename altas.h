#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persona *nuevaPersona(){
    struct Persona *p =(struct Persona*)malloc(sizeof(struct Persona));
    if(p==NULL)
        printf("no se reservo memoria");

    else{
        char nombre[50];
        p->nombre=(char*)malloc(sizeof(nombre));
        printf("Nombre: \n");
        scanf(" ");
        fgets(nombre, 50, stdin);

        printf("Edad: \n");
        scanf("%d",&p->edad);

        printf("Genero(m/f): \n");
        scanf(" %s",&p->genero);

        printf("Fecha de nacimiento: \n");
        scanf("%s",p->fn);
        p->ptrSig=NULL;
    }
    return p;
}

struct Alumno *nuevoAlumno(){
    struct Alumno *A = (struct Alumno *)malloc(sizeof(struct Alumno));
    if(A == NULL) {
        printf("No se reservo memoria para Alumno\n");
        return NULL;
    }
    else {
        printf("Matricula: \n");
        scanf("%s", A->matricula);

        printf("Carrera: \n");
        scanf("%s", A->carrera);

        printf("Semestre: \n");
        scanf(" %s", &A->semestre);

        printf("Correo: \n");
        scanf("%s", A->correo);


        printf("\nCalificaciones \n");
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 4; j++) {
                A->calif[i][j] = rand()%11;// de 3 parciles, el promedio de los 3 parciales, y el ordinario

                if(j < 3) {
                    printf("Materia %d - Parcial %d: %.1f\n", i + 1, j + 1, A->calif[i][j]);
                } else {
                    printf("Materia %d - Ordinario: %.1f\n", i + 1, A->calif[i][j]);
                }
            }
        }
    }
    return A;
}
int Altas(struct Persona **ptr){
    struct Persona *P = NULL;
    struct Alumno *A = NULL;
    int esAlumno;
    int b=1;

    P = nuevaPersona();
    if(P == NULL){
        return 0;
    }

    printf("\n¿Es Alumno? (1 si es Alumno y 0 si no es Alumno): ");
    scanf("%d", &esAlumno);

    if (esAlumno == 1) {
        A = nuevoAlumno();
        if(A == NULL){
            b = 0;
            free(P);
            return b;
        }
        P->ptrAlum = A;
    } else {
        P->ptrAlum = NULL;
    }
    P->ptrSig = *ptr;
    *ptr = P;

    return b;
}
void AltasVarias(struct Persona **ptr){
    int n;
    printf("Cuantas peronas desea dar de alta ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
         Altas(ptr);
    }

}
