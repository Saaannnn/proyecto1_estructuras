#include "lista_simple.h"

Lista_simple crear_vacia(){
    return nullptr;
}
void vaciar_lista(Lista_simple &lista){ //necesito & porque modifico lista
    for (Nodo *cursor = lista,   *temp;
            cursor != nullptr;      ) {
        temp = cursor;
        cursor = cursor->proximo;
        delete temp;
    }
    lista = nullptr;
}
void eliminar_primero(Lista_simple  &lista){
      if (lista!=nullptr){
            Nodo* temp = lista;
            lista = lista->proximo;
           delete temp;
      }
}
void eliminar_primero(Lista_simple  *lista){
      if ((*lista)!=nullptr){
            Nodo* temp = (*lista);
            (*lista) = (*lista)->proximo;
           delete temp;
      }
}


void insertar(Lista_simple &lista, seccion datos){
    if (lista == nullptr)
        lista = new Nodo{{datos.profesor,datos.estudiantes},0,nullptr} ;
    else   // lo inserta de primero
        lista = new Nodo{{datos.profesor,datos.estudiantes},0,lista};
}
void insertar_cola(Lista_simple &lista, seccion datos){
    if (lista == nullptr)
        lista = new Nodo{{datos.profesor,datos.estudiantes},0,nullptr} ;
    else {   // lo inserta de ultimo
        Nodo *cursor = lista;
        while (cursor->proximo != nullptr)
               cursor = cursor->proximo;
        cursor->proximo = new Nodo{{datos.profesor,datos.estudiantes},0,nullptr} ;
    }
}
void insertar_cola(Lista_simple &lista, Nodo* nodo){
    // nodo debe tener proximo en null
    if (lista == nullptr)
        lista = nodo ;
    else {   // lo inserta de ultimo
        Nodo *cursor = lista;
        while (cursor->proximo != nullptr)
               cursor = cursor->proximo;
        cursor->proximo = nodo ;
    }
}
void imprimir(const Lista_simple  & lista){ 
            // no permite const Lista_simple & lista
           // pues lo asignamos al pointer "cursor" y 
           // esto seria ilegal  pues podriamos modificar
           // los valores a los que apunta la constante
    cout<<"SECCIONES:\n";
    for (Nodo *cursor = lista; cursor != nullptr; 
        cursor = cursor->proximo) {
        std::cout << "{ "<< cursor->datos.profesor << " , ";
        imprimir(cursor->datos.estudiantes);
        std::cout <<"} ," " hora: "<< cursor->hora<<"  \n";
    }
}

void invertir(Lista_simple &lista){
    if (lista==nullptr) return;
    Nodo* tmp = lista;
    Nodo* proximo = lista->proximo;
    tmp->proximo = nullptr;
    invertir (proximo);
    insertar_cola(proximo,tmp);
    lista = proximo;
}

void invertir_iter(Lista_simple &lista){
    if (lista==nullptr) return;
    Nodo* anterior;
    Nodo* actual;
    Nodo* tmp;
    anterior = nullptr; actual = lista; 
    while (actual != nullptr ){    
        tmp=actual;
        actual = actual->proximo;
        tmp->proximo = anterior;
        anterior = tmp;
    }
    lista=anterior;
}

int num_elem(const Lista_simple& lista){

    int numero = 0;
	Nodo* sig = lista;
	while (sig != nullptr) numero++;
	return numero;
}

/**
 * hacer_asignacion(Lista_simple& lista):
 * 
 *      Calcula la asignacion de horarios de las secciones de clases dadas por 
 *      "lista". 
 *      "lista" es una lista enlazada donde cada nodo representa una sección
 *      Cada seccion solo posee una sola hora a ser asignada.
 *      Se asignará una hora entre 1 y 10. 
 *      Se recorre la lista desde el primer elemento hasta el último. 
 *      Y se van procesando sus secciones (nodos) una a una.
 *      Al procesar una sección (nodo de la lista) se le asignará la menor hora
 *      de 1 a 10 que no coincida con las horas ya asignadas de las secciones 
 *      previamente procesadas (anteriores en la lista) a ella y que estén en
 *      conflicto con ella (tengan el mismo profesor o 
 *      estudiantes en común). 
 *      Note que si la sección que se está procesando está en conflicto con
 *      secciones a las que ya se les ha asignado todas las horas disponibles
 *      que son del 1 al 10, entonces a esa sección no se le asigna hora.
 *      
 *      parámetros:
 *          lista: la lista de secciones que se les asignará horario.
 */
void hacer_asignacion(Lista_simple& lista){
/*     Lista_simple recorre_secciones=lista, anterior_seccion;
    vector<int> horas(10,0);
    while (recorre_secciones!=nullptr){
        anterior_seccion=lista;
        while (anterior_seccion!=recorre_secciones) {
            // Si hay conflicto marcar hora de anterior_seccion en horas[]



        }
        int i=0;
        // escoger la menor hora disponible de horas[] para asignarla 
        // a la seccion
        while(i<horas.size()){



            i++;
        }
        // aqui se deberia guardar la seccion asignada en el archivo
        // note que si i=horas.size() entonces no se pudo asignar hora a la seccion
        // igual se deberia guardar la seccion indicando que no hay horas asignadas
        recorre_secciones=recorre_secciones->proximo;
        horas.assign(horas.size(),0); // se inicializa horas[] todos en 0
    } */
}

