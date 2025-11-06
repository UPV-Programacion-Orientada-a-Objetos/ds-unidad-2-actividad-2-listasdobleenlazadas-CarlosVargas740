/**
 * @file TramaMap.cpp
 * @brief Implementación de la clase TramaMap
 */

#include "../include/TramaMap.h"
#include "../include/RotorDeMapeo.h"
#include <iostream>

TramaMap::TramaMap(int n) : rotacion(n) {}

void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    rotor->rotar(rotacion);
    
    std::cout << "\nTrama recibida: [M," << rotacion << "] -> Procesando... -> ROTANDO ROTOR ";
    if (rotacion >= 0) {
        std::cout << "+" << rotacion;
    } else {
        std::cout << rotacion;
    }
    std::cout << ".\n" << std::endl;
}
