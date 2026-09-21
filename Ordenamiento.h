#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <vector>
#include "Items.h"

class Ordenamiento {
private:
    
    // Metodo auxiliar de mezcla: combina dos subarreglos contiguos
    // Primer subarreglo:  arr[inicio ... medio]
    // Segundo subarreglo: arr[medio + 1 ... fin]
    // Complejidad temporal: O(m) donde m es el tamano del bloque a mezclar
    // Complejidad espacial: O(m) por la memoria auxiliar de izq y der
    
    static void merge(std::vector<Items>& arr, int inicio, int medio, int fin) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;

        // Arreglos temporales auxiliares
        std::vector<Items> izq(n1);
        std::vector<Items> der(n2);

        // Copiar los datos a los arreglos temporales
        for (int i = 0; i < n1; ++i) {
            izq[i] = arr[inicio + i];
        }
        for (int j = 0; j < n2; ++j) {
            der[j] = arr[medio + 1 + j];
        }

        // Indices de recorrido
        int i = 0;      // Indice para subarreglo izquierdo
        int j = 0;      // Indice para subarreglo derecho
        int k = inicio; // Indice donde reescribimos en el vector original

        // Comparar y colocar el elemento menor en arr[k]
        // Utiliza directamente el operator< definido en Item.h
        while (i < n1 && j < n2) {
            if (izq[i] < der[j]) {
                arr[k] = izq[i];
                i++;
            } else {
                arr[k] = der[j];
                j++;
            }
            k++;
        }

        // Vaciar los elementos restantes de izq (si quedaron)
        while (i < n1) {
            arr[k] = izq[i];
            i++;
            k++;
        }

        // Vaciar los elementos restantes de der (si quedaron)
        while (j < n2) {
            arr[k] = der[j];
            j++;
            k++;
        }
    }

    
    
    static void mergeSortHelper(std::vector<Items>& arr, int inicio, int fin) {
        if (inicio < fin) {
            // Calculo seguro del punto medio para evitar desbordamiento de enteros
            int medio = inicio + (fin - inicio) / 2;

            // Dividir mitad izquierda y mitad derecha
            mergeSortHelper(arr, inicio, medio);
            mergeSortHelper(arr, medio + 1, fin);

            // Conquistar: mezclar ambas mitades ya ordenadas
            merge(arr, inicio, medio, fin);
        }
    }

public:
    // Interfaz publica para ordenar cualquier vector de Item por ID

    static void mergeSortPorID(std::vector<Items>& arr) {
        if (arr.size() > 1) {
            mergeSortHelper(arr, 0, static_cast<int>(arr.size()) - 1);
        }
    }
};

#endif