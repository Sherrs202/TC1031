# TC1031 - Proyecto Integrador: Platinum God Item Tracker

## 1. Análisis de Complejidad (Competencia SICT0301)

### A. Estructura de Datos Principal: std::vector
* **Acceso por índice:** O(1) en tiempo. Permite acceder a cualquier elemento de manera instantánea, propiedad indispensable para calcular el punto medio en la Búsqueda Binaria.
* **Inserción al final (emplace_back):** O(1) amortizado en tiempo. Al redimensionar internamente duplicando su capacidad, el costo prorrateado de inserción permanece constante.
* **Uso de memoria:** O(n) en espacio. Almacena los elementos en un bloque contiguo de memoria RAM, maximizando el aprovechamiento de la memoria caché L1/L2 del procesador gracias al principio de localidad espacial.

### B. Algoritmo de Ordenamiento: MergeSort (Ordenamiento.h)
* **Complejidad Temporal:**
  * **Mejor caso:** O(n log n)
  * **Caso promedio:** O(n log n)
  * **Peor caso:** O(n log n)
  * **Ecuación de Recurrencia:** T(n) = 2T(n/2) + O(n). 
    Por el Teorema Maestro (Caso 2), al dividirse siempre el espacio a la mitad (log_2 n) niveles) y realizar una mezcla lineal de (n) elementos por cada nivel, su cota asintótica es estrictamente Theta(n log n) en cualquier escenario de datos.
* **Complejidad Espacial:** (O(n) de memoria auxiliar requerida por los subvectores temporales `izq` y `der` creados durante la rutina `merge`, más O(log n) en la pila de llamadas del sistema (*call stack*).

### C. Algoritmos de Búsqueda (Catalogo_Isaac.h)
* **Búsqueda Binaria por ID (buscarPorID):**
  * **Complejidad Temporal:**
    * **Mejor caso:** O(1) cuando el elemento buscado se ubica exactamente en la posición central inicial.
    * **Peor y caso promedio:** O(log n) al descartar la mitad del espacio de búsqueda en cada paso (n, n/2, n/4, \dots, 1\).
  * **Complejidad Espacial:** O(1) auxiliar (implementación iterativa basada en apuntadores de índice `inicio` y `fin`).
* **Búsqueda Secuencial por Sala (filtrarPorPool):**
  * **Complejidad Temporal:** O(n) en el peor y caso promedio, ya que debe inspeccionar linealmente cada uno de los (n) registros del catálogo para encontrar múltiples coincidencias.
  * **Complejidad Espacial:** O(1) auxiliar.

### D. Funciones de Cálculo (Calculos_Isaac.h)
* **calcularDPS (Función Directa):** O(1) en tiempo y O(1) en espacio. Ejecuta una secuencia cerrada de operaciones aritméticas elementales sin ciclos ni recursión.
* **simularCrookedPenny (Función Recursiva):** O(k) en tiempo y O(k) en espacio auxiliar en la pila de ejecución, donde (k) representa el número de activaciones consecutivas.

## 2. Justificacion de Decisiones Tecnicas y Algoritmos

### A. Por que MergeSort y no BubbleSort o SelectionSort?
BubbleSort y SelectionSort poseen complejidades cuadráticas de O(n^2) . En un catalógo que contemple la totalidad de los más de 700 ítems de The Binding of Isaac, un algoritmo O(n^2) requeriría cerca de 490,000 comparaciones en el pero caso, mientras que MergeSort requiere aproximadamente 700 X \log_2\(700) = 6,650 operaciones. Se prefirió MergeSort sobre QuickSort debido a que este último pude degradarse a O(n^2) con malos pivotes, mientras que MergeSort garantiza O(n log n) de manera estable.

### B. Por que busqueda binaria para ID y Secuencial para Pool?
* **Por ID:** El identificador númerico es único y el vector puede ordenarse previamente de forma eficiente. Esto habilita la búsqueda Binaria para localizar registros individuales en tiempo (n log n).
* **Por Pool/Sala:** El catálogo no está ordenado alfabéticamente por sala (está ordenado por ID) y una misma sala contiene múltiples ítems dispersos. Por definición, encontrar todas las apariciones de una categoría no ordenada exige una Búsqueda Secuencial exhaustiva de orden O(n).

## Explicación Técnica: Sintaxis
Esta construción corresponde al bucle basado en rango (Ranged-based for loop) estandarizado a partir de C++11. Su desglose sintáctico y semántico es el siguiente:

* **`for (... : inventario):`** El compilador genera automáticamente un recorrido desde `inventario.begin()` hasta `inventario.end()`, eliminanod la necesidad de gestionar índices númericos (`int i = 0`) o iteradores manuales, reduciendo errores comunes de desbordamiento de límites

* `auto`: Indica la deducción automática de tipos en tiempo de compilación. El compilador infirer que el tipo de cada elemento dentro de `inventario` corresponde a la clase `Items`.

* `&`(Paso por Referencia):
  En lugar de crear una copia del objeto `Items` en cada ciclo de la iteracion (lo cual clonaria multiples cadenas `std::string` y valores en memoria consumiendo ciclos de CPU innecesarios, se enlaza a una referencia directa de la direccion de memoria del objeto ya existente en el vector. Esto optimiza el consumo de memoria a O(1) adicional.

* `const` (Genere inmutabilidad):
Aplica el principio de Const-Correctness. Asegura que los elementos del vector sean tratados exclusivamente en modo de solo lectura dentro del cuerpo del bucle. Evita mutaciones accidentales del estado interno del objeto y permite que el metodo que contiene el bucle pueda declararse como metodo constante `const`


