#ifndef CALCULOS_ISAAC_H
#define CALCULOS_ISAAC_H

#include "cmath"

class Calculos_Isaac {
public:
    // Constructor por defecto
    Calculos_Isaac();
    // Funcion directa: O(1) tiempo | O(1) espacio
    // Calcula el Danio por segundo (DPS) proyectado de Isaac
    double calcularDPS(float danoBase, float modDano,
                       float lagrimasBase, float modLagrimas);
    // Funcion recursiva: O(k) tiempo | O(k) espacio en call stack
    // Simula duplicacion de recursos tras k activaciones
    double simularCrookedPenny(double cantidadInicial,
                               int activaciones);
};

// DEFINICIONES FUERA DE LA CLASE

Calculos_Isaac::Calculos_Isaac() {}

double Calculos_Isaac::calcularDPS(float danoBase, float modDano,
                                   float lagrimasBase,
                                   float modLagrimas) {
    double incremento = modDano * 1.2;
    if (incremento < 0.0) {
        incremento = 0.0;
    }

    double danoFinal = danoBase * sqrt(incremento + 1.0);

    double cadencia = lagrimasBase + modLagrimas;
    if (cadencia < 0.2) {
        cadencia = 0.2;
    }

    return danoFinal * cadencia;
}

double Calculos_Isaac::simularCrookedPenny(double cantidadInicial,
    int activaciones) {
    // Caso Base: ya no quedan activaciones pendientes
    if (activaciones <= 0) {
        return cantidadInicial;
    }

    // Paso Recursivo: duplica el valor actual y decrementa el contador
    return simularCrookedPenny(cantidadInicial * 2.0, activaciones - 1);
}

#endif
