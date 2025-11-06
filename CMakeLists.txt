cmake_minimum_required(VERSION 3.10)
project(DecodificadorPRT7 VERSION 1.0)

# Configurar estándar C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir directorios
include_directories(include)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/TramaLoad.cpp
    src/TramaMap.cpp
    src/RotorDeMapeo.cpp
    src/ListaDeCarga.cpp
)

# Crear ejecutable
add_executable(decodificador ${SOURCES})

# Configuración de instalación
install(TARGETS decodificador DESTINATION bin)
