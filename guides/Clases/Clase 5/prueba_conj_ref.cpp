#include <iostream>
#include "conjunto_ref.h"

int main(){
    Conjunto conj;
    insertar(conj,0);
    insertar(conj,1);
    insertar(conj,2);
    imprimir(conj);
    int i=3;
    std::cout << "¿Está " << i  << " en el conjunto?: " 
       << std::boolalpha << verificar(conj,i)<< std::endl; 
    
    
    // arreglos funciona for basado en rango
    double xx[] {1,2,3,4};
    
    for (auto elem : xx)
        std::cout << elem; 
}