int ledPin1 = 2;
int ledPin2 = 3;
int ledPin3 = 4;
int ledPin4 = 5;
int ledPin5 = 6;
int ledPin6 = 7;
int ledPin7 = 8;
int ledPin8 = 9;

void setup() {
  pinMode(ledPin1, OUTPUT);  // Configura el pin 2 como salida
  pinMode(ledPin2, OUTPUT);  // Configura el pin 3 como salida
  pinMode(ledPin3, OUTPUT);  // Configura el pin 4 como salida
  pinMode(ledPin4, OUTPUT);  // Configura el pin 5 como salida
  pinMode(ledPin5, OUTPUT);  // Configura el pin 6 como salida
  pinMode(ledPin6, OUTPUT);  // Configura el pin 7 como salida
  pinMode(ledPin7, OUTPUT);  // Configura el pin 8 como salida
  pinMode(ledPin8, OUTPUT);  // Configura el pin 9 como salida
  Serial.begin(9600);       // Inicializa la comunicación serial a 9600 baudios
}

void loop() {
  if (Serial.available() > 0) {  // Si hay datos disponibles en el puerto serial
    String command = Serial.readString();  // Leer el comando como una cadena

    command.trim();  // Elimina espacios en blanco alrededor del comando

    if (command == "On") {
      digitalWrite(ledPin, HIGH);  // Enciende el LED en el pin 2
      Serial.println("LED encendido");
    } else if (command == "Off") {
      digitalWrite(ledPin, LOW);   // Apaga el LED en el pin 2
      Serial.println("LED Off");
    } else {
      Serial.println("Comando no reconocido");
    }

    delay(10);  // Agrega un pequeño retardo para asegurarte de que la respuesta se envíe completamente
  }
}
