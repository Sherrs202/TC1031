#ifndef CALCULOS_ISAAC_H
#define CALCULOS_ISAAC_H

#include <cmath>
#include <algorithm>

class Calculos_Isaac{
    public:
        // Funcion directa: O(1)
        // Calcula el Danio por segundo (DPS) efectivo de Isaac

        static double calcularDPS(float danoBase, float modDano, float lagrimasBase, float modLagrimas){
            double incremento = std::max(0.0f, modDano * 1.2f);
            double danoFinal = danoBase * std::sqrt(incremento + 1.0);

            double cadenciaFinal = std::max(0.2, static_cast<double>(lagrimasBase + modLagrimas));

            return danoFinal * cadenciaFinal;
        }

        // Funcion recursiva O(n)
        // Simula la duplicacion de un recurso tras n usos consecutivos
        static double simularCrookedPenny(double cantidadInicial, int activaciones) {
        // Caso Base: ya no quedan activaciones por procesar
        if (activaciones <= 0) {
            return cantidadInicial;
        }

        // Paso Recursivo: duplica el valor actual y decrementa el contador n
        return simularCrookedPenny(cantidadInicial * 2.0, activaciones - 1);
    }
};

#endif