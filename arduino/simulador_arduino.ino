/**
 * @file simulador_arduino.ino
 * @brief Código Arduino para enviar tramas del protocolo PRT-7
 * 
 * Este sketch envía las tramas del protocolo PRT-7 por el puerto serial
 * con un retraso de 1 segundo entre cada trama.
 */

void setup() {
  // Inicializar comunicación serial a 9600 baudios
  Serial.begin(9600);
  
  // Esperar a que el puerto serial esté listo
  while (!Serial) {
    ; // Esperar
  }
  
  delay(2000); // Esperar 2 segundos antes de comenzar
}

void loop() {
  // Enviar las tramas una por una con delay
  Serial.println("L,H");
  delay(1000);
  
  Serial.println("L,O");
  delay(1000);
  
  Serial.println("L,L");
  delay(1000);
  
  Serial.println("M,2");
  delay(1000);
  
  Serial.println("L,A");
  delay(1000);
  
  Serial.println("L,Space");
  delay(1000);
  
  Serial.println("L,W");
  delay(1000);
  
  Serial.println("M,-2");
  delay(1000);
  
  Serial.println("L,O");
  delay(1000);
  
  Serial.println("L,R");
  delay(1000);
  
  Serial.println("L,L");
  delay(1000);
  
  Serial.println("L,D");
  delay(1000);
  
  // Esperar 5 segundos antes de repetir
  delay(5000);
}
