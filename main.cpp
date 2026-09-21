#include <iostream>
#include <string>
#include <limits>
#include "Catalogo_Isaac.h"

// Funcion auxiliar para limpiar el buffer de entrada en caso de error
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    CatalogoIsaac catalogo;
    const std::string rutaArchivo = "items_isaac.csv";

    // 1. Carga iterativa inicial de los datos
    if (!catalogo.cargarDesdeCSV(rutaArchivo)) {
        std::cerr << "Asegurate de que el archivo '" << rutaArchivo << "' se encuentre en la misma carpeta.\n";
        return 1;
    }

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
        std::cout << "6. Calcular DPS estimado de Isaac (Funcion Directa O(1))\n";
        std::cout << "7. Simular duplicacion Crooked Penny (Funcion Recursiva O(k))\n";
        std::cout << "8. Guardar cambios en CSV y Salir\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "Selecciona una opcion (1-8): ";

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
                std::cout << "\n[OK] El catalogo fue ordenado exitosamente por ID usando Merge Sort O(n log n).\n";
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

                // La busqueda binaria asegura que el arreglo este ordenado internamente
                int indice = catalogo.buscarPorID(idBuscado);
                if (indice != -1) {
                    std::cout << "\n--- ITEM ENCONTRADO (Posicion en vector: " << indice << ") ---\n";
                    catalogo.getInventario()[indice].imprimirFicha();
                } else {
                    std::cout << "\n[!] No se encontro ningun item con el ID #" << idBuscado << ".\n";
                }
                break;
            }

            case 4: {
                std::string pool;
                std::cout << "\nIngresa el nombre de la sala (Treasure, Devil, Angel, Shop, Secret, Boss): ";
                std::cin >> pool;
                catalogo.filtrarPorPool(pool);
                break;
            }

            case 5: {
                int idModificar;
                int nuevoEstado;
                std::cout << "\nIngresa el ID del item cuyo estado deseas cambiar: ";
                if (!(std::cin >> idModificar)) {
                    std::cout << "ID invalido.\n";
                    limpiarBuffer();
                    break;
                }

                std::cout << "Nuevo estado (1 = Desbloqueado, 0 = Bloqueado): ";
                if (!(std::cin >> nuevoEstado) || (nuevoEstado != 0 && nuevoEstado != 1)) {
                    std::cout << "Opcion de estado no valida (solo 1 o 0).\n";
                    limpiarBuffer();
                    break;
                }

                if (catalogo.modificarEstadoDesbloqueo(idModificar, nuevoEstado == 1)) {
                    std::cout << "\n[OK] Registro modificado en memoria correctamente.\n";
                    std::cout << "Recuerda usar la opcion 8 para guardar los cambios permanentemente en disco.\n";
                } else {
                    std::cout << "\n[!] No se pudo encontrar el item con ID #" << idModificar << ".\n";
                }
                break;
            }

            case 6: {
                float danoBase, modDano, lagrimasBase, modLagrimas;
                std::cout << "\n--- CALCULADORA DE DPS (Tiempo O(1)) ---\n";
                std::cout << "Ingresa el dano base de Isaac (por defecto 3.5): ";
                std::cin >> danoBase;
                std::cout << "Ingresa el bono de dano del item (+/-): ";
                std::cin >> modDano;
                std::cout << "Ingresa las lagrimas base (por defecto 1.0): ";
                std::cin >> lagrimasBase;
                std::cout << "Ingresa el bono de lagrimas del item (+/-): ";
                std::cin >> modLagrimas;

                double dps = Calculos_Isaac::calcularDPS(danoBase, modDano, lagrimasBase, modLagrimas);
                std::cout << "\n>> DPS Final proyectado: " << dps << " puntos de dano por segundo.\n";
                break;
            }

            case 7: {
                double cantidadInicial;
                int activaciones;
                std::cout << "\n--- SIMULADOR CROOKED PENNY (Tiempo O(k), Memoria O(k)) ---\n";
                std::cout << "Ingresa la cantidad base del recurso (ej. 5 monedas): ";
                std::cin >> cantidadInicial;
                std::cout << "Ingresa el numero de duplicaciones sucesivas (k): ";
                std::cin >> activaciones;

                if (activaciones < 0) {
                    std::cout << "El numero de activaciones no puede ser negativo.\n";
                } else {
                    double resultado = Calculos_Isaac::simularCrookedPenny(cantidadInicial, activaciones);
                    std::cout << "\n>> Tras " << activaciones << " duplicaciones sucesivas: " 
                              << resultado << " unidades generadas.\n";
                }
                break;
            }

            case 8: {
                std::cout << "\nGuardando cambios en '" << rutaArchivo << "'...\n";
                if (catalogo.guardarEnCSV(rutaArchivo)) {
                    std::cout << "[OK] Archivo actualizado exitosamente en disco.\n";
                } else {
                    std::cout << "[!] Ocurrio un error al intentar escribir el archivo.\n";
                }
                std::cout << "Cerrando sistema Platinum God. ¡Buena suerte en tu run!\n";
                break;
            }

            default:
                std::cout << "Opcion no reconocida. Selecciona un valor entre 1 y 8.\n";
                break;
        }

    } while (opcion != 8);

    return 0;
}