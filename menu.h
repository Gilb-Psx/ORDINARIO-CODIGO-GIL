#include <stdio.h>

int menuPrincipal(void){
    int op;
    printf("\n---MENU---\n");
    printf("[1].Dar de alta\n");
    printf("[2].Dar de baja\n");
    printf("[3].Mostrar datos\n");
    printf("[4].Funciones Especiales\n");
    printf("[5].Salir\n");
    printf("Elija una operacion a realizar: \n");
    scanf("%d",&op);
    return op;
}

int menuAltas(void){
    int opc;
    printf("\n---MENU ALTAS---\n");
    printf("[1].Dar de alta a una persona\n");
    printf("[2].Dar de alta a varias personas\n");
    printf("[3].Regresar al menú\n");
    printf("Elije una operacion a realizar: \n");
    scanf("%d",&opc);
    return opc;
}

int menuBajas(void){
    int op;
    printf("\n---MENU BAJAS---\n");
    printf("[1].Dar de baja a una persona\n");
    printf("[2].Dar de baja a varias personas\n");
    printf("[3].Dar de baja a todos\n");
    printf("[4].Regresar\n");
    printf("Elije una operacion a realizar: \n");
    scanf("%d",&op);
    return op;
}
int menuMostrar(void){
    int op;
    printf("\n---MENU MOSTRAR---\n");
    printf("[1].Todas las personas\n");
    printf("[2].Por carrera\n");
    printf("[3].Por semestre\n");
    printf("[4].Por Carrera y semestre\n");
    printf("[5].Regresar\n");
    printf("Elije una operacion a realizar: \n");
    scanf("%d",&op);
    return op;
}
