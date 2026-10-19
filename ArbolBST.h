#ifndef ARBOL_BST_H
#define ARBOL_BST_H

#include <iostream>
#include <sstream>

// Clase NodoArbol
class NodoArbol {
    private:
        int id;
        NodoArbol* izquierda;
        NodoArbol* derecha;
        NodoArbol(int);
        friend class ArbolBST;

};

// Constructor de NodoArbol
NodoArbol::NodoArbol(int valor)
    : id(valor), izquierda(0), derecha(0) {}

// Clase ArbolBST
class ArbolBST {
    private:
        NodoArbol* raiz;
        void  inorder(NodoArbol*) const;
        int calcularAltura(NodoArbol*) const;
        void liberar(NodoArbol*);
    
    public:
        ArbolBST();
        ~ArbolBST();
        ArbolBST(const ArbolBST&) = delete;
        ArbolBST& operator=(const ArbolBST&) = delete;
        bool insertar (int);
        void visit() const;
        int height() const;
        bool ancestors(int) const;
        int currentLevel(int) const;
    
};

// Constructor de ArbolBST
ArbolBST::ArbolBST() : raiz(0) {}

// Implementacion de insertar
bool ArbolBST::insertar(int id) {
    NodoArbol* actual;
    NodoArbol* padre;

    actual = raiz;
    padre = 0;

    while (actual != 0) {
        padre = actual;

        if (id == actual->id) {
            return false;
        }

        if (id < actual->id) {
            actual = actual->izquierda;
        } else {
            actual = actual->derecha;
        }
    }

    NodoArbol* nuevo = new NodoArbol(id);

    if (padre == 0) {
        raiz = nuevo;
    } else if (id < padre->id) {
        padre->izquierda = nuevo;
    } else {
        padre->derecha = nuevo;
    }

    return true;
}

void ArbolBST::inorder(NodoArbol* actual) const {
    if (actual != 0) {
        inorder(actual->izquierda);
        std::cout << actual->id << " ";
        inorder(actual->derecha);
    }
}

void ArbolBST::visit() const {
    std::cout << "\n RECORRIDO INORDER BST \n";
    inorder(raiz);
    std::cout << "\n";
}

int ArbolBST::calcularAltura(NodoArbol* actual) const {
    if (actual == 0) {
        return -1;
    }

    int alturaIzquierda = calcularAltura(actual->izquierda);
    int alturaDerecha = calcularAltura(actual->derecha);

    if (alturaIzquierda > alturaDerecha) {
        return alturaIzquierda +1;
    } else {
        return alturaDerecha +1;
    }
    
}

int ArbolBST::height() const {
    return calcularAltura(raiz);
}

bool ArbolBST::ancestors(int id) const {
    NodoArbol* actual;
    std::stringstream camino;

    actual = raiz;

    while (actual != 0) {

        if (id == actual->id) {

            if (actual == raiz) {
                std::cout << "El nodo es la raiz y no tiene antecesores.\n";
            } else {
                std::cout << "Antecesores del ID " << id << ": "
                          << camino.str() << "\n";
            }

            return true;
        }

        camino << actual->id << " ";

        if (id < actual->id) {
            actual = actual->izquierda;
        } else {
            actual = actual->derecha;
        }
    }

    return false;
}

int ArbolBST::currentLevel(int id) const {
    NodoArbol* actual;
    int nivel;

    actual = raiz;
    nivel = 0;

    while (actual != 0) {
        if (id == actual->id) {
            return nivel;
        }

        if (id < actual->id) {
            actual = actual->izquierda;
        } else {
            actual = actual->derecha;
        }

        nivel++;
    }

    return -1;
}

void ArbolBST::liberar(NodoArbol* actual) {
    if (actual != 0) {
        liberar(actual->izquierda);
        liberar(actual->derecha);

        delete actual;
    }
}

ArbolBST::~ArbolBST() {
    liberar(raiz);
    raiz = 0;
}

#endif