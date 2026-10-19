#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <vector>
#include "Items.h"

class Ordenamiento {
private:
    // Metodo auxiliar de mezcla: combina dos subarreglos contiguos
    // Complejidad temporal: O(m) donde m es el tamano del bloque a mezclar
    // Complejidad espacial: O(m) por la memoria auxiliar de izq y der
    void merge(std::vector<Items>& arr, int inicio,
               int medio, int fin);

    // Metodo recursivo divide y venceras
    // Complejidad temporal: O(n log n)
    // Complejidad espacial: O(log n) por la memoria en la pila de ejecucion
    void mergeSortHelper(std::vector<Items>& arr,
                         int inicio, int fin);

public:
    // Constructor por defecto
    Ordenamiento();

    // Interfaz publica para ordenar un vector de Items por ID
    // Complejidad temporal: O(n log n) en mejor, peor y promedio
    // Complejidad espacial: O(n) por memoria auxiliar de merge
    void mergeSortPorID(std::vector<Items>& arr);
};

// ============================================================================
// DEFINICIONES FUERA DE LA CLASE
// ============================================================================

Ordenamiento::Ordenamiento() {}

void Ordenamiento::merge(std::vector<Items>& arr, int inicio,
                         int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    std::vector<Items> izq(n1);
    std::vector<Items> der(n2);

    for (int i = 0; i < n1; i++) {
        izq[i] = arr[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        der[j] = arr[medio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = inicio;

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

    while (i < n1) {
        arr[k] = izq[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = der[j];
        j++;
        k++;
    }
}

void Ordenamiento::mergeSortHelper(std::vector<Items>& arr,
                                   int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;

        mergeSortHelper(arr, inicio, medio);
        mergeSortHelper(arr, medio + 1, fin);

        merge(arr, inicio, medio, fin);
    }
}

void Ordenamiento::mergeSortPorID(std::vector<Items>& arr) {
    if (arr.size() > 1) {
        int ultimoIndice = arr.size() - 1;
        mergeSortHelper(arr, 0, ultimoIndice);
    }
}

#endif
