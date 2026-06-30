#include <stdio.h>
#include <stdlib.h>

void bajas(struct Persona **ptr){
    struct Persona *ptraux;
    if(*ptr==NULL){
        printf("No existe registro\n");
        return;
    }else{
        ptraux=*ptr;
        *ptr = ptraux->ptrSig;
        if(ptraux->ptrAlum!=NULL){
            free(ptraux->ptrAlum);
        }
        free(ptraux->nombre);
        free(ptraux);
        printf("Baja realizada con exito.\n");
    }
}

void Bajasamas(struct Persona **ptr){
    int n;
    if (*ptr == NULL) {
        printf("No existen registros\n");
        return;
    }
    printf("¿a cuantos alumnos se les aplicara la baja?: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        if (*ptr == NULL) {
            printf("\nlista vacia, no se elaboro.\n");
            break;
        }
        bajas(ptr);
    }
}
void BajasTodos(struct Persona **ptr) {
    if (*ptr == NULL) {
        printf("No existe algun registro.\n");
        return;
    }

    printf("\n Eliminando registros\n");

    
    while (*ptr != NULL) {
        struct Persona *ptraux = *ptr;
        *ptr = ptraux->ptrSig;
        if (ptraux->ptrAlum != NULL) {
            free(ptraux->ptrAlum);
        }
        free(ptraux->nombre);
        free(ptraux);
    }
    printf("registros exitosos\n");
}