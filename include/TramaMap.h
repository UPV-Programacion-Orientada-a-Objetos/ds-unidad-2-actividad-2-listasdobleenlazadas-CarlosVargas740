/**
 * @file TramaMap.h
 * @brief Trama de mapeo que rota el rotor de cifrado
 */

#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"

/**
 * @class TramaMap
 * @brief Representa una trama tipo MAP (M,N) que rota el rotor
 */
class TramaMap : public TramaBase {
private:
    int rotacion; ///< Número de posiciones a rotar (puede ser negativo)
    
public:
    /**
     * @brief Constructor que inicializa la trama con un valor de rotación
     * @param n El número de posiciones a rotar
     */
    TramaMap(int n);
    
    /**
     * @brief Procesa la trama rotando el rotor
     * @param carga Puntero a la lista de carga (no se usa)
     * @param rotor Puntero al rotor de mapeo
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_MAP_H
