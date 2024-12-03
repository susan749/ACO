float temp, tempC, tempMV; // Variables para almacenar datos de temperatura
                          // temp: Valor leído del sensor
                          // tempMV: Valor convertido a milivoltios
                          // tempC: Temperatura en grados Celsius

void setup() {
  pinMode(A0, INPUT);    // Configura el pin A0 como entrada para el sensor de temperatura
  pinMode(8, OUTPUT);    // Configura el pin 8 como salida para controlar el motor
  pinMode(7, OUTPUT);    // Configura el pin 7 como salida para apagar el motor
}

void loop() {
  temp = analogRead(A0);          // Lee el valor analógico del sensor de temperatura
  tempMV = temp * 5000 / 1024;    // Convierte la lectura analógica a milivoltios
  tempC = (tempMV / 10) + (-50);  // Convierte los milivoltios a grados Celsius
  Serial.println(tempC);          // Envía la temperatura al monitor serial

  // Condición para activar o desactivar el motor
  if (tempC > 23) {               // Si la temperatura es mayor a 23°C
    digitalWrite(8, HIGH);        // Enciende el motor (pin 8 en HIGH)
    digitalWrite(7, LOW);         // Asegura que el pin 7 esté en LOW
  } else {                        // Si la temperatura es 23°C o menor
    digitalWrite(8, LOW);         // Apaga el motor (pin 8 en LOW)
    digitalWrite(7, LOW);         // Mantiene el pin 7 en LOW
  }
}
