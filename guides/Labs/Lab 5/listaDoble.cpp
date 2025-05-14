#include <iostream>
#include "listaDoble.h"

Lista_dob_enl crear_lista_vacia(){
  Lista_dob_enl p;
  p.cabeza = new Nodo{0,nullptr, nullptr};
  p.cola = new Nodo{0,p.cabeza, nullptr};
  (p.cabeza)->proximo = p.cola;
  p.num_elem =0;
  return p;
}
bool esVacia(const Lista_dob_enl &lista){
  return (lista.num_elem == 0);
}
Nodo* Obtener_Ref(Lista_dob_enl &lista, int pos){
  // pos debe estar entre 0 y numero de elementos de la lista
  Nodo* cursor = (lista.cabeza)->proximo;
  int posicion=0;
  while (posicion != pos){
    cursor = cursor->proximo;
    posicion++;   
  }
  return cursor;
}
void insertar(Lista_dob_enl &lista, int x, int pos){
  // Inserta x en la posición pos de lista
  if (pos <0 || pos > lista.num_elem) return;
  Nodo* cursor = Obtener_Ref(lista,pos);
  Nodo* nuevo = new Nodo{x,cursor->anterior,cursor};
  (cursor->anterior)->proximo = nuevo;
  cursor->anterior = nuevo;
  (lista.num_elem)++;
}
void eliminar(Lista_dob_enl &lista, int pos){
  if (pos <0 || pos >= lista.num_elem) return;
  Nodo* cursor = Obtener_Ref(lista,pos);
  (cursor->anterior)->proximo = cursor->proximo;
  (cursor->proximo)->anterior  = cursor->anterior;
  (lista.num_elem)--;
}
void imprimir(const Lista_dob_enl &lista){
  // imprime lista
  Nodo* p = lista.cabeza->proximo;
  while (p != lista.cola){
     std::cout << p->data << " ";
     p = p->proximo;
  }
  std::cout << std::endl;
}
