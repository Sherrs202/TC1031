#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "Catalogo_Isaac.h"
#include "Calculos_Isaac.h"
#include "Items.h"
#include "ArbolBST.h"

// Funcion auxiliar para limpiar el buffer de entrada en caso de error
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void cargarBST(ArbolBST& arbol, const std::vector<Items>& items,
               int inicio, int fin) {

    if (inicio > fin) {
        return;
    }

    int medio = inicio + (fin - inicio) / 2;

    arbol.insertar(items[medio].getId());

    cargarBST(arbol, items, inicio, medio - 1);
    cargarBST(arbol, items, medio + 1, fin);
}

int main() {
    CatalogoIsaac catalogo;
    Calculos_Isaac calculos;
    ArbolBST arbol;
    const std::string rutaArchivo = "items_isaac.csv";

    // 1. Carga iterativa inicial de los datos
    if (!catalogo.cargarDesdeCSV(rutaArchivo)) {
        std::cerr << "Asegurate de que el archivo '" << rutaArchivo
                  << "' se encuentre en la misma carpeta.\n";
        return 1;
    }

    catalogo.ordenarPorID();
    int totalItems = catalogo.getCantidadItems();
    if (totalItems > 0) {
        cargarBST(arbol, catalogo.getInventario(), 0, totalItems - 1);
    }

    std::cout << "\n--- BST CARGADO CORRECTAMENTE ---\n";
    std::cout << "Items registrados: " << totalItems << "\n";
    std::cout << "Altura del BST: " << arbol.height() << "\n";

    int opcion = 0;

    do {
        std::cout << "\n===================================================\n";
        std::cout << "        PLATINUM GOD - GESTOR DE ITEMS (TC1031)     \n";
        std::cout << "===================================================\n";
        std::cout << "1. Mostrar todos los items del catalogo\n";
        std::cout << "2. Ordenar items por ID (Merge Sort)\n";
        std::cout << "3. Buscar item por ID (Busqueda Binaria)\n";
        std::cout << "4. Filtrar items por Sala / Pool (Busqueda Secuencial)\n";
        std::cout << "5. Modificar estado de desbloqueo de un item\n";
        std::cout << "6. Calcular DPS estimado de Isaac (Funcion Directa)\n";
        std::cout << "7. Simular duplicacion Crooked Penny (Recursiva)\n";
        std::cout << "8. Favoritos\n";
        std::cout << "9. Historial de cambios\n";
        std::cout << "10. Modificar item del catalogo\n";
        std::cout << "11. Guardar cambios en CSV y Salir\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "Selecciona una opcion (1-11): ";

        if (!(std::cin >> opcion)) {
            std::cout << "Entrada invalida. Por favor, ingresa un numero.\n";
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
            case 1: {
                catalogo.mostrarCatalogo();
                break;
            }

            case 2: {
                catalogo.ordenarPorID();
                std::cout << "\n[OK] Catalogo ordenado exitosamente por ID "
                          << "usando Merge Sort O(n log n).\n";
                catalogo.mostrarCatalogo();
                break;
            }

            case 3: {
                int idBuscado;
                std::cout << "\nIngresa el ID del item a buscar: ";
                if (!(std::cin >> idBuscado)) {
                    std::cout << "ID no valido.\n";
                    limpiarBuffer();
                    break;
                }

                int indice = catalogo.buscarPorID(idBuscado);
                if (indice != -1) {
                    std::cout << "\n--- ITEM ENCONTRADO (Posicion: "
                              << indice << ") ---\n";
                    catalogo.getInventario()[indice].imprimirFicha();
                    std::cout << "\n --- INFORMACION DEL BST --- \n";
                    std::cout << "Nivel de item: "
                              << arbol.currentLevel(idBuscado) << "\n";
                    arbol.ancestors(idBuscado);
                } else {
                    std::cout << "\n[!] No se encontro ningun item con ID #"
                              << idBuscado << ".\n";
                }
                break;
            }

            case 4: {
                std::string pool;
                std::cout << "\nIngresa sala (Treasure, Devil, Angel, "
                          << "Shop, Secret, Boss): ";
                std::cin >> pool;
                catalogo.filtrarPorPool(pool);
                break;
            }

            case 5: {
                int idModificar;
                int nuevoEstado;
                std::cout << "\nIngresa el ID del item a cambiar: ";
                if (!(std::cin >> idModificar)) {
                    std::cout << "ID invalido.\n";
                    limpiarBuffer();
                    break;
                }

                std::cout << "Nuevo estado (1 = Desbloqueado, 0 = Bloqueado): ";
                if (!(std::cin >> nuevoEstado) ||
                    (nuevoEstado != 0 && nuevoEstado != 1)) {
                    std::cout << "Opcion de estado no valida (solo 1 o 0).\n";
                    limpiarBuffer();
                    break;
                }

                if (catalogo.modificarEstadoDesbloqueo(idModificar,
                                                       nuevoEstado == 1)) {
                    std::cout << "\n[OK] Registro modificado en memoria.\n";
                    std::cout << "Usa la opcion 8 para guardar en disco.\n";
                } else {
                    std::cout << "\n[!] No se encontro el item con ID #"
                              << idModificar << ".\n";
                }
                break;
            }

            case 6: {
                float danoBase, modDano, lagrimasBase, modLagrimas;
                std::cout << "\n--- CALCULADORA DE DPS (Tiempo O(1)) ---\n";
                std::cout << "Ingresa el dano base de Isaac (ej. 3.5): ";
                std::cin >> danoBase;
                std::cout << "Ingresa el bono de dano del item (+/-): ";
                std::cin >> modDano;
                std::cout << "Ingresa las lagrimas base (ej. 1.0): ";
                std::cin >> lagrimasBase;
                std::cout << "Ingresa el bono de lagrimas del item (+/-): ";
                std::cin >> modLagrimas;

                double dps = calculos.calcularDPS(danoBase, modDano,
                                                  lagrimasBase,
                                                  modLagrimas);
                std::cout << "\n>> DPS Final proyectado: " << dps
                          << " puntos de dano por segundo.\n";
                break;
            }

            case 7: {
                double cantidadInicial;
                int activaciones;
                std::cout << "\n--- SIMULADOR CROOKED PENNY (Recursiva) ---\n";
                std::cout << "Ingresa la cantidad base del recurso: ";
                std::cin >> cantidadInicial;
                std::cout << "Ingresa numero de duplicaciones sucesivas (k): ";
                std::cin >> activaciones;

                if (activaciones < 0) {
                    std::cout << "El numero no puede ser negativo.\n";
                } else {
                    double res = calculos.simularCrookedPenny(
                        cantidadInicial, activaciones);
                    std::cout << "\n>> Tras " << activaciones
                              << " duplicaciones sucesivas: "
                              << res << " unidades generadas.\n";
                }
                break;
            }

            case 8: {
                int opcionFav;

                do {
                    std::cout << "\n--- MIS ITEMS FAVORITOS ---\n";
                    std::cout << "1. Mostrar favoritos\n";
                    std::cout << "2. Agregar favorito al inicio\n";
                    std::cout << "3. Agregar favorito al final\n";
                    std::cout << "4. Buscar favoritos\n";
                    std::cout << "5. Modificar favorito\n";
                    std::cout << "6. Eliminar favorito\n";
                    std::cout << "0. Regresar al menu principal\n";
                    std::cout << "Selecciona una opcion: ";
                    
                    if (!(std::cin >> opcionFav)){
                        std::cout << "Opcion invalida\n";
                        limpiarBuffer();
                        continue;
                    }

                    switch (opcionFav){
                        case 1:
                            std::cout << catalogo.toStringFavoritos() << "\n";
                            break;

                        case 2: {
                            std::string entrada;
                            std::string nombre;
                            bool encontrado = false;

                            std::cout << "Ingresa el ID o nombre del item: ";\
                            std::getline(std::cin >> std::ws, entrada);

                            std::stringstream ss(entrada);
                            int id;

                            if((ss >> id) && (ss >> std::ws).eof()){
                                int indice = catalogo.buscarPorID(id);

                                if (indice != -1){
                                    nombre = catalogo.getInventario()
                                    [indice].getNombre();
                                    encontrado = true;
                                }
                            } else {
                                for (const auto& item : catalogo.getInventario()){
                                    if (item.getNombre() == entrada){
                                        nombre = item.getNombre();
                                        encontrado = true;
                                        break;
                                    }
                                }
                            }

                            if (encontrado) {
                                if (!catalogo.contains(nombre)) {
                                    catalogo.addFirst(nombre);
                                    catalogo.addHistorial
                                    ("Agregado al inicio de favoritos: " + nombre);
                                    std::cout << "Item agregado" << nombre << "\n";
                                } else {
                                    std::cout << "Este item ya esta en favoritos.\n";
                                }
                            } else {
                                std::cout << "No se encuentro el item en el catalogo.\n";
                            }

                            break;
                        }

                        case 3: {
                            std::string entrada;
                            std::string nombre;
                            bool encontrado = false;

                            std::cout << "Ingresa el ID o nombre del item: ";
                            std::getline(std::cin >> std::ws, entrada);

                            std::stringstream ss(entrada);
                            int id;

                            if ((ss >> id) && (ss >> std::ws).eof()) {
                                int indice = catalogo.buscarPorID(id);

                                if (indice != -1) {
                                    nombre = catalogo.getInventario()
                                    [indice].getNombre();
                                    encontrado = true;
                                }
                            } else {
                                for (const auto& item : 
                                    catalogo.getInventario()) {
                                    if (item.getNombre() == entrada) {
                                        nombre = item.getNombre();
                                        encontrado = true;
                                        break;
                                    }
                                }
                            }

                            if (encontrado) {
                                if (!catalogo.contains(nombre)){
                                    catalogo.add(nombre);
                                    catalogo.addHistorial
                                    ("Agregado al final de favoritos: " + nombre);
                                    std::cout << "Item agregado al final: "
                                              << nombre << "\n";
                                } else {
                                    std::cout << 
                                    "Este item ya esta en favoritos.\n";
                                }
                            } else {
                                std::cout << 
                                "No se encontro el item en el catalogo.\n";
                            }

                            break;
                        }

                        case 4: {
                            std::string entrada;
                            std::string nombre;
                            bool encontrado = false;

                            std::cout << "Ingresa el ID o nombre del item: ";
                            std::getline(std::cin >> std::ws, entrada);

                            std::stringstream ss(entrada);
                            int id;

                            if ((ss >> id) && (ss >> std::ws).eof()) {
                                int indice = catalogo.buscarPorID(id);

                                if (indice != -1) {
                                    nombre = catalogo.getInventario()
                                    [indice].getNombre();
                                    encontrado = true;
                                }
                            } else {
                                for (const auto& item :catalogo.getInventario()){
                                    if (item.getNombre() == entrada) {
                                        nombre = item.getNombre();
                                        encontrado = true;
                                        break;
                                    }
                                }
                            }

                            if (encontrado) {
                                if (catalogo.contains(nombre)) {
                                    std::cout << "[OK] " << nombre
                                              << "esta en tus favoritos.\n";
                                } else {
                                    std::cout << "[!] " << nombre
                                              << " no esta en tus favoritos.\n";
                                }
                            } else {
                                std::cout << "No se encontro el item en el catalogo";
                            }

                            break;
                        }

                        case 5: {
                            int posicion;
                            std::string entrada;
                            std::string nombre;
                            bool encontrado = false;

                            std::cout << "\nFavoritos actuales: "
                                      << catalogo.toStringFavoritos() << "\n";

                                      std::cout << 
                                      "Ingresar la posicion del favorito a modificar: ";

                                      if (!(std::cin >> posicion)) {
                                        std::cout << "Posicion invalida.\n";
                                        limpiarBuffer();
                                        break;
                                      }

                                      std::cout << 
                                      "Ingresar el ID o nombre del nuevo item: ";
                                        std::stringstream ss(entrada);
                                        int id;

                                      if ((ss >> id) && (ss >> std::ws).eof()) {
                                        int indice = catalogo.buscarPorID(id);

                                        if (indice != -1) {
                                            nombre = catalogo.getInventario()
                                            [indice].getNombre();
                                            encontrado = true;

                                        }
                                      } else {
                                            for (const auto& item : catalogo.getInventario()) {
                                                if (item.getNombre() == entrada) {
                                                    nombre = item.getNombre();
                                                    encontrado = true;
                                                    break;
                                                }
                                            }
                                      }

                                      if (encontrado) {
                                        if (catalogo.contains(nombre)) {
                                            std::cout << 
                                            "Este item ya esta en favoritos.\n";
                                        } else if (catalogo.set(posicion, nombre)) {
                                            std::cout << 
                                            "Favorito modificado correctamente.\n";
                                        } else {
                                            std::cout << "La posicion no existe.\n";
                                        }
                                      } else {
                                        std::cout << 
                                        "No se encontro el item en el catalogo.\n";

                                      }

                                      break;
                        }

                        case 6: {
                            int posicion;

                            std::cout << "\nFavoritos actuales: "
                                      << catalogo.toStringFavoritos() << "\n";
                            
                            std::cout << "Ingresa la posicion del favorito a eliminar: ";

                            if (!(std::cin >> posicion)){
                                std::cout << "Posicion invalida.\n";
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits
                                    <std::streamsize>::max(), '\n');
                                break;
                            }

                            if (catalogo.remove(posicion)) {
                                std::cout << "Favorito eliminado correctamente.\n";
                            } else {
                                std::cout << "La posicion no existe.\n";
                            }

                            break;
                        }

                        case 0:
                            std::cout << "Regresando al menu principal...\n";
                            break;

                        default:
                            std::cout << "Opcion no valida.\n";
                            break;
                    }
                } while (opcionFav != 0);

                break;
            }

            case 9: {
                int opcionHistorial;

                do {
                    std::cout << "\n---- HISTORIAL DE CAMBIOS ----\n";
                    std::cout << "1. Mostrar historial completo\n";
                    std::cout << "2. Mostrar historial en orden inverso\n";
                    std::cout << "3. Buscar un registro\n";
                    std::cout << "4. Modificar un registro\n";
                    std::cout << "5. Eliminar un registro\n";
                    std::cout << "0. Regresar al menu principal\n";
                    std::cout << "Selecciona una opcion: ";

                    if (!(std::cin >> opcionHistorial)) {
                        std::cin.clear();
                        limpiarBuffer();
                        opcionHistorial = -1;
                    }

                    switch (opcionHistorial){

                        case 1: {
                            std::cout << "\n--- HISTORIAL COMPLETO ---\n";
                            std::cout << catalogo.toStringHistorial() << "\n";
                            break;
                        }

                        case 2: {
                            std::cout << "\n--- HISTORIAL INVERSO ---\n";
                            std::cout << catalogo.toStringHistorialReversa() << "\n";
                            break;
                        }

                        case 3: {
                            std::string registro;

                            std::cout << "Escribe el registro completo: ";
                            std::getline(std::cin >> std::ws, registro);

                            if (catalogo.containsHistorial(registro)){
                                std::cout << "Registro encontrado.\n";
                            } else {
                                std::cout << "Posicion del registro a modificar: ";
                            }
                            break;
                        }
                        
                        case 4: {
                            int posicion;
                            std::string nuevoRegistro;

                            std::cout << "Posicion del registro a modificar: ";

                            if (!(std::cin >> posicion)) {
                                std::cin.clear();
                                limpiarBuffer();
                                std::cout << "Posicion invalida.\n";
                                break;
                            }

                            std::cout << "Escribre el nuevo registro: ";
                            std::getline(std::cin >> std::ws, nuevoRegistro);

                            if (catalogo.setHistorial(posicion, nuevoRegistro)) {
                                std::cout << "Registro modificado.\n";
                            } else {
                                std::cout << "Posicion no encontrada.\n";
                            }

                            break;
                        }

                        case 5: {
                            int posicion;

                            std::cout << "Posicion del registro a eliminar: ";

                            if (!(std::cin >> posicion)) {
                                std::cin.clear();
                                limpiarBuffer();
                                std::cout << "Posicion invalida.\n";
                                break;
                            }

                            if (catalogo.removeHistorial(posicion)) {
                                std::cout << "Registro eliminado.\n";
                            } else {
                                std::cout << "Posicion no encontrada.\n";
                            }

                            break;
                        }

                        case 0: {
                            std::cout << "Regresando al menu principal...\n";
                            break;

                        default:
                        std::cout << "Opcion no valida.\n";
                        break;
                        }
                    }
                } while (opcionHistorial != 0);

                break;
            }

            case 10: {
                int opcionEditar;

                do {
                    std::cout << "\n======= MODIFICAR ITEM DEL CATALOGO =======\n";
                    std::cout << "1. Modificar nombre\n";
                    std::cout << "2. Modificar calidad\n";
                    std::cout << "3. Modificar dano\n";
                    std::cout << "4. Modificar lagrimas\n";
                    std::cout << "5. Modificar velocidad\n";
                    std::cout << "6. Modificar rango\n";
                    std::cout << "0. Regresar al menu principal\n";
                    std::cout << "Selecciona una opcion: ";

                    if (!(std::cin >> opcionEditar)) {
                        limpiarBuffer();
                        opcionEditar = -1;
                    }

                    if (opcionEditar == 0) {
                        break;
                    }

                    if (opcionEditar < 1 || opcionEditar > 6) {
                        std::cout << "Opcion no valida.\n";
                        continue;
                    }

                    int idItem;

                    std::cout << "Ingresa el ID del item: ";

                    if (!(std::cin >> idItem)) {
                        limpiarBuffer();
                        std::cout << "ID invalido.\n";
                        continue;
                    }

                    int indice = catalogo.buscarPorID(idItem);

                    if (indice == -1) {
                        std::cout << "No se encontro el item.\n";
                        continue;
                    }

                    std::cout << "\nItem seleccionado:\n";
                    catalogo.getInventario()[indice].imprimirFicha();

                    bool modificado = false;

                    switch (opcionEditar) {

                        case 1: {
                            std::string nuevoNombre;

                            std::cout << "Nuevo nombre: ";
                            std::getline(std::cin >> std::ws, nuevoNombre);

                            modificado = catalogo.modificarNombreItem(
                            idItem, nuevoNombre
                            );
                            break;
                        }

                        case 2: {
                            int nuevaCalidad;

                            std::cout << "Nueva calidad (0-4): ";

                            if (!(std::cin >> nuevaCalidad)) {
                                limpiarBuffer();
                                std::cout << "Calidad invalida.\n";
                                break;
                            }
                                modificado = catalogo.modificarCalidadItem(
                                idItem, nuevaCalidad
                                );
                                break;
                        }

                        case 3:
                        case 4:
                        case 5:
                        case 6: {
                            float nuevoValor;

                            std::cout << "Ingresa el nuevo modificador: ";

                            if (!(std::cin >> nuevoValor)) {
                                limpiarBuffer();
                                std::cout << "Valor invalido.\n";
                                break;
                            }

                            if (opcionEditar == 3) {
                                modificado = catalogo.modificarDanoItem(
                                idItem, nuevoValor
                                );
                            } else if (opcionEditar == 4) {
                                modificado = catalogo.modificarLagrimasItem(
                                idItem, nuevoValor
                                );
                            } else if (opcionEditar == 5) {
                                modificado = catalogo.modificarVelocidadItem(
                                idItem, nuevoValor
                                );
                            } else {
                                modificado = catalogo.modificarRangoItem(
                                idItem, nuevoValor
                                );
                            }

                break;
            }
        }

        if (modificado) {
            std::cout << "\n[OK] Item modificado correctamente.\n";
            std::cout << "Cambio registrado en el historial.\n";
        } else {
            std::cout << "\n[!] No se realizo ninguna modificacion.\n";
        }

    } while (opcionEditar != 0);

    break;
}

            case 11: {
                std::cout << "\nGuardando cambios en '" << rutaArchivo
                          << "'...\n";
                if (catalogo.guardarEnCSV(rutaArchivo)) {
                    std::cout << "[OK] Archivo actualizado en disco.\n";
                } else {
                    std::cout << "[!] Error al escribir el archivo.\n";
                }
                std::cout << "Cerrando Platinum God. ¡Buena suerte!\n";
                break;
            }

            default:
                std::cout << "Opcion no reconocida. Elige entre 1 y 11.\n";
                break;
        }

    } while (opcion != 11);

    return 0;
}
