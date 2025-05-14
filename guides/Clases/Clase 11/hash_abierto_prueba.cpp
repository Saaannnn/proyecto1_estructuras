#include "hash_abierto.h"
using std::string, std::vector, std::cout, std::endl;
 
// codigo de prueba
int main()
{
    // Inicializzar la Tabla tabla
    TablaHash tabla ;
    inicializarTabla(tabla,2);
    insertar(tabla, "3456", "Carlos Perez");
    insertar(tabla, "0000", "Martha");
    imprimir(tabla);
    insertar(tabla, "2391", "Maria Hernandez");
    imprimir(tabla);
    insertar(tabla, "3345", "Oscar Delgado");
    
    imprimir(tabla);
    std::cout << tabla.num_elem << std::endl;
    std::cout << buscar(tabla, "3345") << std::endl;
    std::cout << buscar(tabla, "2391") << std::endl;
    std::cout << buscar(tabla, "3456") << std::endl;
    
   // clave no existe
    std::cout << buscar(tabla, "9999") << std::endl;
    insertar(tabla, "2391", "Maria Hernandez");
    imprimir(tabla);
    
    // Borrar nodo con clave dada
    eliminar(tabla, "3456");
    imprimir(tabla);
    std::cout << tabla.num_elem << std::endl;
    // Buscar clave borrada
    std::cout << buscar(tabla, "3456") << std::endl;
				vaciar(tabla);
    return 0;
}