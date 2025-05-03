#include <vector>
using namespace std;
//typedef vector<int> Conjunto;  es igual a using
using Conjunto = vector<int> ;
Conjunto crear_conjunto_vacio();
void insertar(Conjunto & , int);
void imprimir(const Conjunto & ) ;
bool pertenece(const Conjunto & , int );
Conjunto intersectar(const Conjunto & , const Conjunto & );
bool esvacio(const Conjunto& );
