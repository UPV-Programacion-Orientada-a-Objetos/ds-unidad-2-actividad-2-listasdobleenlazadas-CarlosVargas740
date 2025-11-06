/**
 * @file TramaLoad.cpp
 * @brief Implementación de la clase TramaLoad
 */

#include "../include/TramaLoad.h"
#include "../include/ListaDeCarga.h"
#include "../include/RotorDeMapeo.h"
#include <iostream>

TramaLoad::TramaLoad(char c) : dato(c) {}

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    char decodificado = rotor->getMapeo(dato);
    carga->insertarAlFinal(decodificado);
    
    std::cout << "Trama recibida: [L," << dato << "] -> Procesando... -> Fragmento '" 
              << dato << "' decodificado como '" << decodificado << "'. Mensaje: ";
    carga->imprimirMensaje();
    std::cout << std::endl;
}
