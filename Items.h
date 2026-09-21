#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <iostream>
#include <iomanip>

class Items {
    private :
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
    //constructor por defecto
    Items()
        :id(0),nombre(""), tipo(""), pool(""), calidad(0),
        modDano(0.0f), modLagrimas(0.0f), modVelocidad(0.0f), 
        modRango(0.0f), desbloqueado(false) {}
    
    // Constructor con parametros para inicializar desde el CSV
    Items(int _id, const std::string& _nombre, const std::string& _tipo, 
         const std::string& _pool, int _calidad, float _dano, 
         float _lagrimas, float _velocidad, float _rango, bool _desbloqueado)
        : id(_id), nombre(_nombre), tipo(_tipo), pool(_pool), calidad(_calidad),
          modDano(_dano), modLagrimas(_lagrimas), modVelocidad(_velocidad), 
          modRango(_rango), desbloqueado(_desbloqueado) {}

// Getters
    int getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getTipo() const { return tipo; }
    std::string getPool() const { return pool; }
    int getCalidad() const { return calidad; }
    float getModDano() const { return modDano; }
    float getModLagrimas() const { return modLagrimas; }
    float getModVelocidad() const { return modVelocidad; }
    float getModRango() const { return modRango; }
    bool isDesbloqueado() const { return desbloqueado; }

    // Setter para el requerimiento de modificacion de datos
    void setDesbloqueado(bool estado) { 
        desbloqueado = estado; 
    }

    // Sobrecarga del operador < para que Merge Sort y Busqueda Binaria comparen por ID
    bool operator<(const Items& otro) const {
        return this->id < otro.id;
    }

    // Sobrecarga de igualdad para validaciones directas
    bool operator==(const Items& otro) const {
        return this->id == otro.id;
    }

    // Metodo de impresion formateada en consola
    void imprimirFicha() const {
        std::cout << "#" << std::setw(3) << id << " | "
                  << std::setw(16) << std::left << nombre << " | "
                  << "Tipo: " << std::setw(7) << tipo << " | "
                  << "Pool: " << std::setw(8) << pool << " | "
                  << "Q: " << calidad << " | "
                  << "Dmg: " << std::showpos << modDano << " | "
                  << "Tears: " << modLagrimas << " | "
                  << std::noshowpos
                  << "Estado: " << (desbloqueado ? "[Desbloqueado]" : "[Bloqueado]") 
                  << "\n";
    }
};

#endif