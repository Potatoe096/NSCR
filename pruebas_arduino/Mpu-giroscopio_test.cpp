//------------------------ Librerias ------------------------
#include <Wire.h>
#include <Adafruit_MPU6050.h> // Arduino ide: Herramientas > administrar librerias
#include <Adafruit_Sensor.h>  // Arduino ide: Herramientas > administrar librerias

//----------------------------------------------------------


Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);

  // ---> AQUÍ SE ASIGNAN LOS PINES I2C <---
  // SDA -> Pin A4
  // SCL -> Pin A5
  Wire.begin();

  Serial.println("--- Test Individual MPU6050 ---");
  if (!mpu.begin()) {
    Serial.println("Error: No se detecta el MPU6050.");
    while (1);
  }
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Acel X: "); Serial.print(a.acceleration.x, 1);
  Serial.print(" | Y: "); Serial.print(a.acceleration.y, 1);
  Serial.print(" | Z: "); Serial.print(a.acceleration.z, 1);
  Serial.print(" m/s^2  ||  Giro Z: "); Serial.println(g.gyro.z, 1);
  delay(500);
}