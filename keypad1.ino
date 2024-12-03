#include <Keypad.h>        // Librería para manejar el teclado matricial (keypad)
#include <LiquidCrystal.h> // Librería para controlar la pantalla LCD
#include <Servo.h>         // Librería para controlar el servomotor

#define Password_Length 5  // Longitud de la contraseña (incluye el carácter nulo '\0')

Servo myservo;  // Creación del objeto para el servomotor
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); // Conexión de la pantalla LCD usando pines analógicos

int pos = 0;  // Variable para el ángulo del servomotor

char Data[Password_Length];  // Almacena los datos ingresados por el usuario
char Master[Password_Length] = "1234"; // Contraseña maestra
byte data_count = 0;  // Contador para los caracteres ingresados
bool door = false;    // Estado de la puerta: cerrada (false) o abierta (true)
char customKey;       // Variable para almacenar la tecla presionada

// Configuración del teclado 4x4
const byte ROWS = 4;  
const byte COLS = 4;
char keys[ROWS][COLS] = {  // Mapa de teclas
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3}; // Pines conectados a las filas del teclado
byte colPins[COLS] = {4, 5, 6, 7}; // Pines conectados a las columnas del teclado
Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); // Objeto para manejar el teclado

// Configuración inicial del sistema
void setup() {
  myservo.attach(9, 2000, 2400); // Conectar el servomotor al pin 9 con límites PWM
  ServoClose();                 // Asegurarse de que el servomotor esté cerrado al inicio
  lcd.begin(16, 2);             // Inicializar la pantalla LCD de 16x2 caracteres
  lcd.print("Protected Door");  // Mostrar el mensaje inicial
  loading("Loading");           // Mostrar animación de carga
  lcd.clear();                  // Limpiar la pantalla
}

void loop() {
  if (door == true) {  // Si la puerta está abierta
    customKey = customKeypad.getKey(); // Leer la tecla presionada
    if (customKey == '#') {            // Si se presiona '#', cerrar la puerta
      lcd.clear();
      ServoClose();
      lcd.print("Door is closed");
      delay(3000);
      door = false;  // Cambiar el estado a puerta cerrada
    }
  } else {
    Open();  // Llamar a la función para solicitar contraseña
  }
}

// Función de animación de carga
void loading(char msg[]) {
  lcd.setCursor(0, 1);
  lcd.print(msg);
  for (int i = 0; i < 9; i++) {
    delay(1000);
    lcd.print(".");
  }
}

// Función para limpiar la entrada de datos
void clearData() {
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
}

// Función para cerrar el servomotor gradualmente
void ServoClose() {
  for (pos = 180; pos >= 0; pos -= 10) {
    myservo.write(pos);
    delay(15);
  }
}

// Función para abrir el servomotor gradualmente
void ServoOpen() {
  for (pos = 0; pos <= 180; pos += 10) {
    myservo.write(pos);
    delay(15);
  }
}

// Función para solicitar y verificar la contraseña
void Open() {
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");  // Mostrar mensaje para ingresar contraseña
  customKey = customKeypad.getKey(); // Leer la tecla presionada

  if (customKey) {  // Si se presiona una tecla
    Data[data_count] = customKey;  // Guardar el carácter en el arreglo
    lcd.setCursor(data_count, 1);  // Mover el cursor a la posición correspondiente
    lcd.print(Data[data_count]);  // Mostrar el carácter ingresado en la pantalla
    data_count++;
  }

  if (data_count == Password_Length - 1) {  // Si la contraseña está completa
    if (!strcmp(Data, Master)) {            // Comparar con la contraseña maestra
      lcd.clear();
      ServoOpen();
      lcd.print(" Door is Open ");
      door = true;
      delay(5000);            // Mantener la puerta abierta por un tiempo
      loading("Waiting");     // Mostrar animación de espera
      lcd.clear();
      lcd.print(" Time is up! ");
      delay(1000);
      ServoClose();
      door = false;           // Cambiar el estado a puerta cerrada
    } else {  // Si la contraseña es incorrecta
      lcd.clear();
      lcd.print(" Wrong Password ");
      door = false;
    }
    delay(1000);
    lcd.clear();
    clearData();  // Limpiar la entrada de datos
  }
}
