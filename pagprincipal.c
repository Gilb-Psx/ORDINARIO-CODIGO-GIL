#ifndef STRUCTS_H
#define STRUCTS_H

// Mis estructuras fijas para el programa
struct Persona{
    char *nombre;
    int edad;
    char genero;
    char fn[8];
    struct Alumno *ptrAlum;
    struct Persona *ptrSig; // El enlace al siguiente de la lista
};

struct Alumno{
    char matricula[10];
    char carrera[5];
    char semestre;
    char correo[23];
    float calif [5][5]; // Matriz: 5 materias y 5 columnas (P1, P2, P3, Ord y Promedio)
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
    struct Persona *ptr = NULL; // Mi puntero inicializador de la lista (empieza vacio)

    do {
        op = menuPrincipal(); // Capturo la eleccion del menu grande
        switch (op) {
            case 1: 
                do {
                    op2 = menuAltas();
                    switch (op2) {
                        case 1: Altas(&ptr); break; // Alta individual
                        case 2: AltasVarias(&ptr); break; // Alta continua e interactiva
                        case 3: printf("\nRegresando... \n"); break;
                        default: printf("opcion invalida");
                    }
                } while(op2 != 3); // Ciclo del submenu de altas
                break;

            case 2: 
                do {
                    op3 = menuBajas();
                    switch (op3) {
                        case 1: bajas(&ptr); break; // Borra el primero de la lista
                        case 2: Bajasamas(&ptr); break; // Borra interactivo hasta que el usuario diga no
                        case 3: BajasTodos(&ptr); break; // Limpia toda la memoria de golpe
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
                menuFuncionesEspeciales(ptr); // Abre el modulo de reportes y modificaciones
                break;

            case 5: 
                printf("\nLiberando memoria...\n");
                BajasTodos(&ptr); // Por seguridad limpio la memoria antes de cerrar el exe
                printf("Fin del programa.\n");
                break;

            default:
                printf("opcion invalida");
                break;
        }
    } while(op != 5); // El programa corre hasta que elijan la opcion 5
    
    return 0;
}
