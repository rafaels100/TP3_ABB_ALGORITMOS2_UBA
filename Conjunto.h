#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Conjunto
{
    public:

        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remover(const T&);

        // Siguiente elemento al recibido por párametro, en orden.
        const T& siguiente(const T& elem);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        // Devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto.
        void mostrar(std::ostream&) const;

    private:
        struct Nodo
        {
            // El constructor, toma el elemento al que representa el nodo.
            Nodo(const T& v) : valor(v), izq(nullptr), der(nullptr){};
            // El elemento al que representa el nodo.
            T valor;
            // Puntero a la raíz del subárbol izquierdo.
            Nodo* izq;
            // Puntero a la raíz del subárbol derecho.
            Nodo* der; 
        };
        // Puntero a la raíz de nuestro árbol.
        Nodo* _raiz;

        //ayudante del cardinal
        unsigned int cardinalAux(const Nodo* nodo) const;

        //ayudante del insertar
        void insertarAux(const T&, Nodo* nodo);

        //ayudante del pertenece
        bool perteneceAux(const T&, const Nodo* nodo) const;

        //ayudantes del remover
        void removerAux(const T&, Nodo* nodo);
        void eliminarMatch(Nodo* padre, Nodo* match, const bool izq);
        void eliminarRaiz();
        //obtener el valor al minimo del mas pequenio del arbol/subarbol
        const T& getMinimoSubArbol(Nodo* padre) const;
        const T& getMaximoSubArbol(Nodo* padre) const;

        //ayudante del siguiente
        const T& siguienteAux(Nodo* parent, Nodo* succ, const T& elem) const;

        //ayudante del destructor
        void destr_Aux(Nodo* nodo);

};

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
