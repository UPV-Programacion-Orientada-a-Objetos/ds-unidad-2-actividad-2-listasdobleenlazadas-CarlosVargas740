/**
 * @file RotorDeMapeo.cpp
 * @brief Implementación de la clase RotorDeMapeo
 */

#include "../include/RotorDeMapeo.h"

RotorDeMapeo::RotorDeMapeo() {
    // Crear la lista circular con A-Z y espacio
    cabeza = new NodoRotor('A');
    NodoRotor* actual = cabeza;
    
    // Crear nodos de B a Z
    for (char c = 'B'; c <= 'Z'; c++) {
        NodoRotor* nuevo = new NodoRotor(c);
        actual->siguiente = nuevo;
        nuevo->previo = actual;
        actual = nuevo;
    }
    
    // Agregar espacio al final
    NodoRotor* espacio = new NodoRotor(' ');
    actual->siguiente = espacio;
    espacio->previo = actual;
    
    // Cerrar el círculo
    espacio->siguiente = cabeza;
    cabeza->previo = espacio;
}

RotorDeMapeo::~RotorDeMapeo() {
    if (cabeza == nullptr) return;
    
    NodoRotor* actual = cabeza->siguiente;
    while (actual != cabeza) {
        NodoRotor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    delete cabeza;
}

void RotorDeMapeo::rotar(int n) {
    if (cabeza == nullptr) return;
    
    // Normalizar n para evitar rotaciones innecesarias
    int total = 27; // A-Z + espacio
    n = n % total;
    
    if (n > 0) {
        // Rotar hacia adelante
        for (int i = 0; i < n; i++) {
            cabeza = cabeza->siguiente;
        }
    } else if (n < 0) {
        // Rotar hacia atrás
        for (int i = 0; i > n; i--) {
            cabeza = cabeza->previo;
        }
    }
}

char RotorDeMapeo::getMapeo(char in) {
    if (cabeza == nullptr) return in;
    
    // Buscar el carácter en la lista
    NodoRotor* actual = cabeza;
    int posicion = 0;
    
    do {
        if (actual->dato == in) {
            // Encontrado, ahora obtener el carácter en la posición relativa desde cabeza
            NodoRotor* resultado = cabeza;
            for (int i = 0; i < posicion; i++) {
                resultado = resultado->siguiente;
            }
            return resultado->dato;
        }
        actual = actual->siguiente;
        posicion++;
    } while (actual != cabeza);
    
    // Si no se encuentra, devolver el mismo carácter
    return in;
}
