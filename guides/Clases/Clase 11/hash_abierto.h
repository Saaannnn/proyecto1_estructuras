#include <iostream>
#include <string>
#include <vector>
using std::string, std::vector, std::cout, std::endl;
 
// La Tabla de Hash sera un vector de apuntadores a nodo
struct nodo {
    // clave is string
    string clave;
    // valor is also string
    string valor;
    struct nodo* proximo;
};
struct TablaHash {
    // numero de elementos y tamaño de la tabla
    int num_elem, capacidad;
    // vector de apuntadores a nodo
    vector<nodo*> arr;
};
// Inicializar un nodo
void inicializarNodo(nodo& nodo, string clave, string valor) ;
 
// Inicializar la tabla
void inicializarTabla(TablaHash& tabla, int capacidad) ;
 
int hashCode(const TablaHash& tabla, string clave);

string buscar(const TablaHash& tabla, string clave);

void insertar(TablaHash& tabla, string clave, string valor) ;
 
void eliminar(TablaHash& tabla, string clave);
 