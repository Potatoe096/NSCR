//------------------------ Librerias ------------------------
#include <Wire.h>
#include <Adafruit_TCS34725.h> // Arduino ide: Herramientas > administrar librerias
//----------------------------------------------------------


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);

  // ---> AQUÍ SE ASIGNAN LOS PINES I2C <---
  // SDA -> Pin A4
  // SCL -> Pin A5
  Wire.begin();

  Serial.println("--- Test Individual TCS34725 ---");
  if (!tcs.begin()) {
    Serial.println("Error: No se detecta el TCS34725.");
    while (1);
  }
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  Serial.print("Rojo: "); Serial.print(r);
  Serial.print(" | Verde: "); Serial.print(g);
  Serial.print(" | Azul: "); Serial.print(b);
  Serial.print(" | Claro: "); Serial.println(c);
  delay(500);
}
