/**
 * @file main.cpp
 * @brief Programa principal del Decodificador PRT-7
 */

#include "../include/TramaBase.h"
#include "../include/TramaLoad.h"
#include "../include/TramaMap.h"
#include "../include/ListaDeCarga.h"
#include "../include/RotorDeMapeo.h"
#include <iostream>
#include <fstream>
#include <fcntl.h>    // Para open()
#include <unistd.h>   // Para read(), close()
#include <termios.h>  // Para configuración serial
#include <cstring>    // Para strcmp(), memset()
#include <fcntl.h>    // Para open()
#include <unistd.h>   // Para read(), close()
#include <termios.h>  // Para configuración serial
#include <cstring>    // Para strcmp(), memset()

/**
 * @brief Configura el puerto serial para Arduino
 * @param puerto Ruta del puerto serial (ej: /dev/ttyUSB0, /dev/ttyACM0)
 * @return Descriptor de archivo o -1 si hay error
 */
int configurarSerial(const char* puerto) {
    int fd = open(puerto, O_RDONLY | O_NOCTTY);
    if (fd == -1) {
        return -1;
    }
    
    struct termios opciones;
    tcgetattr(fd, &opciones);
    
    // Configurar velocidad 9600 baudios
    cfsetispeed(&opciones, B9600);
    cfsetospeed(&opciones, B9600);
    
    // 8 bits, sin paridad, 1 bit de parada
    opciones.c_cflag &= ~PARENB;  // Sin paridad
    opciones.c_cflag &= ~CSTOPB;  // 1 bit de parada
    opciones.c_cflag &= ~CSIZE;   // Limpiar bits de tamaño
    opciones.c_cflag |= CS8;      // 8 bits de datos
    opciones.c_cflag &= ~CRTSCTS; // Sin control de flujo
    opciones.c_cflag |= CREAD | CLOCAL;
    
    // Modo raw
    opciones.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    opciones.c_iflag &= ~(IXON | IXOFF | IXANY);
    opciones.c_oflag &= ~OPOST;
    
    // Aplicar configuración
    tcsetattr(fd, TCSANOW, &opciones);
    
    // Limpiar buffer
    tcflush(fd, TCIFLUSH);
    
    return fd;
}

/**
 * @brief Lee una línea desde el puerto serial
 * @param fd Descriptor del puerto serial
 * @param buffer Buffer donde guardar la línea
 * @param maxLen Tamaño máximo del buffer
 * @return true si se leyó una línea, false si hay error
 */
bool leerLineaSerial(int fd, char* buffer, int maxLen) {
    int i = 0;
    char c;
    
    while (i < maxLen - 1) {
        int n = read(fd, &c, 1);
        if (n <= 0) {
            return false;
        }
        
        if (c == '\n' || c == '\r') {
            if (i > 0) {
                buffer[i] = '\0';
                return true;
            }
            continue;
        }
        
        buffer[i++] = c;
    }
    
    buffer[i] = '\0';
    return true;
}

/**
 * @brief Parsea una línea del protocolo y devuelve la trama correspondiente
 * @param linea Cadena con el formato "L,X" o "M,N"
 * @return Puntero a la trama creada (debe liberarse con delete)
 */
TramaBase* parsearTrama(const char* linea) {
    if (linea == nullptr || linea[0] == '\0') return nullptr;
    
    char tipo = linea[0];
    
    if (tipo == 'L' && linea[1] == ',') {
        // Trama LOAD
        char dato = linea[2];
        if (dato == 'S' && linea[3] == 'p' && linea[4] == 'a' && linea[5] == 'c' && linea[6] == 'e') {
            dato = ' ';
        }
        return new TramaLoad(dato);
    } else if (tipo == 'M' && linea[1] == ',') {
        // Trama MAP - parsear el número
        int num = 0;
        int signo = 1;
        int i = 2;
        
        if (linea[i] == '-') {
            signo = -1;
            i++;
        } else if (linea[i] == '+') {
            i++;
        }
        
        while (linea[i] >= '0' && linea[i] <= '9') {
            num = num * 10 + (linea[i] - '0');
            i++;
        }
        
        return new TramaMap(num * signo);
    }
    
    return nullptr;
}

/**
 * @brief Función principal del decodificador
 */
int main(int argc, char* argv[]) {
    std::cout << "Iniciando Decodificador PRT-7. Conectando a puerto COM..." << std::endl;
    
    // Crear las estructuras de datos
    ListaDeCarga miListaDeCarga;
    RotorDeMapeo miRotorDeMapeo;
    
    // Determinar modo de entrada
    bool modoSerial = false;
    const char* puerto = "/dev/ttyUSB0";  // Puerto por defecto para Arduino en Linux
    const char* archivo = "tramas.txt";
    
    // Verificar argumentos: ./decodificador serial /dev/ttyUSB0
    //                    o: ./decodificador archivo tramas.txt
    if (argc > 1) {
        if (strcmp(argv[1], "serial") == 0) {
            modoSerial = true;
            if (argc > 2) {
                puerto = argv[2];
            }
        } else {
            archivo = argv[1];
        }
    }
    
    if (modoSerial) {
        // MODO SERIAL: Leer desde Arduino
        std::cout << "Abriendo puerto serial: " << puerto << std::endl;
        
        int serialFd = configurarSerial(puerto);
        if (serialFd == -1) {
            std::cout << "ERROR: No se pudo abrir el puerto " << puerto << std::endl;
            std::cout << "Verifica que el Arduino este conectado." << std::endl;
            std::cout << "Puertos comunes: /dev/ttyUSB0, /dev/ttyACM0" << std::endl;
            std::cout << "\nUsando tramas de prueba en su lugar...\n" << std::endl;
            
            // Fallback a tramas de prueba
            const char* tramas[] = {
                "L,H", "L,O", "L,L", "M,2", "L,A", "L,Space", 
                "L,W", "M,-2", "L,O", "L,R", "L,L", "L,D", nullptr
            };
            
            for (int i = 0; tramas[i] != nullptr; i++) {
                TramaBase* trama = parsearTrama(tramas[i]);
                if (trama != nullptr) {
                    trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                    delete trama;
                }
            }
        } else {
            std::cout << "Conexion establecida. Esperando tramas del Arduino...\n" << std::endl;
            std::cout << "Presiona Ctrl+C para detener.\n" << std::endl;
            
            char linea[100];
            int contadorTramas = 0;
            
            while (true) {
                if (leerLineaSerial(serialFd, linea, 100)) {
                    contadorTramas++;
                    
                    // Parsear y procesar la trama
                    TramaBase* trama = parsearTrama(linea);
                    if (trama != nullptr) {
                        trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                        delete trama;
                    }
                    
                    // Salir después de 12 tramas (como el ejemplo)
                    if (contadorTramas >= 12) {
                        break;
                    }
                }
            }
            
            close(serialFd);
        }
    } else {
        // MODO ARCHIVO: Leer desde archivo de texto
        std::cout << "Leyendo desde archivo: " << archivo << std::endl;
        std::cout << "Conexion establecida. Esperando tramas...\n" << std::endl;
        
        std::ifstream entrada(archivo);
        if (entrada.is_open()) {
            char linea[100];
            
            while (entrada.getline(linea, 100)) {
                if (linea[0] == '\0') continue;
                
                TramaBase* trama = parsearTrama(linea);
                if (trama != nullptr) {
                    trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                    delete trama;
                }
            }
            
            entrada.close();
        } else {
            std::cout << "ERROR: No se pudo abrir el archivo " << archivo << std::endl;
            return 1;
        }
    }
    
    // Mostrar resultado final
    std::cout << "\n---" << std::endl;
    std::cout << "Flujo de datos terminado." << std::endl;
    std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
    miListaDeCarga.imprimirMensaje();
    std::cout << "\n---" << std::endl;
    std::cout << "Liberando memoria... Sistema apagado." << std::endl;
    
    return 0;
}
