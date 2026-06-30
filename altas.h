#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcion para pedir los datos de una persona nueva con malloc
struct Persona *nuevaPersona(){
    struct Persona *p =(struct Persona*)malloc(sizeof(struct Persona));
    if(p==NULL)
        printf("no se reservo memoria");
    else{
        char nombre[50];
        p->nombre=(char*)malloc(sizeof(nombre)); // Reservo espacio justo para el texto del nombre
        printf("Nombre: \n");
        scanf(" "); // Limpio el buffer para que el fgets no se salte solo
        fgets(nombre, 50, stdin);
        nombre[strcspn(nombre, "\n")] = '\0'; // Le quito el enter que deja el fgets al final

        printf("Edad: \n");
        scanf("%d",&p->edad);

        printf("Genero(m/f): \n");
        scanf(" %c",&p->genero);

        printf("Fecha de nacimiento: \n");
        scanf("%s",p->fn);
        p->ptrSig=NULL; // El nuevo nodo empieza apuntando a la nada
    }
    return p;
}

// Funcion para pedir los datos de escuela y escribir las calificaciones a mano
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

        printf("\nCaptura de Calificaciones \n");
        // Hago dos ciclos for para llenar la matriz a mano
        // i es para cambiar de materia, j es para meter los parciales y el ordinario
        for(int i = 0; i < 5; i++){
            printf("\n--- MATERIA %d ---\n", i + 1);
            for(int j = 0; j < 4; j++) {
                if(j < 3) {
                    printf("Parcial %d: ", j + 1);
                    scanf("%f", &A->calif[i][j]); // Aqui el usuario teclea la calificacion
                } else {
                    printf("Ordinario: ");
                    scanf("%f", &A->calif[i][j]); // Aqui el usuario teclea el ordinario
                }
            }
            // Sumo las primeras 4 notas y divido entre 4. Lo guardo en la ultima columna de esa materia.
            A->calif[i][4] = (A->calif[i][0] + A->calif[i][1] + A->calif[i][2] + A->calif[i][3]) / 4.0;
            printf("Promedio calculado para Materia %d: %.1f\n", i + 1, A->calif[i][4]);
        }
    }
    return A;
}

// Con esta funcion meto el nodo al principio de la lista ligada
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
            free(P); // Si falla el alumno, libero tambien a la persona para no dejar basura
            return b;
        }
        P->ptrAlum = A; // Conecto los datos de alumno dentro de la persona
    } else {
        P->ptrAlum = NULL; // Si es particular se queda en nulo
    }
    
    // Metodo para meter al inicio: el nuevo apunta al que estaba antes al principio, y la lista cambia al nuevo
    P->ptrSig = *ptr;
    *ptr = P;

    printf("Registro guardado.\n");
    return b;
}

// Esta funcion sirve para meter varias personas seguidas usando un ciclo do-while
void AltasVarias(struct Persona **ptr){
    int resp;
    do {
         Altas(ptr); // Uso la funcion de alta de arriba para no repetir codigo
         printf("\n¿Registrar a otra persona? (1=si, 0=no): ");
         scanf("%d", &resp);
    } while(resp == 1); // Si ponen 1 se repite el ciclo, si ponen 0 se sale
    printf("\nProceso terminado.\n");
}
}
