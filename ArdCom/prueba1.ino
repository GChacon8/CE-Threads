int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);  // Configura el pin 2 como salida
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
