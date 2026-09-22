//------------------------ Librerias ------------------------
#include <Wire.h>
#include <Adafruit_VL53L0X.h> // Arduino ide: Herramientas > administrar librerias
//----------------------------------------------------------

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);

  // ---> AQUÍ SE ASIGNAN LOS PINES I2C <---
  // Wire.begin() configura internamente:
  // SDA -> Pin A4 (Arduino Uno)
  // SCL -> Pin A5 (Arduino Uno)
  Wire.begin();

  Serial.println("--- Test Individual VL53L0X ---");
  if (!lox.begin()) {
    Serial.println("Error: No se detecta el VL53L0X.");
    while (1);
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {
    Serial.print("Distancia: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
  } else {
    Serial.println("Fuera de rango");
  }
  delay(500);
}