int codigo;            // Variable para almacenar el código ingresado
int estado;            // Variable para el estado de la alarma: activada (true) o desactivada (false)
int led1 = 5;          // Pin conectado al LED 1
int led2 = 7;          // Pin conectado al LED 2
int bocina = 6;        // Pin conectado a la bocina (piezoeléctrico)
int sensor = A0;       // Pin analógico conectado al sensor PIR
int contra = 1234;     // Código de seguridad para activar/desactivar la alarma

void setup() {
  pinMode(led1, OUTPUT);    // Configura el pin del LED 1 como salida
  pinMode(led2, OUTPUT);    // Configura el pin del LED 2 como salida
  pinMode(sensor, INPUT);   // Configura el pin del sensor PIR como entrada
  pinMode(bocina, OUTPUT);  // Configura el pin de la bocina como salida
  Serial.begin(9600);       // Inicia la comunicación serial a 9600 baudios
}

void loop() {
  // Solicitar el código para activar la alarma
  if (estado == false) { 
    Serial.println("INGRESA CODIGO DE ACTIVACION"); // Mensaje para el usuario
    codigo = Serial.parseInt();                    // Lee el código ingresado
    if (codigo == contra) {                        // Verifica si el código es correcto
      Serial.println("ALARMA ACTIVADA");           // Informa que la alarma está activada
      estado = true;                               // Cambia el estado a activada
    }
  }

  // Detectar código para desactivar la alarma sin movimiento
  if (estado == true) {
    codigo = Serial.parseInt();                    // Lee el código ingresado
    if (codigo == contra) {                        // Verifica si el código es correcto
      Serial.println("ALARMA DESACTIVADA SIN MOVIMIENTO"); // Mensaje de alarma desactivada
      estado = false;                              // Cambia el estado a desactivada
    }
  }

  // Detectar movimiento con la alarma activa
  if (estado == true && digitalRead(sensor) == HIGH) {
    Serial.println("MOVIMIENTO DETECTADO");        // Informa que se detectó movimiento
    Serial.println("INGRESE EL CODIGO PARA DESACTIVAR LA ALARMA"); // Solicita el código

    // Activa la alarma hasta que se ingrese el código correcto
    while (estado == true) {
      tone(bocina, 2500);                          // Emite un sonido en la bocina
      digitalWrite(led1, LOW);                     // Enciende el LED 2 y apaga el LED 1
      digitalWrite(led2, HIGH);
      delay(1000);                                 // Retardo para el parpadeo
      digitalWrite(led1, HIGH);                    // Enciende el LED 1 y apaga el LED 2
      digitalWrite(led2, LOW);
      
      codigo = Serial.parseInt();                  // Lee el código ingresado
      if (contra == codigo) {                      // Verifica si el código es correcto
        Serial.println("ALARMA DESACTIVADA");      // Mensaje de alarma desactivada
        noTone(bocina);                            // Apaga la bocina
        estado = false;                            // Cambia el estado a desactivada
        digitalWrite(led1, LOW);                   // Apaga los LEDs
      }
    }
  }
}











