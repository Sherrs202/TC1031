#ifndef ITEMS_H
#define ITEMS_H

#include "string"
#include "iostream"
#include "iomanip"

class Items {
private:
    int id;
    std::string nombre;
    std::string tipo;
    std::string pool;
    int calidad;
    float modDano;
    float modLagrimas;
    float modVelocidad;
    float modRango;
    bool desbloqueado;

public:
    // Constructor por defecto: O(1) tiempo | O(1) espacio
    Items();

    // Constructor con parametros: O(1) tiempo | O(1) espacio
    Items(int _id, const std::string& _nombre, const std::string& _tipo,
          const std::string& _pool, int _calidad, float _dano,
          float _lagrimas, float _velocidad, float _rango,
          bool _desbloqueado);

    // Getters: O(1) tiempo | O(1) espacio
    int getId() const;
    std::string getNombre() const;
    std::string getTipo() const;
    std::string getPool() const;
    int getCalidad() const;
    float getModDano() const;
    float getModLagrimas() const;
    float getModVelocidad() const;
    float getModRango() const;
    bool isDesbloqueado() const;

    // Setter: O(1) tiempo | O(1) espacio
    void setDesbloqueado(bool estado);
    void setNombre(const std::string&);
    void setCalidad(int);
    void setModDano(float);
    void setModLagrimas(float);
    void setModVelocidad(float);
    void setModRango(float);

    // Sobrecargas de operadores: O(1) tiempo | O(1) espacio
    bool operator<(const Items& otro) const;
    bool operator==(const Items& otro) const;

    // Metodo de despliegue en consola: O(1) tiempo | O(1) espacio
    void imprimirFicha() const;
};

// DEFINICIONES FUERA DE LA CLASE

Items::Items()
    : id(0), nombre(""), tipo(""), pool(""), calidad(0),
      modDano(0.0f), modLagrimas(0.0f), modVelocidad(0.0f),
      modRango(0.0f), desbloqueado(false) {}

Items::Items(int _id, const std::string& _nombre,
             const std::string& _tipo, const std::string& _pool,
             int _calidad, float _dano, float _lagrimas,
             float _velocidad, float _rango, bool _desbloqueado)
    : id(_id), nombre(_nombre), tipo(_tipo), pool(_pool),
      calidad(_calidad), modDano(_dano), modLagrimas(_lagrimas),
      modVelocidad(_velocidad), modRango(_rango),
      desbloqueado(_desbloqueado) {}

int Items::getId() const {
    return id;
}

std::string Items::getNombre() const {
    return nombre;
}

std::string Items::getTipo() const {
    return tipo;
}

std::string Items::getPool() const {
    return pool;
}

int Items::getCalidad() const {
    return calidad;
}

float Items::getModDano() const {
    return modDano;
}

float Items::getModLagrimas() const {
    return modLagrimas;
}

float Items::getModVelocidad() const {
    return modVelocidad;
}

float Items::getModRango() const {
    return modRango;
}

bool Items::isDesbloqueado() const {
    return desbloqueado;
}

void Items::setDesbloqueado(bool estado) {
    desbloqueado = estado;
}

void Items::setNombre(const std::string& nuevoNombre) {
    nombre = nuevoNombre;
}

void Items::setCalidad(int nuevaCalidad) {
    calidad = nuevaCalidad;
}

void Items::setModDano(float nuevoDano) {
    modDano = nuevoDano;
}

void Items::setModLagrimas(float nuevasLagrimas) {
    modLagrimas = nuevasLagrimas;
}

void Items::setModVelocidad(float nuevaVelocidad) {
    modVelocidad = nuevaVelocidad;
}

void Items::setModRango(float nuevoRango) {
    modRango = nuevoRango;
}

bool Items::operator<(const Items& otro) const {
    return this->id < otro.id;
}

bool Items::operator==(const Items& otro) const {
    return this->id == otro.id;
}

void Items::imprimirFicha() const {
    std::cout << "#" << std::setw(3) << id << " | "
              << std::setw(16) << std::left << nombre << " | "
              << "Tipo: " << std::setw(7) << tipo << " | "
              << "Pool: " << std::setw(8) << pool << " | "
              << "Q: " << calidad << " | "
              << "Dmg: " << std::showpos << modDano << " | "
              << "Tears: " << modLagrimas << " | "
              << std::noshowpos
              << "Estado: "
              << (desbloqueado ? "[Desbloqueado]" : "[Bloqueado]")
              << "\n";
}

#endif
