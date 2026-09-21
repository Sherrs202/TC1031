#ifndef CATALOGO_ISAAC_H
#define CATALOGO_ISAAC_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Items.h"
#include "Ordenamiento.h"
#include "Calculos_Isaac.h"

class CatalogoIsaac {
private:
    std::vector<Items> inventario;
    bool estaOrdenado;

public:
    // Constructor
    CatalogoIsaac() : estaOrdenado(false) {}

    // Lee linea por linea, separa por comas y puebla el vector
   
    bool cargarDesdeCSV(const std::string& rutaArchivo) {
        inventario.clear();
        std::ifstream archivo(rutaArchivo);

        if (!archivo.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << rutaArchivo << "\n";
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
            std::getline(ss, desbStr, ',');

            if (!idStr.empty()) {
                int id = std::stoi(idStr);
                int cal = std::stoi(calStr);
                float dano = std::stof(danoStr);
                float lag = std::stof(lagStr);
                float vel = std::stof(velStr);
                float ran = std::stof(ranStr);
                bool desb = (std::stoi(desbStr) == 1);

                inventario.emplace_back(id, nombre, tipo, pool, cal, 
                                        dano, lag, vel, ran, desb);
            }
        }

        archivo.close();
        estaOrdenado = false; // Al cargar datos nuevos se reinicia la bandera
        return true;
    }

    // Reescribe el archivo en disco reflejando los cambios hechos
    bool guardarEnCSV(const std::string& rutaArchivo) const {
        std::ofstream archivo(rutaArchivo);

        if (!archivo.is_open()) {
            std::cerr << "Error: No se pudo guardar en " << rutaArchivo << "\n";
            return false;
        }

        archivo << "id,nombre,tipo,pool,calidad,mod_dano,mod_lagrimas,mod_velocidad,mod_rango,desbloqueado\n";
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

    // Invoca el algoritmo aislado en Ordenamiento.h
    void ordenarPorID() {
        Ordenamiento::mergeSortPorID(inventario);
        estaOrdenado = true;
    }

    // Busca un item por su identificador numerico unico
    // Retorna el indice dentro del vector, o -1 si no existe
    int buscarPorID(int idBuscado) {
        // Garantizar la precondicion de orden antes de buscar
        if (!estaOrdenado) {
            ordenarPorID();
        }

        int inicio = 0;
        int fin = static_cast<int>(inventario.size()) - 1;

        while (inicio <= fin) {
            int medio = inicio + (fin - inicio) / 2;

            if (inventario[medio].getId() == idBuscado) {
                return medio; // Elemento encontrado
            }
            if (inventario[medio].getId() < idBuscado) {
                inicio = medio + 1; // Descartar mitad izquierda
            } else {
                fin = medio - 1;    // Descartar mitad derecha
            }
        }

        return -1; // No encontrado
    }

    // Filtra y despliega todos los items asociados a una sala (pool)
   
    int filtrarPorPool(const std::string& poolBuscada) const {
        int coincidencias = 0;
        std::cout << "\n--- Items encontrados en la sala [" << poolBuscada << "] ---\n";
        
        for (const auto& item : inventario) {
            if (item.getPool() == poolBuscada) {
                item.imprimirFicha();
                coincidencias++;
            }
        }

        if (coincidencias == 0) {
            std::cout << "No se encontraron items registrados en la pool '" << poolBuscada << "'.\n";
        }
        return coincidencias;
    }

    // Alterna el estado de desbloqueo de un item
    bool modificarEstadoDesbloqueo(int id, bool nuevoEstado) {
        int idx = buscarPorID(id);
        if (idx != -1) {
            inventario[idx].setDesbloqueado(nuevoEstado);
            return true;
        }
        return false;
    }

    // Metodo de despliegue general
    void mostrarCatalogo() const {
        std::cout << "\n============================== CATALOGO PLATINUM GOD ==============================\n";
        for (const auto& item : inventario) {
            item.imprimirFicha();
        }
        std::cout << "===================================================================================\n";
    }

    // Acceso al vector interno para pruebas unitarias
    std::vector<Items>& getInventario() { 
        return inventario; 
    }

    size_t getCantidadItems() const { 
        return inventario.size(); 
    }
};

#endif