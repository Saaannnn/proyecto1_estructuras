#include <iostream>
#include "Conjunto.hpp"

int main(){
    Conjunto conj;
    conj = insertar(conj,0);
    conj = insertar(conj,1);
    conj = insertar(conj,2);
    imprimir(conj);
    int i=3;
    std::cout << "¿Está " << i  << " en el conjunto?: " 
       <<  std::boolalpha << pertenece(conj,i) 
       << "   Es vacio?: " << es_vacio(conj);
    Conjunto conj1;
    conj1 = insertar(conj1,0);
    conj1 = insertar(conj1,4);
    conj1 = insertar(conj1,5);
    Conjunto c = unir(conj,conj1);
    imprimir(c);
}
