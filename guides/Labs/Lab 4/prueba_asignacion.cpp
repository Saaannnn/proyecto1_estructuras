#include <iostream>
#include "lista_simple.h"
#include "conjunto_ref.h"

int main(){
    Lista_simple lista = crear_vacia();
    insertar(lista, {'m', {1,2}});
    insertar(lista, {'m', {3,4}});
    insertar(lista, {'m', {5}});
    insertar(lista, {'s', {3}});
    insertar(lista, {'q', {3,5}});
    insertar(lista, {'q', {5}});
    imprimir(lista);
    // hacer asignacion
    hacer_asignacion(lista);
    imprimir(lista);

    // tenemos las mismas secciones anteriores pero introducidas en
    // orden diferente. 
    // es este caso se asignan las horas 1 2 3 , mientras que en el caso anterior 
    // se asignan las horas 1 2 3 4
    // por lo que importa el orden para reducir el numero de horas a asignar
    vaciar_lista(lista);
    insertar(lista, {'s', {3}});
    insertar(lista, {'m', {5}});
    insertar(lista, {'q', {5}});
    insertar(lista, {'m', {3,4}});
    insertar(lista, {'q', {3,5}});
    insertar(lista, {'m', {1,2}});
    imprimir(lista);
    // hacer asignacion
    hacer_asignacion(lista);
    imprimir(lista);

    vaciar_lista(lista); 
    insertar(lista, {'m', {1,2}}); // lista con un solo elemento
    imprimir(lista);
    // hacer asignacion
    hacer_asignacion(lista);
    imprimir(lista);

    vaciar_lista(lista); 
//    insertar(lista, {'m', {1,2}}); // lista con un solo elemento
    imprimir(lista);
    // hacer asignacion
    hacer_asignacion(lista); //lista con cero elementos
    imprimir(lista);

}