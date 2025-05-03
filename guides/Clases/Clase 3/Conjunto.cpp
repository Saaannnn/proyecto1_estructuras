//#include <vector> ya está en .h
#include <iostream>
#include "Conjunto.hpp"

Conjunto insertar(Conjunto v, int i){
    // Verificar que no esté para poderlo insertar
    for (int j=0; j<v.size(); j++){
        if (i==v[j]) return v;
    }
    v.push_back(i);
    return v;
}
bool pertenece(Conjunto v, int i){
    // Verificar que no esté para poderlo insertar
    for (int j=0; j<v.size(); j++){
        if (i==v[j]) return true;
    }
    return false;
}
void imprimir(Conjunto conj){
    for (int j=0; j<conj.size(); j++)
        std::cout << conj[j] << " " ;
				std::cout<<endl;
}
bool es_vacio(Conjunto conj){
    if (conj.empty()) return true;
    else return false;
}

Conjunto unir(Conjunto A, Conjunto B){
    Conjunto result;
    for (auto i : A)
       result.push_back(i);
    for (auto i : B)
       if (! pertenece(A,i))
          result.push_back(i);
    return result;

}
