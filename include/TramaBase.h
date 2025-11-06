/**
 * @file TramaBase.h
 * @brief Clase base abstracta para todas las tramas del protocolo PRT-7
 */

#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

// Forward declarations
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase base abstracta que define la interfaz para todas las tramas
 */
class TramaBase {
public:
    /**
     * @brief Destructor virtual para asegurar destrucción correcta
     */
    virtual ~TramaBase() {}
    
    /**
     * @brief Procesa la trama usando las estructuras de datos proporcionadas
     * @param carga Puntero a la lista de carga donde se almacenan los datos decodificados
     * @param rotor Puntero al rotor de mapeo que define el cifrado actual
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif // TRAMA_BASE_H
