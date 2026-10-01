# TC1031 - Proyecto Integrador: Platinum God Item Tracker

## 1. Análisis de Complejidad (Competencia SICT0301)

### A. Estructura de Datos Principal: std::vector
* **Acceso por índice:** \(O(1)\) en tiempo. Permite acceder a cualquier elemento de manera instantánea, propiedad indispensable para calcular el punto medio en la Búsqueda Binaria.
* **Inserción al final (emplace_back):** \(O(1)\) amortizado en tiempo. Al redimensionar internamente duplicando su capacidad, el costo prorrateado de inserción permanece constante.
* **Uso de memoria:** \(O(n)\) en espacio. Almacena los elementos en un bloque contiguo de memoria RAM, maximizando el aprovechamiento de la memoria caché L1/L2 del procesador gracias al principio de localidad espacial.

### B. Algoritmo de Ordenamiento: MergeSort (Ordenamiento.h)
* **Complejidad Temporal:**
  * **Mejor caso:** \(O(n \log n)\)
  * **Caso promedio:** \(O(n \log n)\)
  * **Peor caso:** \(O(n \log n)\)
  * **Ecuación de Recurrencia:** \(T(n) = 2T(n/2) + O(n)\). 
    Por el Teorema Maestro (Caso 2), al dividirse siempre el espacio a la mitad (\(\log_2 n\) niveles) y realizar una mezcla lineal de \(n\) elementos por cada nivel, su cota asintótica es estrictamente \(\Theta(n \log n)\) en cualquier escenario de datos.
* **Complejidad Espacial:** \(O(n)\) de memoria auxiliar requerida por los subvectores temporales `izq` y `der` creados durante la rutina `merge`, más \(O(\log n)\) en la pila de llamadas del sistema (*call stack*).

### C. Algoritmos de Búsqueda (Catalogo_Isaac.h)
* **Búsqueda Binaria por ID (buscarPorID):**
  * **Complejidad Temporal:**
    * **Mejor caso:** \(O(1)\) cuando el elemento buscado se ubica exactamente en la posición central inicial.
    * **Peor y caso promedio:** \(O(\log n)\) al descartar la mitad del espacio de búsqueda en cada paso (\(n, n/2, n/4, \dots, 1\)).
  * **Complejidad Espacial:** \(O(1)\) auxiliar (implementación iterativa basada en apuntadores de índice `inicio` y `fin`).
* **Búsqueda Secuencial por Sala (filtrarPorPool):**
  * **Complejidad Temporal:** \(O(n)\) en el peor y caso promedio, ya que debe inspeccionar linealmente cada uno de los \(n\) registros del catálogo para encontrar múltiples coincidencias.
  * **Complejidad Espacial:** \(O(1)\) auxiliar.

### D. Funciones de Cálculo (Calculos_Isaac.h)
* **calcularDPS (Función Directa):** \(O(1)\) en tiempo y \(O(1)\) en espacio. Ejecuta una secuencia cerrada de operaciones aritméticas elementales sin ciclos ni recursión.
* **simularCrookedPenny (Función Recursiva):** \(O(k)\) en tiempo y \(O(k)\) en espacio auxiliar en la pila de ejecución, donde \(k\) representa el número de activaciones consecutivas.

## 2. Justificacion de Decisiones Tecnicas y Algoritmos

