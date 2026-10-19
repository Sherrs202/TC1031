#ifndef CATALOGO_ISAAC_H
#define CATALOGO_ISAAC_H

#include "vector"
#include "string"
#include "fstream"
#include "sstream"
#include "iostream"
#include "Items.h"
#include "Ordenamiento.h"

// Clase del nodo para poder mas adelante utilizarlo bien
class Nodo {
    private:
        std::string nombre;
        Nodo *siguiente;
        Nodo *anterior;

        Nodo(const std::string&);

        friend class CatalogoIsaac;
};

//Constructor del nodo
Nodo::Nodo(const std::string& nom)
    : nombre(nom), siguiente(0){}

// Clase del nodo doble 
class NodoDoble {
    private:
        std::string nombre;
        NodoDoble* siguiente;
        NodoDoble* anterior;

        NodoDoble(const std::string&);

        friend class CatalogoIsaac;
};

// Constructor del nodo doble
NodoDoble::NodoDoble(const std::string& nom)
    : nombre(nom), siguiente(0), anterior(0){}

// Clase original 
class CatalogoIsaac {
private:
    std::vector<Items> inventario;
    bool estaOrdenado;
    // Linked list de favoritos
    Nodo* head;
    // Double Linked list del historial
    NodoDoble* headHistorial;
    NodoDoble* tailHistorial;
    

public:
    // Constructor: O(1) tiempo | O(1) espacio
    CatalogoIsaac();
    // Desctructor O(n) tiempo
    ~CatalogoIsaac();
    // Permite agregar un item de primero O(1) tiempo | 
    void addFirst(const std::string&);
    // Agrega un item al final de todo O(n) tiempo 
    void add(const std::string&);
    // Buscar si hay un item en la linked list O(n) tiempo
    bool contains(const std::string&) const;
    // Modifica el nombre de un item que ya tenemos guardado
    bool set(int, const std::string&);
    // Borrar un item de la lista
    bool remove(int);
    // Liberar memoria O(n) tiempo
    void clear();
    // Mostrar nuestros items fav
    std::string toStringFavoritos() const;
    void addHistorial(const std::string&);
    bool containsHistorial(const std::string&) const;
    bool setHistorial(int, const std::string&);
    bool removeHistorial(int);
    void clearHistorial();
    bool modificarNombreItem(int,const std::string&);
    bool modificarCalidadItem(int, int);
    bool modificarDanoItem(int, float);
    bool modificarLagrimasItem(int, float);
    bool modificarVelocidadItem(int, float);
    bool modificarRangoItem(int, float);
    std::string toStringHistorial() const;
    std::string toStringHistorialReversa() const;
    // Carga de archivo CSV: O(n) tiempo | O(n) espacio
    bool cargarDesdeCSV(const std::string& rutaArchivo);
    // Guardado en CSV: O(n) tiempo | O(1) espacio auxiliar
    bool guardarEnCSV(const std::string& rutaArchivo) const;
    // Ordenamiento por ID: O(n log n) tiempo | O(n) espacio
    void ordenarPorID();
    // Busqueda binaria por ID: O(log n) tiempo | O(1) espacio
    int buscarPorID(int idBuscado);
    // Busqueda secuencial por sala: O(n) tiempo | O(1) espacio
    int filtrarPorPool(const std::string& poolBuscada) const;
    // Alterna desbloqueo de un item: O(log n) tiempo | O(1) espacio
    bool modificarEstadoDesbloqueo(int id, bool nuevoEstado);
    // Despliegue en consola: O(n) tiempo | O(1) espacio
    void mostrarCatalogo() const;
    // Accesores: O(1) tiempo | O(1) espacio
    std::vector<Items>& getInventario();
    int getCantidadItems() const;
};

// ============================================================================
// DEFINICIONES FUERA DE LA CLASE
// ============================================================================

CatalogoIsaac::CatalogoIsaac() 
    : estaOrdenado(false), head(0),
      headHistorial(0), tailHistorial(0) {}

CatalogoIsaac::~CatalogoIsaac() {
    clear();
}

void CatalogoIsaac::addFirst(const std::string& nombre){
    Nodo* nuevo = new Nodo(nombre);

    nuevo->siguiente = head;
    head = nuevo;
}

void CatalogoIsaac::add(const std::string& nombre){
    Nodo* nodo;
    Nodo* p;

    if (head == 0){
        addFirst(nombre);
        return;
    }

    nodo = new Nodo(nombre);

    p = head;
    while (p->siguiente != 0){
        p = p->siguiente;
    }

    p->siguiente = nodo;
}

bool CatalogoIsaac::contains(const std::string& nombre) const {
    Nodo* p;

    p = head;

    while (p != 0){
        if (p->nombre == nombre){
            return true;
        }
        p = p->siguiente;
    }

    return false;
}

bool CatalogoIsaac::set(int index, const std::string& nombre){
    Nodo* p;
    int pos;

    if (index < 0){
        return false;
    }

    p = head;
    pos = 0;

    while (p != 0 && pos < index){
        p = p->siguiente;
        pos++;
    }

    if (p == 0){
        return false;
    }

    if (p->nombre != nombre) {
    addHistorial("Favorito modificado: " + p->nombre + " -> " + nombre);
    }

    p->nombre = nombre;
    return true;
}

bool CatalogoIsaac::remove(int index){
    Nodo* p;
    Nodo* anterior;
    int pos;

    if (index < 0 || head == 0){
        return false;
    }

    p = head;

    if (index == 0){
        head = p->siguiente;
        addHistorial("Eliminado de favoritos: " + p->nombre);
        delete p;
        return true;
    }

    anterior = 0;
    pos = 0;

    while (p != 0 && pos < index){
        anterior = p;
        p = p->siguiente;
        pos++;
    }

    if (p == 0){
        return false;
    }

    anterior->siguiente = p->siguiente;
    delete p;

    return true;
}

void CatalogoIsaac::clear(){
    Nodo* p;
    Nodo* q;

    p = head;

    while (p != 0){
        q = p->siguiente;
        delete p;
        p = q;
    }

    head = 0;
}

std::string CatalogoIsaac::toStringFavoritos() const{
    std::stringstream aux;
    Nodo* p;

    p = head;
    aux << "[";

    while (p != 0){
        aux << p->nombre;

        if (p->siguiente !=0){
            aux << ", ";
        }

        p = p->siguiente;
    }

    aux << "]";

    return aux.str();
}

void CatalogoIsaac::addHistorial(const std::string& nombre) {
    NodoDoble* nodo;

    nodo = new NodoDoble(nombre);

    if (headHistorial == 0) {
        headHistorial = nodo;
        tailHistorial = nodo;
    } else {
        tailHistorial->siguiente = nodo;
        nodo->anterior = tailHistorial;
        tailHistorial = nodo;
    }
}

bool CatalogoIsaac::containsHistorial(const std::string& nombre) const {
    NodoDoble* p;

    p = headHistorial;

    while(p != 0) {
        if (p->nombre == nombre) {
            return true;
        }

        p = p->siguiente;
    }

    return false;
}

bool CatalogoIsaac::setHistorial(int index, const std::string& nombre) {
    NodoDoble* p;
    int pos;

    if (index < 0){
        return false;
    }

    p = headHistorial;
    pos = 0;

    while (p != 0 && pos < index) {
        p = p->siguiente;
        pos++;
    }

    if (p == 0) {
        return false;
    }

    p->nombre = nombre;

    return true;
}

bool CatalogoIsaac::removeHistorial(int index) {
    NodoDoble* p;
    int pos;

    if (index < 0) {
        return false;
    }

    p = headHistorial;
    pos = 0;

    while (p != 0 && pos < index) {
        p = p->siguiente;
        pos++;
    }

    if (p == 0) {
        return false;
    }

    if (p->anterior != 0) {
        p->anterior->siguiente = p->siguiente;
    } else {
        headHistorial = p->siguiente;
    }

    if (p->siguiente != 0) {
        p->siguiente->anterior = p->anterior;
    } else {
        tailHistorial = p->anterior;
    }

    delete p;

    return true;
}

void CatalogoIsaac::clearHistorial(){
    NodoDoble* p;
    NodoDoble* q;

    p = headHistorial;

    while (p != 0) {
        q = p->siguiente;
        delete p;
        p = q;
    }

    headHistorial = 0;
    tailHistorial = 0;
}

std::string CatalogoIsaac::toStringHistorial() const {
    std::stringstream aux;
    NodoDoble* p;

    p = headHistorial;
    aux << "[";

    while (p != 0) {
        aux << p->nombre;

        if (p->siguiente != 0) {
            aux << ", ";
        }

        p = p->siguiente;
    }

    aux << "]";

    return aux.str();
}

std::string CatalogoIsaac::toStringHistorialReversa() const {
    std::stringstream aux;
    NodoDoble* p;

    p = tailHistorial;
    aux << "[";

    while (p != 0) {
        aux << p->nombre;

        if (p->anterior != 0) {
            aux << ", ";
        }

        p = p->anterior;
    }

    aux << "]";

    return aux.str();
}

bool CatalogoIsaac::cargarDesdeCSV(const std::string& rutaArchivo) {
    inventario.clear();
    std::ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo "
                  << rutaArchivo << "\n";
        return false;
    }

    std::string linea;
    std::getline(archivo, linea); // Omitir encabezado

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string idStr, nombre, tipo, pool, calStr;
        std::string danoStr, lagStr, velStr, ranStr, desbStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, tipo, ',');
        std::getline(ss, pool, ',');
        std::getline(ss, calStr, ',');
        std::getline(ss, danoStr, ',');
        std::getline(ss, lagStr, ',');
        std::getline(ss, velStr, ',');
        std::getline(ss, ranStr, ',');
        std::getline(ss, desbStr); // Lee hasta fin de linea

        if (!idStr.empty()) {
            int id = std::stoi(idStr);
            int cal = std::stoi(calStr);
            float dano = std::stof(danoStr);
            float lag = std::stof(lagStr);
            float vel = std::stof(velStr);
            float ran = std::stof(ranStr);
            bool desb = (!desbStr.empty() && desbStr[0] == '1');

            Items nuevoItem(id, nombre, tipo, pool, cal,
                            dano, lag, vel, ran, desb);
            inventario.push_back(nuevoItem);
        }
    }

    archivo.close();
    estaOrdenado = false;
    return true;
}

bool CatalogoIsaac::guardarEnCSV(const std::string& rutaArchivo) const {
    std::ofstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo guardar en "
                  << rutaArchivo << "\n";
        return false;
    }

    archivo << "id,nombre,tipo,pool,calidad,mod_dano,mod_lagrimas,"
            << "mod_velocidad,mod_rango,desbloqueado\n";

    for (const auto& item : inventario) {
        archivo << item.getId() << ","
                << item.getNombre() << ","
                << item.getTipo() << ","
                << item.getPool() << ","
                << item.getCalidad() << ","
                << item.getModDano() << ","
                << item.getModLagrimas() << ","
                << item.getModVelocidad() << ","
                << item.getModRango() << ","
                << (item.isDesbloqueado() ? 1 : 0) << "\n";
    }

    archivo.close();
    return true;
}

void CatalogoIsaac::ordenarPorID() {
    Ordenamiento ordenador;
    ordenador.mergeSortPorID(inventario);
    estaOrdenado = true;
}

int CatalogoIsaac::buscarPorID(int idBuscado) {
    if (!estaOrdenado) {
        ordenarPorID();
    }

    int inicio = 0;
    int fin = inventario.size() - 1;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;

        if (inventario[medio].getId() == idBuscado) {
            return medio;
        }
        if (inventario[medio].getId() < idBuscado) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }

    return -1;
}

int CatalogoIsaac::filtrarPorPool(const std::string& poolBuscada) const {
    int coincidencias = 0;
    std::cout << "\n--- Items encontrados en la sala ["
              << poolBuscada << "] ---\n";

    for (const auto& item : inventario) {
        if (item.getPool() == poolBuscada) {
            item.imprimirFicha();
            coincidencias++;
        }
    }

    if (coincidencias == 0) {
        std::cout << "No se encontraron items registrados en la pool '"
                  << poolBuscada << "'.\n";
    }
    return coincidencias;
}

bool CatalogoIsaac::modificarEstadoDesbloqueo(int id, bool nuevoEstado) {
    int idx = buscarPorID(id);

    if (idx != -1) {
        bool estadoAnterior = inventario[idx].isDesbloqueado();

        if (estadoAnterior != nuevoEstado) {
            inventario[idx].setDesbloqueado(nuevoEstado);

            std::string nombre = inventario[idx].getNombre();

            if (nuevoEstado) {
                addHistorial("Item desbloqueado: " + nombre +
                             " (Bloqueado -> Desbloqueado)");
            } else {
                addHistorial("Item bloqueado: " + nombre +
                             " (Desbloqueado -> Bloqueado)");
            }
        }

        return true;
    }

    return false;
}

bool CatalogoIsaac::modificarNombreItem(int id, const std::string& nuevoNombre) {
    int idx = buscarPorID(id);

    if (idx == -1 || nuevoNombre.empty()) {
        return false;
    }

    std::string nombreAnterior = inventario[idx].getNombre();

    if (nombreAnterior == nuevoNombre) {
        return false;
    }

    inventario[idx].setNombre(nuevoNombre);

    addHistorial("Catalogo - Nombre modificado: " +
                 nombreAnterior + " -> " + nuevoNombre +
                 " (ID: " + std::to_string(id) + ")");

    return true;
}

bool CatalogoIsaac::modificarCalidadItem(int id, int nuevaCalidad) {
    int idx = buscarPorID(id);

    if (idx == -1 || nuevaCalidad < 0 || nuevaCalidad > 4) {
        return false;
    }

    int calidadAnterior = inventario[idx].getCalidad();

    if (calidadAnterior == nuevaCalidad) {
        return false;
    }

    inventario[idx].setCalidad(nuevaCalidad);

    std::string nombre = inventario[idx].getNombre();

    addHistorial("Catalogo - Calidad modificada: " + nombre +
                 " (" + std::to_string(calidadAnterior) +
                 " -> " + std::to_string(nuevaCalidad) + ")");

    return true;
}

bool CatalogoIsaac::modificarDanoItem(int id, float nuevoDano) {
    int idx = buscarPorID(id);

    if (idx == -1) {
        return false;
    }

    float danoAnterior = inventario[idx].getModDano();

    if (danoAnterior == nuevoDano) {
        return false;
    }

    inventario[idx].setModDano(nuevoDano);

    std::string nombre = inventario[idx].getNombre();

    addHistorial("Catalogo - Dano modificado: " + nombre +
                 " (" + std::to_string(danoAnterior) +
                 " -> " + std::to_string(nuevoDano) +
                 ") ID: " + std::to_string(id));

    return true;
}

bool CatalogoIsaac::modificarLagrimasItem(int id, float nuevasLagrimas) {
    int idx = buscarPorID(id);

    if (idx == -1) {
        return false;
    }

    float lagrimasAnteriores = inventario[idx].getModLagrimas();

    if (lagrimasAnteriores == nuevasLagrimas) {
        return false;
    }

    inventario[idx].setModLagrimas(nuevasLagrimas);

    std::string nombre = inventario[idx].getNombre();

    addHistorial("Catalogo - Lagrimas modificadas: " + nombre +
                 " (" + std::to_string(lagrimasAnteriores) +
                 " -> " + std::to_string(nuevasLagrimas) +
                 ") ID: " + std::to_string(id));

    return true;
}

bool CatalogoIsaac::modificarVelocidadItem(int id, float nuevaVelocidad) {
    int idx = buscarPorID(id);

    if (idx == -1) {
        return false;
    }

    float velocidadAnterior = inventario[idx].getModVelocidad();

    if (velocidadAnterior == nuevaVelocidad) {
        return false;
    }

    inventario[idx].setModVelocidad(nuevaVelocidad);

    std::string nombre = inventario[idx].getNombre();

    addHistorial("Catalogo - Velocidad modificada: " + nombre +
                 " (" + std::to_string(velocidadAnterior) +
                 " -> " + std::to_string(nuevaVelocidad) +
                 ") ID: " + std::to_string(id));

    return true;
}

bool CatalogoIsaac::modificarRangoItem(int id, float nuevoRango) {
    int idx = buscarPorID(id);

    if (idx == -1) {
        return false;
    }

    float rangoAnterior = inventario[idx].getModRango();

    if (rangoAnterior == nuevoRango) {
        return false;
    }

    inventario[idx].setModRango(nuevoRango);

    std::string nombre = inventario[idx].getNombre();

    addHistorial("Catalogo - Rango modificado: " + nombre +
                 " (" + std::to_string(rangoAnterior) +
                 " -> " + std::to_string(nuevoRango) +
                 ") ID: " + std::to_string(id));

    return true;
}

void CatalogoIsaac::mostrarCatalogo() const {
    std::cout << "\n============================== "
              << "CATALOGO PLATINUM GOD "
              << "==============================\n";
    for (const auto& item : inventario) {
        item.imprimirFicha();
    }
    std::cout << "=============================="
              << "=====================================================\n";
}

std::vector<Items>& CatalogoIsaac::getInventario() {
    return inventario;
}

int CatalogoIsaac::getCantidadItems() const {
    return inventario.size();
}

#endif
