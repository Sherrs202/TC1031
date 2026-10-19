# Platinum God - Gestor de Items de The Binding of Isaac

**Proyecto Integrador TC1031 - Programación de Estructuras de Datos y Algoritmos**

**Lenguaje:** C++  
**Autor:** Gerardo Silva

---

## 1. Descripción del proyecto

Platinum God es un programa desarrollado en C++ e inspirado en el videojuego
*The Binding of Isaac: Repentance*.

El objetivo principal del proyecto es crear un gestor de items que permita
consultar y modificar información del juego, aplicando diferentes estructuras
de datos y algoritmos aprendidos durante la materia TC1031.

El programa utiliza un catálogo almacenado en un archivo CSV, donde se
registran los items con sus respectivos atributos, como nombre, ID,
calidad, tipo, pool y modificadores de estadísticas.

Además, cuenta con funcionalidades para administrar favoritos, registrar
un historial de cambios y realizar búsquedas mediante diferentes algoritmos.

También se implementó un Binary Search Tree (BST), que permite organizar
los IDs de los items y consultar su nivel y sus antecesores.

El proyecto funciona mediante un menú interactivo en consola y utiliza
únicamente la biblioteca estándar de C++.

---

## 2. Funcionalidades del programa

Las principales funcionalidades de Platinum God son:

- Mostrar todos los items registrados en el catálogo.
- Ordenar los items mediante Merge Sort.
- Buscar items utilizando Binary Search.
- Filtrar items por su sala o pool.
- Modificar el estado de desbloqueo de los items.
- Editar atributos como nombre, calidad, daño, lágrimas, velocidad y rango.
- Calcular el DPS estimado de Isaac.
- Simular duplicaciones utilizando recursividad.
- Agregar, modificar y eliminar items favoritos.
- Consultar el historial de cambios realizados.
- Recorrer el historial en orden normal e inverso.
- Consultar información de los items mediante un BST.
- Guardar las modificaciones del catálogo en un archivo CSV.

Estas funcionalidades permiten utilizar las estructuras de datos
en diferentes partes del programa sin necesidad de crear un menú
independiente para cada una.

---

## 3. Estructuras de datos utilizadas

Para desarrollar este proyecto se utilizaron diferentes estructuras
de datos, cada una con una función específica.

### 3.1 Vector dinámico

**Archivo:** `Catalogo_Isaac.h`

La estructura principal del catálogo utiliza un `vector<Items>`,
en el cual se almacenan los objetos que representan los items del juego.

Cada item contiene:

- ID
- Nombre
- Tipo
- Pool
- Calidad
- Modificador de daño
- Modificador de lágrimas
- Modificador de velocidad
- Modificador de rango
- Estado de desbloqueo

Se eligió un vector porque permite acceder directamente a sus elementos
mediante índices y facilita la implementación de algoritmos de búsqueda
y ordenamiento.

**Complejidades:**

| Operación | Complejidad |
|---|---|
| Acceso por índice | O(1) |
| Recorrer el catálogo | O(n) |
| Filtrar por pool | O(n) |
| Búsqueda binaria en datos ordenados | O(log n) |

### 3.2 Singly Linked List

**Archivo:** `Catalogo_Isaac.h`

La lista simplemente ligada se utiliza para administrar los items
favoritos del usuario.

Cada nodo almacena el nombre de un item y un apuntador llamado
`siguiente`, que conecta con el siguiente elemento de la lista.

Esta estructura permite agregar, buscar, modificar y eliminar favoritos
utilizando memoria dinámica.

**Métodos implementados:**

- `addFirst()`: agrega un favorito al inicio.
- `add()`: agrega un nuevo favorito.
- `contains()`: verifica si existe un favorito.
- `set()`: modifica un elemento.
- `remove()`: elimina un favorito.
- `clear()`: libera los nodos.
- `toStringFavoritos()`: muestra los favoritos.

**Complejidades:**

| Operación | Complejidad |
|---|---|
| Insertar al inicio | O(1) |
| Buscar un elemento | O(n) |
| Modificar un elemento | O(n) |
| Eliminar un elemento | O(n) |
| Recorrer la lista | O(n) |

Esta estructura se eligió para practicar el manejo de apuntadores
y las operaciones sobre listas enlazadas.

### 3.3 Doubly Linked List

**Archivo:** `Catalogo_Isaac.h`

La lista doblemente ligada se utiliza para almacenar el historial
de cambios realizados durante la ejecución del programa.

A diferencia de la lista simplemente ligada, cada nodo contiene
dos apuntadores:

- `siguiente`: apunta al siguiente registro.
- `anterior`: apunta al registro anterior.

Esta estructura permite consultar el historial desde el cambio
más antiguo hasta el más reciente y también en sentido contrario.

**Métodos implementados:**

- `addHistorial()`
- `containsHistorial()`
- `setHistorial()`
- `removeHistorial()`
- `clearHistorial()`
- `toStringHistorial()`
- `toStringHistorialReversa()`

**Complejidades:**

| Operación | Complejidad |
|---|---|
| Insertar al final | O(1) |
| Buscar un registro | O(n) |
| Modificar un registro | O(n) |
| Eliminar un registro | O(n) |
| Recorrer en ambos sentidos | O(n) |

Esta estructura resulta útil para registrar las modificaciones
realizadas en los items y en la lista de favoritos.

### 3.4 Binary Search Tree (BST)

**Archivo:** `ArbolBST.h`

Se implementó un árbol binario de búsqueda para organizar los IDs
de los items.

Cada nodo contiene:

- Un ID.
- Un apuntador `izquierda`.
- Un apuntador `derecha`.

El árbol sigue las siguientes reglas:

1. Los valores menores se colocan a la izquierda.
2. Los valores mayores se colocan a la derecha.
3. Los IDs repetidos no se insertan nuevamente.

Cuando se carga el catálogo, se construye automáticamente el BST
utilizando los IDs de los items.

Para obtener una distribución equilibrada inicialmente, se utiliza
el vector ordenado y se insertan primero los elementos centrales
de cada intervalo.

**Métodos implementados:**

| Método | Función | Complejidad |
|---|---|---|
| `insertar()` | Inserta un ID | O(h) |
| `visit()` | Recorrido inorden | O(n) |
| `height()` | Calcula la altura | O(n) |
| `ancestors()` | Muestra los antecesores | O(h) |
| `currentLevel()` | Obtiene el nivel | O(h) |
| Destructor | Libera memoria | O(n) |

Donde:

- `n` representa la cantidad de nodos.
- `h` representa la altura del árbol.

En un BST equilibrado, la búsqueda puede realizarse en O(log n).

En un BST desbalanceado, puede llegar a O(n).

Para este proyecto, la raíz se considera nivel 0.

Al buscar un item por ID, el programa muestra automáticamente
su nivel y sus antecesores dentro del BST.

---

## 4. Algoritmos implementados

### 4.1 Merge Sort

**Archivo:** `Ordenamiento.h`

Se utiliza Merge Sort para ordenar los items del catálogo
de menor a mayor según su ID.

Este algoritmo se basa en la técnica Divide and Conquer.

Su funcionamiento consiste en:

1. Dividir el vector en dos mitades.
2. Ordenar cada mitad de manera recursiva.
3. Combinar las mitades ordenadas.
4. Repetir el procedimiento hasta ordenar todos los elementos.

**Complejidad temporal:**

- Mejor caso: O(n log n).
- Caso promedio: O(n log n).
- Peor caso: O(n log n).

**Complejidad espacial auxiliar:** O(n).

Se eligió porque permite ordenar una cantidad considerable
de items de manera eficiente.

### 4.2 Binary Search

**Archivo:** `Catalogo_Isaac.h`

La búsqueda binaria permite encontrar un item mediante su ID.

Para utilizar este algoritmo, el vector debe estar ordenado.

El procedimiento consiste en:

1. Comparar el ID buscado con el elemento central.
2. Si coinciden, devolver su posición.
3. Si el ID es menor, continuar en la mitad izquierda.
4. Si el ID es mayor, continuar en la mitad derecha.
5. Repetir hasta encontrar el elemento o terminar la búsqueda.

**Complejidad temporal:** O(log n), sobre datos ordenados.

**Complejidad espacial auxiliar:** O(1).

### 4.3 Sequential Search

**Archivo:** `Catalogo_Isaac.h`

La búsqueda secuencial se utiliza para filtrar items
según su pool o sala.

El algoritmo recorre el catálogo y compara la categoría
de cada item con la ingresada por el usuario.

Si encuentra coincidencias, muestra los resultados.

**Complejidad temporal:** O(n).

**Complejidad espacial auxiliar:** O(1).

### 4.4 Recursividad

**Archivo:** `Calculos_Isaac.h`

Se implementó una función recursiva inspirada en el item
Crooked Penny.

El usuario ingresa una cantidad inicial y el número
de duplicaciones que desea simular.

La función se llama a sí misma hasta alcanzar el caso base
y devuelve el resultado de las duplicaciones.

Este apartado permite demostrar el uso de funciones recursivas
dentro de un programa.

### 4.5 Cálculo directo de DPS

**Archivo:** `Calculos_Isaac.h`

El programa incluye una calculadora que permite estimar
el daño por segundo utilizando los valores ingresados.

Se consideran:

- Daño base.
- Modificador de daño.
- Lágrimas base.
- Modificador de lágrimas.

**Complejidad temporal:** O(1).

---

## 5. Manejo de archivos CSV

El programa utiliza un archivo llamado `items_isaac.csv`
para almacenar la información del catálogo.

Para trabajar con el archivo se utilizan:

- `ifstream`: lectura de datos.
- `ofstream`: escritura de datos.
- `stringstream`: separación de los campos del CSV.

Las columnas del archivo son:

```csv
id,nombre,tipo,pool,calidad,mod_dano,mod_lagrimas,mod_velocidad,mod_rango,desbloqueado
```

El catálogo de prueba contiene aproximadamente la mitad
de los items coleccionables de The Binding of Isaac: Repentance,
con 360 registros colocados en un orden aleatorio.

Esto permite comprobar el funcionamiento de los algoritmos
de ordenamiento y búsqueda.

Algunos atributos del CSV contienen valores provisionales
cuando no se dispone de información verificada del juego.

Cuando el usuario modifica un item, el cambio se realiza
en memoria y puede guardarse posteriormente en el CSV.

Los favoritos y el historial permanecen en memoria
durante la ejecución del programa.

---

## 6. Organización de archivos

La estructura actual del proyecto es:

```text
Platinum-God/
|
|-- main.cpp
|
|-- Items.h
|
|-- Catalogo_Isaac.h
|
|-- Ordenamiento.h
|
|-- Calculos_Isaac.h
|
|-- ArbolBST.h
|
|-- items_isaac.csv
|
|-- README.md
```

**Descripción de los archivos:**

| Archivo | Descripción |
|---|---|
| `main.cpp` | Contiene el menú principal y controla el programa |
| `Items.h` | Define la clase Items y sus atributos |
| `Catalogo_Isaac.h` | Administra el catálogo, favoritos e historial |
| `Ordenamiento.h` | Implementa Merge Sort |
| `Calculos_Isaac.h` | Contiene los cálculos y la función recursiva |
| `ArbolBST.h` | Implementa el Binary Search Tree |
| `items_isaac.csv` | Almacena los registros del catálogo |
| `README.md` | Documentación del proyecto |

---

## 7. Compilación y ejecución

### Requisitos

Para ejecutar el proyecto se necesita:

- Un compilador de C++.
- Visual Studio Code o cualquier editor compatible.
- Una terminal.
- El archivo `items_isaac.csv`.

### Compilar el programa

Desde la terminal, ubicarse en la carpeta del proyecto.

Ejecutar:

```bash
g++ -std=c++11 main.cpp -o platinum_god
```

### Ejecutar en Windows

```powershell
.\platinum_god.exe
```

### Ejecutar en Linux

```bash
./platinum_god
```

Es importante ejecutar el programa desde la carpeta
que contiene `items_isaac.csv`.

---

## 8. Ejemplo de funcionamiento

Al iniciar el programa, se cargan los datos del catálogo
y se construye automáticamente el BST.

El usuario puede seleccionar cualquiera de las opciones
disponibles.

Por ejemplo, al buscar un item por ID:

```text
Selecciona una opcion: 3

Ingresa el ID del item: 118

--- ITEM ENCONTRADO ---

ID: 118
Nombre: Brimstone

--- INFORMACION DEL BST ---

Nivel del item: [nivel calculado]

Antecesores: [IDs calculados]
```

El nivel y los antecesores dependen de cómo se haya
construido el árbol con los IDs del catálogo.

El usuario puede continuar realizando operaciones
hasta seleccionar la opción de guardar y salir.

---

## 9. Pruebas del programa

Para comprobar el funcionamiento del proyecto
se consideran los siguientes casos:

| Prueba | Resultado esperado |
|---|---|
| Cargar archivo CSV | Los items se cargan correctamente |
| Ordenar por ID | Los items aparecen de menor a mayor |
| Buscar un ID existente | Se muestra la información del item |
| Buscar un ID inexistente | Se informa que no existe |
| Filtrar por pool | Se muestran los items correspondientes |
| Agregar favoritos | Los elementos aparecen en la lista |
| Eliminar favoritos | Los elementos se eliminan correctamente |
| Consultar historial | Se muestran los cambios realizados |
| Historial inverso | Se muestran los cambios en orden inverso |
| Modificar un item | Los atributos se actualizan |
| Guardar en CSV | Se conservan los cambios del catálogo |
| BST inorden | Los IDs aparecen en orden ascendente |
| BST height | Se obtiene la altura del árbol |
| BST ancestors | Se muestran los antecesores |
| BST currentLevel | Se obtiene el nivel del nodo |

---

## 10. Mejoras futuras

Aunque el programa ya cuenta con diferentes estructuras
de datos y algoritmos, todavía existen algunas
funcionalidades que pueden agregarse.

Entre las mejoras consideradas se encuentran:

- Implementar un árbol AVL.
- Agregar las rotaciones necesarias para balancear el AVL.
- Comparar las alturas del BST y del AVL.
- Completar los atributos provisionales de los items.
- Guardar los favoritos y el historial entre ejecuciones.
- Mejorar la presentación de los resultados en consola.

---

## 11. Referencias

Las siguientes fuentes se utilizaron como apoyo para los conceptos
de estructuras de datos, algoritmos y manejo de archivos en C++,
así como para la temática del proyecto.

1. cppreference.com. (s. f.). *std::vector*.  
   https://cppreference.com/cpp/container/vector

2. cppreference.com. (s. f.). *Standard library header <fstream>*.  
   https://cppreference.com/cpp/header/fstream

3. VisuAlgo. (s. f.). *Linked List (Single, Doubly), Stack, Queue, Deque*.  
   https://visualgo.net/en/list

4. VisuAlgo. (s. f.). *Binary Search Tree, AVL Tree*.  
   https://visualgo.net/en/bst

5. Sedgewick, R., & Wayne, K. (s. f.). *2.2 Mergesort*.  
   Algorithms, 4th Edition. Princeton University.  
   https://algs4.cs.princeton.edu/22mergesort/index.php

6. The Binding of Isaac Wiki. (s. f.). *Objetos*.  
   https://bindingofisaac.fandom.com/es/wiki/Objetos

---

## 12. Créditos

Este proyecto fue desarrollado con fines académicos
para la materia TC1031.

The Binding of Isaac: Repentance es propiedad de sus
respectivos creadores y se utiliza únicamente
como inspiración temática.

Platinum God es un proyecto no oficial y no está
afiliado a los desarrolladores del videojuego.
