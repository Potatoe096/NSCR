/* =========================================================================
   CÓDIGO DE PRUEBA Y TESTEO DE SENSORES 
   ========================================================================= */

#include <Wire.h>

// =========================================================================
// 1. TCA9548A - Módulo Multiplexor I2C
// =========================================================================
// LIBRERÍA: No requiere librería externa (usa Wire.h estándar).
// FUNCIONES:
//   - Wire.beginTransmission(dirección_I2C)
//   - Wire.write(canal_byte)
//   - Wire.endTransmission()
// =========================================================================

#define TCA_ADDR 0x70 // Dirección I2C por defecto del TCA9548A

// Seleccionar el canal (0 a 7) en el multiplexor
void tcaSelect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << i); // Envía un bit desplazado para activar el canal deseado
  Wire.endTransmission();
}

void test_TCA9548A() {
  Serial.println("\n--- [TEST] TCA9548A Multiplexor ---");
  
  // Probamos activando el canal 0
  tcaSelect(0); 
  Serial.println("Canal 0 del multiplexor activado correctamente.");
}


// =========================================================================
// 2. VL53L0X - Medidor de Distancia Láser ToF
// =========================================================================
// LIBRERÍA: "Adafruit_VL53L0X" (por Adafruit)
// FUNCIONES CLAVE:
//   - lox.begin()                 : Inicializa el sensor via I2C.
//   - lox.readRangeSingleMillimeters() : Devuelve la distancia en milímetros (uint16_t).
//   - lox.timeoutOccurred()       : Verifica si hubo un error de tiempo de espera.
// =========================================================================

#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void test_VL53L0X() {
  Serial.println("\n--- [TEST] VL53L0X Distancia ---");
  
  // Si está detrás del multiplexor TCA9548A, seleccionamos su canal primero
  tcaSelect(0); 

  if (!lox.begin()) {
    Serial.println("Error: No se encontró el VL53L0X.");
    return;
  }

  // Medición puntual
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // "false" desactiva el modo debug de la librería

  if (measure.RangeStatus != 4) { // Status 4 significa que la lectura estuvo fuera de rango
    Serial.print("Distancia: ");
    Serial.print(measure.RangeMilliMeter); // <--- FUNCIÓN CLAVE DE LECTURA DE DISTANCIA
    Serial.println(" mm");
  } else {
    Serial.println("Fuera de rango");
  }
}


// =========================================================================
// 3. TCS34725 - Sensor de Reconocimiento de Color RGB
// =========================================================================
// LIBRERÍA: "Adafruit TCS34725" (por Adafruit)
// FUNCIONES CLAVE:
//   - tcs.begin()       : Inicializa el sensor.
//   - tcs.getRawData()  : Obtiene valores de los canales Rojo, Verde, Azul y Claro (Clear).
//   - tcs.setInterrupt(): Controla el LED blanco integrado del módulo (true = apagado, false = encendido).
// =========================================================================

#include "Adafruit_TCS34725.h"

// Inicialización con tiempo de integración y ganancia estándar
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void test_TCS34725() {
  Serial.println("\n--- [TEST] TCS34725 Color RGB ---");

  // Si está conectado al multiplexor, p.ej. canal 1:
  tcaSelect(1);

  if (!tcs.begin()) {
    Serial.println("Error: No se encontró el TCS34725.");
    return;
  }

  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c); // <--- FUNCIÓN CLAVE DE LECTURA RGB

  Serial.print("Rojo (R): "); Serial.print(r);
  Serial.print(" | Verde (G): "); Serial.print(g);
  Serial.print(" | Azul (B): "); Serial.print(b);
  Serial.print(" | Claro (C): "); Serial.println(c);
}


// =========================================================================
// 4. MPU6050 - IMU de 6 Grados de Libertad (Acelerómetro + Giroscopio)
// =========================================================================
// LIBRERÍA: "Adafruit MPU6050" (por Adafruit) + requiere "Adafruit Unified Sensor"
// FUNCIONES CLAVE:
//   - mpu.begin()            : Inicializa el sensor.
//   - mpu.getEvent()          : Obtiene lecturas actualizadas de aceleración, giro y temp.
//   - mpu.setAccelerometerRange() / setGyroRange() : Modifica las escalas de medición.
// =========================================================================

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void test_MPU6050() {
  Serial.println("\n--- [TEST] MPU6050 IMU ---");

  // Si está conectado al multiplexor, p.ej. canal 2:
  tcaSelect(2);

  if (!mpu.begin()) {
    Serial.println("Error: No se encontró el MPU6050.");
    return;
  }

  // Creación de objetos donde se almacenarán las mediciones
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp); // <--- FUNCIÓN CLAVE DE LECTURA DE EVENTOS

  Serial.print("Aceleración X: "); Serial.print(a.acceleration.x);
  Serial.print(" | Y: "); Serial.print(a.acceleration.y);
  Serial.print(" | Z: "); Serial.println(a.acceleration.z);

  Serial.print("Giroscopio X: "); Serial.print(g.gyro.x);
  Serial.print(" | Y: "); Serial.print(g.gyro.y);
  Serial.print(" | Z: "); Serial.println(g.gyro.z);
}


// =========================================================================
// 5. TCRT5000 - Seguidor de Línea Óptico Infrarrojo
// =========================================================================
// LIBRERÍA: Ninguna (Componente analógico/digital básico).
// FUNCIONES CLAVE DE ARDUINO:
//   - pinMode(pin, INPUT)  : Configura el pin digital/analógico.
//   - digitalRead(pin)     : Lee el estado del pin digital DO (HIGH/LOW).
//   - analogRead(pin)      : Lee la intensidad reflejada si usas la salida analógica AO.
// =========================================================================

const int PIN_TCRT_DIGITAL = 4; // Pin digital (DO) del módulo seguidor de línea
const int PIN_TCRT_ANALOG  = 34; // Pin analógico (AO) opcional

void setup_TCRT5000() {
  pinMode(PIN_TCRT_DIGITAL, INPUT); // <--- FUNCIÓN CLAVE
}

void test_TCRT5000() {
  Serial.println("\n--- [TEST] TCRT5000 Seguidor de Línea ---");

  // Lectura Digital (Salida del comparador LM393 del módulo)
  int estadoDigital = digitalRead(PIN_TCRT_DIGITAL); // <--- FUNCIÓN CLAVE
  
  // Lectura Analógica (Valor raw del fototransistor)
  int valorAnalogico = analogRead(PIN_TCRT_ANALOG);   // <--- FUNCIÓN CLAVE (Opcional)

  Serial.print("Estado Digital (0/1): "); Serial.println(estadoDigital);
  Serial.print("Valor Analógico (0-4095/1023): "); Serial.println(valorAnalogico);
}


// =========================================================================
// SETUP Y LOOP PRINCIPAL
// =========================================================================

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.begin(); // Inicialización del bus I2C
  
  setup_TCRT5000(); // Configuración de pines para el seguidor de línea
  
  Serial.println("--- Sistema Listo para Pruebas ---");
}

void loop() {
  test_TCA9548A();
  test_VL53L0X();
  test_TCS34725();
  test_MPU6050();
  test_TCRT5000();

  delay(2000); // Pausa de 2 segundos entre ciclo de pruebas
}