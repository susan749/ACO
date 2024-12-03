void setup() {
  Serial.begin(9600);    // Inicializa la comunicación serial a 9600 baudios para monitorear datos en el monitor serial.
  pinMode(7, OUTPUT);    // Configura el pin digital 7 como salida para controlar el LED.
}

void loop() {
  int c = analogRead(A0);  // Lee el valor analógico de la fotorresistencia conectado al pin A0.
  Serial.println(c);       // Imprime el valor leído en el monitor serial para monitoreo.

  // Condición para encender o apagar el LED según la cantidad de luz detectada.
  if (c < 500) {           // Si el valor leído es menor a 500 (luz tenue o poca iluminación):
    digitalWrite(7, LOW);  // Apaga el LED (pin 7 en LOW).
  } else {                 // Si el valor leído es mayor o igual a 500 (mucha iluminación):
    digitalWrite(7, HIGH); // Enciende el LED (pin 7 en HIGH).
  }
}
