//------------------------ Librerias ------------------------
  //*no requiere
//----------------------------------------------------------

// ---> AQUÍ TÚ ELIGES Y ASIGNAS LOS PINES LIBREMENTE <---
const int PIN_DIGITAL = 4;  // Pin para la salida DO (Digital)
const int PIN_ANALOG  = A0; // Pin para la salida AO (Analógica)

void setup() {
  Serial.begin(9600);

  // Configura el pin 4 como entrada de datos
  pinMode(PIN_DIGITAL, INPUT); 
  
  // Nota: El pin A0 no requiere pinMode() porque analogRead() 
  // lo configura automáticamente.

  Serial.println("--- Test Individual TCRT5000 ---");
}

void loop() {
  int estadoDigital = digitalRead(PIN_DIGITAL);
  int valorAnalogico = analogRead(PIN_ANALOG);

  Serial.print("Digital (0/1): "); Serial.print(estadoDigital);
  Serial.print(" | Analógico (0-1023): "); Serial.println(valorAnalogico);
  delay(500);
}

