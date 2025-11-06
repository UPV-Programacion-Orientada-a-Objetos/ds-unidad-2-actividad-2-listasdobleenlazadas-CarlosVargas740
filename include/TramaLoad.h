/**
 * @file TramaLoad.h
 * @brief Trama de carga que contiene un fragmento de datos
 */

#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"

/**
 * @class TramaLoad
 * @brief Representa una trama tipo LOAD (L,X) que contiene un carácter
 */
class TramaLoad : public TramaBase {
private:
    char dato; ///< El carácter contenido en la trama
    
public:
    /**
     * @brief Constructor que inicializa la trama con un carácter
     * @param c El carácter a almacenar
     */
    TramaLoad(char c);
    
    /**
     * @brief Procesa la trama decodificando el carácter y añadiéndolo a la lista
     * @param carga Puntero a la lista de carga
     * @param rotor Puntero al rotor de mapeo
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_LOAD_H
