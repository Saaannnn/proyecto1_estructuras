//#include <vector> ya está en .h
#include <iostream>
#include "conjunto_ref.h"

Conjunto crear_conjunto_vacio(){
    return {};
}
void insertar(Conjunto &v, int i){
    // Verificar que no esté para poderlo insertar
    for (int j=0; j<v.size(); j++){
        if (i==v[j]) return;
    }
    v.push_back(i);
}
bool pertenece(const Conjunto &v, int i){
    // Verificar que no esté para poderlo insertar
    for (int j=0; j<v.size(); j++){
        if (i==v[j]) return true;
    }
    return false;
}
void imprimir(const Conjunto &conj){
    for (int j=0; j<conj.size(); j++)
        std::cout << conj[j] << " " ;
}
Conjunto intersectar(const Conjunto & A, const Conjunto & B){
    Conjunto C;
    for (int i:A)
      if (pertenece(B,i))  insertar(C,i);
    return C;
}

bool esvacio(const Conjunto& C){
    return (C.size()==0);
}