struct Nodo {
  int data; 
  Nodo *anterior;
  Nodo *proximo;
};
struct Lista_dob_enl{
  Nodo* cabeza = nullptr;
  Nodo* cola = nullptr;
  int num_elem=0; 
} ;
Lista_dob_enl crear_lista_vacia();
void insertar(Lista_dob_enl &, int , int pos);
void imprimir(const Lista_dob_enl &);
void eliminar(Lista_dob_enl &, int pos );
bool esVacia(const Lista_dob_enl &);