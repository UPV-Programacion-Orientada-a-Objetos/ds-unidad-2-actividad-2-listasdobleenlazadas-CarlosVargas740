/**
 * @file ListaDeCarga.cpp
 * @brief Implementación de la clase ListaDeCarga
 */

#include "../include/ListaDeCarga.h"
#include <iostream>

ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr) {}

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        NodoCarga* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga(dato);
    
    if (cabeza == nullptr) {
        // Lista vacía
        cabeza = nuevo;
        cola = nuevo;
    } else {
        // Añadir al final
        cola->siguiente = nuevo;
        nuevo->previo = cola;
        cola = nuevo;
    }
}

void ListaDeCarga::imprimirMensaje() {
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "[" << actual->dato << "]";
        actual = actual->siguiente;
    }
}
