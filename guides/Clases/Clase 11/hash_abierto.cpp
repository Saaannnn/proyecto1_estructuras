#include "hash_abierto.h"
using std::string, std::vector, std::cout, std::endl;
 
void inicializarNodo(nodo& nodo, string clave, string valor) {
    nodo.clave = clave;
    nodo.valor = valor;
    nodo.proximo = nullptr;
}
  
// Inicializar la tabla
void inicializarTabla(TablaHash& tabla, int capacidad) {
    // tamaño de la tabla
    tabla.capacidad = capacidad;
    tabla.num_elem = 0;
    // crea vector con cada elemento nullptr
    tabla.arr = vector<nodo*>(tabla.capacidad);
    
}
 
int hashCode(const TablaHash& tabla, string clave) {
    // devuel de una vez el índice de la tabla donde
    //  que corresponde a clave
    long long suma = 0, factor = 1;
    for (int i = 0; i < clave.size(); i++) {
        // suma = suma + (valor asscii de
        // char * (primo ^ x))...
        // donde x = 0, 1, 2, 3....n
        suma = (suma  + 
            (((int)clave[i]) * factor) % tabla.capacidad) % tabla.capacidad;
        factor = (factor * 37)% tabla.capacidad;
    }
    // si por overflow da negativo, ponerlo positivo
    if (suma<0) {
        suma += tabla.capacidad; 
    }
    return suma;
}

string buscar(const TablaHash& tabla, string clave) {
    // Obtener el indice de la casilla de la clave
    int indiceCasilla = hashCode(tabla, clave);
    // Apunta a la cabeza de la lista
    nodo* cabezaCasilla = tabla.arr[indiceCasilla];
    
    while (cabezaCasilla != nullptr) {
        
        // Si la clave esta
        if (cabezaCasilla->clave == clave) {
            return cabezaCasilla->valor;
        }
        
        cabezaCasilla = cabezaCasilla->proximo;
    }
    
    // Si la clave no se consigue
    
    return "No se encontro";
}

// hay que colocar el protocolo de insertar 
// porque lo usa reshash y veciversa
void insertar(TablaHash& tabla, string clave, string valor) ;
void rehash(TablaHash& tabla){
    TablaHash vieja = tabla;
    inicializarTabla(tabla,vieja.capacidad*2);
    nodo* tmp;
    for (int i=0; i<vieja.capacidad; i++){      
        tmp = vieja.arr[i];
        while (tmp!=nullptr){
            insertar(tabla,tmp->clave,tmp->valor);
            tmp = tmp->proximo;
        }
    }
    vaciar(vieja);
}

void insertar(TablaHash& tabla, string clave, string valor) {
    if (buscar(tabla,clave)!="No se encontro") return;
    
    //comprobar factor de carga para hacer rehash
    // si el num elem mas el que voy a insertar hace el 
    // factor de carga > 0.6 hacer rehash
    // el (1.0) es para convertir a double
    if ((tabla.num_elem+1)*(1.0)/tabla.capacidad > 0.6) rehash(tabla);
    // Se busca el indice donde ira clave valor
    int indiceCasilla = hashCode(tabla, clave);
    // se crea e inicializa un nodo
    nodo* nuevoNodo = new nodo;
    inicializarNodo((*nuevoNodo), clave, valor);
    // la casilla esta vacia, no hay colision
    if (tabla.arr[indiceCasilla] == nullptr) {
        tabla.arr[indiceCasilla] = nuevoNodo;
    }
    // Colision
    else {
        // agregar nodo de primeo en la lista
        nuevoNodo->proximo = tabla.arr[indiceCasilla];
        tabla.arr[indiceCasilla] = nuevoNodo;
    }
    tabla.num_elem++;
}
 
void eliminar(TablaHash& tabla, string clave) {
    // obtener indice casilla para la clave dada
    int indiceCasilla = hashCode(tabla, clave);
    nodo* anterior = nullptr;
    // apuntar a la cabeza de la lista apuntada por la casilla
    nodo* nodoActual = tabla.arr[indiceCasilla];
    while (nodoActual != nullptr) {
        // borrar nodo si coincide su clave
        if (clave == nodoActual->clave)  {
            // Borrar la cabeza de la lista
            if (nodoActual == tabla.arr[indiceCasilla]) {
                tabla.arr[indiceCasilla] = nodoActual->proximo;
            }
            // Borrar otro nodo
            else {
                anterior->proximo = nodoActual->proximo;
            }
            delete nodoActual;
            tabla.num_elem--;
            break;
        }
 
        anterior = nodoActual;
        nodoActual = nodoActual->proximo;
    }
    return;
}
 