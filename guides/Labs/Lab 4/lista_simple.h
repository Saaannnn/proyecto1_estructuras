#include <iostream>
#include "conjunto_ref.h"
struct seccion{ 
    char profesor;    // informacion del nodo  
    Conjunto estudiantes;
};
struct Nodo {

    seccion datos;
    int hora=0;  // contendra la hora asignada (de 1 a 10)
    Nodo *proximo;  // enlace a otro
                              //  nodo
};
typedef Nodo* Lista_simple;
Lista_simple crear_vacia();
void vaciar_lista(Lista_simple &lista);
void eliminar_primero(Lista_simple  &lista);
void eliminar_primero(Lista_simple  *lista);
void insertar(Lista_simple &lista, seccion datos);
void insertar_cola(Lista_simple &lista, seccion datos);
void insertar_cola(Lista_simple &lista, Nodo* nodo);
void imprimir(const Lista_simple  & lista);
            // no permite const Nodo * & lista
           // pues lo asignamos al pointer "cursor" y 
           // esto seria ilegal  pues podriamos modificar
           // los valores a los que apunta la constante
           // en cambio permite Nodo * const & lista

void invertir(Lista_simple &lista);
void invertir_iter(Lista_simple &lista);

int num_elem(const Lista_simple& lista);

/**
 * hacer_asignacion(Lista_simple& lista):
 * 
 *      Calcula la asignacion de horarios de las secciones de clases dadas por 
 *      "lista". 
 *      "lista" es una lista enlazada donde cada nodo representa una sección
 *      Cada seccion solo posee una sola hora a ser asignada.
 *      Se asignará una hora entre 1 y 10. 
 *      Se recorre la lista desde el primer elemento hasta el último. 
 *      Y se van procesando sus secciones (nodos) una a una.
 *      Al procesar una sección (nodo de la lista) se le asignará la menor hora
 *      de 1 a 10 que no coincida con las horas ya asignadas de las secciones 
 *      previamente procesadas (anteriores en la lista) a ella y que estén en
 *      conflicto con ella (tengan el mismo profesor o 
 *      estudiantes en común). 
 *      Note que si la sección que se está procesando está en conflicto con
 *      secciones a las que ya se les ha asignado todas las horas disponibles
 *      que son del 1 al 10, entonces a esa sección no se le asigna hora.
 *      
 *      parámetros:
 *          lista: la lista de secciones que se les asignará horario.
 */
void hacer_asignacion(Lista_simple& lista);