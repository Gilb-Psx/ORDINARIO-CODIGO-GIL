#ifndef STRUCTS_H
#define STRUCTS_H

// Mis estructuras para guardar los datos
struct Persona{
    char *nombre;
    int edad;
    char genero;
    char fn[8];
    struct Alumno *ptrAlum;
    struct Persona *ptrSig; // Puntero para conectar con el siguiente nodo
};

struct Alumno{
    char matricula[10];
    char carrera[5];
    char semestre;
    char correo[23];
    float calif [5][5]; // Matriz de 5 materias y 5 columnas para las notas
};
#endif

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "altas.h"
#include "bajas.h"
#include "mostrar.h"
#include "fuctionspecial.h"

int main(){
    int op, op2, op3, opMostrar;
    struct Persona *ptr = NULL; // El inicio de mi lista empieza vacio

    do {
        op = menuPrincipal(); // Guardo la opcion del menu principal
        switch (op) {
            case 1: 
                do {
                    op2 = menuAltas();
                    switch (op2) {
                        case 1: Altas(&ptr); break; // Alta de uno solo
                        case 2: AltasVarias(&ptr); break; // Alta de varios seguidos
                        case 3: printf("\nRegresando... \n"); break;
                        default: printf("opcion invalida");
                    }
                } while(op2 != 3); // Cierra el submenu de altas
                break;

            case 2: 
                do {
                    op3 = menuBajas();
                    switch (op3) {
                        case 1: bajas(&ptr); break; // Quita el primero de la lista
                        case 2: Bajasamas(&ptr); break; // Quita varios preguntando
                        case 3: BajasTodos(&ptr); break; // Borra toda la lista completa
                        case 4: printf("Regreso\n"); break;
                        default: printf("opcion invalida");
                    }
                } while(op3 != 4);
                break;

            case 3: 
                do {
                    opMostrar = menuMostrar();
                    switch(opMostrar) {
                        case 1: MostrarTodas(ptr); break;
                        case 2: MostrarPorCarrera(ptr); break;
                        case 3: MostrarPorSemestre(ptr); break;
                        case 4: MostrarCarreraYSemestre(ptr); break;
                        case 5: BuscarPorNombre(ptr); break;
                        case 6: BuscarPorMatricula(ptr); break;
                        case 7: printf("Regresando... \n"); break;
                        default: printf("opcion invalida");
                    }
                } while(opMostrar != 7);
                break;

            case 4: 
                menuFuncionesEspeciales(ptr); // Abre el menu de reportes y cambios
                break;

            case 5: 
                printf("\nLiberando memoria...\n");
                BajasTodos(&ptr); // Limpio todo antes de cerrar para que no se quede trabado
                printf("Fin del programa.\n");
                break;

            default:
                printf("opcion invalida");
                break;
        }
    } while(op != 5); // Corre hasta que le den salir
    
    return 0;
}
