/**
 * @file RotorDeMapeo.h
 * @brief Lista circular doblemente enlazada que actúa como disco de cifrado
 */

#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

/**
 * @struct NodoRotor
 * @brief Nodo para la lista circular doblemente enlazada
 */
struct NodoRotor {
    char dato;
    NodoRotor* siguiente;
    NodoRotor* previo;
    
    NodoRotor(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class RotorDeMapeo
 * @brief Lista circular doblemente enlazada que contiene el alfabeto A-Z
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza; ///< Puntero a la posición 'cero' actual
    
public:
    /**
     * @brief Constructor que inicializa el rotor con A-Z
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor que libera la memoria
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor N posiciones
     * @param n Número de posiciones (positivo o negativo)
     */
    void rotar(int n);
    
    /**
     * @brief Obtiene el carácter mapeado según la rotación actual
     * @param in El carácter de entrada
     * @return El carácter mapeado
     */
    char getMapeo(char in);
};

#endif // ROTOR_DE_MAPEO_H
