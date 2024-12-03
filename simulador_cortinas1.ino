// Importamos la librería Servo para controlar el servomotor
#include <Servo.h>

// Declaramos un objeto llamado 'myservo' para manejar el servomotor
Servo myservo;
// Variable para almacenar el ángulo del servomotor
int angulo  =0;
// Definimos el pin analógico donde está conectada la fotoresistencia
int ldr=A0;
// Variable para guardar la lectura del sensor LDR
int lectura;


// Conectamos el servomotor al pin digital 2
void setup()
{
  myservo.attach(2);
}

void loop()
{
  // Leemos el valor analógico de la fotoresistencia
  lectura=analogRead(ldr);
  // Convertimos el rango de la lectura del LDR (0-1023) al rango del servomotor (0-180 grados)
  angulo =map(lectura,0,1023,180,0);
  // Movemos el servomotor al ángulo calculado
  myservo.write(angulo);
  delay(10);
  // Pausa breve para estabilizar la operación
}