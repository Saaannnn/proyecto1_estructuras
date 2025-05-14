#include "cola.h"
Cola crearVacia(){
    return crear_lista_vacia();
}
int frente(const Cola& cola){
    // el frente es el primero de la list vaciaa
    // se supone que la cola no esta vacia
    return cola.cabeza->proximo->data;
}
void desencolar(Cola& cola){
    // elimina el frente de la cola
    // se supone que la cola no esta vacia
    eliminar(cola, 0);
}
void encolar(Cola& cola, int elem){
    // // lo inserta de ultimo en la lista
    // insertar(cola, elem, cola.num_elem);
   Nodo* p = cola.cola;
   Nodo* nuevo_nodo = new Nodo{ elem, p->anterior, p }; 
   (nuevo_nodo->anterior)  ->  proximo = nuevo_nodo; 
   p->anterior = nuevo_nodo;  
   cola.num_elem ++;
}
int num_elem(const Cola& cola){
    return cola.num_elem;
}
void imprimir_cola(const Cola& cola){
    imprimir(cola);
}
