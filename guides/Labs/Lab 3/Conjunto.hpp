#include <vector>
using namespace std;
//typedef vector<int> Conjunto;  es igual a using
using Conjunto = vector<int> ;
Conjunto insertar(Conjunto, int);
void imprimir(Conjunto conj);
bool pertenece(Conjunto, int );
bool es_vacio(Conjunto);
Conjunto unir(Conjunto, Conjunto);