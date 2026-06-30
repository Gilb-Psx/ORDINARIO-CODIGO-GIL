#include <stdio.h>
#include <stdlib.h>

// Borra siempre el primer elemento que este en la lista
void bajas(struct Persona **ptr){
    struct Persona *ptraux;
    if(*ptr==NULL){
        printf("No existe registro\n");
        return;
    }else{
        ptraux=*ptr; // Guardo el de adelante en un auxiliar
        *ptr = ptraux->ptrSig; // Muevo el inicio real de la lista al siguiente nodo
        
        if(ptraux->ptrAlum!=NULL){
            free(ptraux->ptrAlum); // Si era estudiante le borro sus datos de escuela primero
        }
        free(ptraux->nombre); // Borro el espacio del texto del nombre
        free(ptraux); // Borro por completo de la memoria el nodo de la persona
        printf("Baja realizada con exito.\n");
    }
}

// Borra elementos uno por uno preguntandole al usuario en cada paso si quiere seguir
void Bajasamas(struct Persona **ptr){
    if (*ptr == NULL) {
        printf("No existen registros\n");
        return;
    }

    int resp;
    do {
        bajas(ptr); // Borro el nodo que este al principio

        // Si la lista ya se quedo vacia, salgo del ciclo para que no marque error
        if (*ptr == NULL) {
            printf("\nlista vacia, proceso terminado.\n");
            break;
        }

        printf("¿Dar de baja a otra persona? (1=si, 0=no): ");
        scanf("%d", &resp);

    } while(resp == 1);
    printf("Proceso de bajas terminado.\n");
}

// Ciclo while para recorrer toda la lista y borrar absolutamente todo de golpe
void BajasTodos(struct Persona **ptr) {
    if (*ptr == NULL) {
        return;
    }
    printf("\nEliminando registros\n");
    while (*ptr != NULL) {
        struct Persona *ptraux = *ptr;
        *ptr = ptraux->ptrSig;
        if (ptraux->ptrAlum != NULL) {
            free(ptraux->ptrAlum);
        }
        free(ptraux->nombre);
        free(ptraux);
    }
    printf("Todos eliminados.\n");
}
