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

    if (command == "patrulla_izq_on") {
      digitalWrite(ledPin2, HIGH);  // Enciende el LED en el pin 2
      Serial.println("LED encendido");
    } else if (command == "patrulla_izq_off") {
      digitalWrite(ledPin2, LOW);   // Apaga el LED en el pin 2
      Serial.println("LED Off");
    } else if (command == "pesquero_izq_on") {
      digitalWrite(ledPin3, HIGH);   // Apaga el LED en el pin 3
      Serial.println("LED encendido");
    } else if (command == "pesquero_izq_off") {
      digitalWrite(ledPin3, LOW);   // Apaga el LED en el pin 3
      Serial.println("LED Off");
    } else if (command == "normal_izq_on") {
      digitalWrite(ledPin4, HIGH);   // Apaga el LED en el pin 4
      Serial.println("LED encendido");
    } else if (command == "normal_izq_off") {
      digitalWrite(ledPin4, LOW);   // Apaga el LED en el pin 4
      Serial.println("LED Off");
    } else if (command == "canal_izq_on"){
      digitalWrite(ledPin5, HIGH); //Enciende el LED en el pin 5
      Serial.println("LED encendido");
    }else if (command == "canal_izq_off") {
      digitalWrite(ledPin5, LOW);   // Apaga el LED en el pin 5
      Serial.println("LED Off");
    } else if (command == "canal_der_on"){
      digitalWrite(ledPin6, HIGH); //Enciende el LED en el pin 6
      Serial.println("LED encendido");
    } else if (command == "canal_der_off") {
      digitalWrite(ledPin6, LOW);   // Apaga el LED en el pin 6
      Serial.println("LED Off");
    } else if (command == "normal_der_on") {
      digitalWrite(ledPin7, HIGH);   // Apaga el LED en el pin 7
      Serial.println("LED encendido");
    } else if (command == "normal_der_off") {
      digitalWrite(ledPin7, LOW);   // Apaga el LED en el pin 7
      Serial.println("LED Off");
    } else if (command == "pesquero_der_on") {
      digitalWrite(ledPin8, HIGH);   // Apaga el LED en el pin 8
      Serial.println("LED encendido");
    } else if (command == "pesquero_der_off") {
      digitalWrite(ledPin8, LOW);   // Apaga el LED en el pin 8
      Serial.println("LED Off");
    } else if (command == "patrulla_der_on") {
      digitalWrite(ledPin9, HIGH);  // Enciende el LED en el pin 9
      Serial.println("LED encendido");
    } else if (command == "patrulla_der_off") {
      digitalWrite(ledPin9, LOW);  // Enciende el LED en el pin 9
      Serial.println("LED encendido");
    }
    delay(10);  // Agrega un pequeño retardo para asegurarte de que la respuesta se envíe completamente
  }
}
