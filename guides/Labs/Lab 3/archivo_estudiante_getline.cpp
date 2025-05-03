#include <iostream>
#include <fstream>
#include <string>	
#include <vector>
#include <sstream>
using namespace std;
// crea un archivo de estudiantes:
//    carlos perez 31456456 17 15
//    oscar meza 34567654 18 12
// Luego lee el archivo de estudiantes y lo guarda en un vector
struct estudiante{
    std::string nombre;
    std::string apellido;
    std::string cedula;
    int edad;
    double promedio;
};
void Extraer(const string Text, vector<estudiante>& vector) {
    estudiante var;
    std::stringstream ss(Text); // ss es un stream
    ss>>var.nombre;
    ss>>var.apellido;
    ss>>var.cedula;
    ss>>var.edad;
    ss>>var.promedio;
    vector.push_back(var);
 }	

estudiante mayor_promedio(std::vector<estudiante> v){
    estudiante est_mayor_promedio ;
    est_mayor_promedio.promedio=-1;
    for (auto est: v) 
        if (est.promedio > est_mayor_promedio.promedio) 
            est_mayor_promedio = est;
    return est_mayor_promedio;
}
int main() {
	std::string line;
	std::string filename;
	std::cout << " Coloque el nombre del archivo: ";  
    std::cin >> filename;
	// cin queda con una linea vacia que hay que leer
	getline(std::cin,line);

	// crear archivo y guardar en el archivo cada linea  leida
    std::ofstream out(filename);
	// ingrese los numeros a ser guardados en el archivo
    if (out.is_open())  { // si se abrio bien el archivo
	  // colocar varios enteros y terminar con un caracter
			std::cout << " Coloque las lineas una a una y al final una linea vacia: \n";
			getline(std::cin,line);
			// note que al final del archivo habra una linea vacia
			// debido al "\n" de la ultima linea a ingresar
			while ( line!="" ){ 
				 out << line << "\n";   // se creara una linea vacia al final
				 getline (std::cin,line);
			}
	}
     else
       std::cout << "No se pudo escribir en el archivo\n";
	
	out.close();
	

	std::cout << " Coloque el nombre del archivo: ";  
	std::string text;
	std::cin >> filename;
	std::ifstream in(filename);
    if (in.is_open()){

        std::vector<estudiante> v;
        //estudiante var;
        while(!in.eof()) 
        {
        getline(in,text);
        if (text!="")
            Extraer (text,v);
        }
        std::cout << "tamaño= "<<v.size()<< std::endl;
        estudiante est = mayor_promedio(v);
        std::cout << est.nombre<< " " << est. apellido << std::endl;
    }
    in.close();
    return 0;
 }  