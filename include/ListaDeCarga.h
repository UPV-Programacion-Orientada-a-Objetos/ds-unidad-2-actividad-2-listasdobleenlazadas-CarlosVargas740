/**
 * @file ListaDeCarga.h
 * @brief Lista doblemente enlazada para almacenar los caracteres decodificados
 */

#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

/**
 * @struct NodoCarga
 * @brief Nodo para la lista doblemente enlazada
 */
struct NodoCarga {
    char dato;
    NodoCarga* siguiente;
    NodoCarga* previo;
    
    NodoCarga(char c) : dato(c), siguiente(nullptr), previo(nullptr) {}
};

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada que almacena los caracteres decodificados
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza;  ///< Primer nodo de la lista
    NodoCarga* cola;    ///< Último nodo de la lista
    
public:
    /**
     * @brief Constructor que inicializa la lista vacía
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor que libera la memoria
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un carácter al final de la lista
     * @param dato El carácter a insertar
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje completo
     */
    void imprimirMensaje();
};

#endif // LISTA_DE_CARGA_H
