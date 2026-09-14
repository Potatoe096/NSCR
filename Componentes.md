Componentes a usar

Multiplexor 

TCA9548A: Módulo Multiplexor I2C UNIT DevLab
------------------------------------------------------
LIBRERÍA: No requiere librería externa como los sensores (usa Wire.h estándar).
FUNCIONES CLAVE: 
    -Wire.beginTransmission(dirección_I2C)
    -Wire.write(canal_byte)
    -Wire.endTransmission()


Sensores que usamos (algunos requieren descargar librerias externas)


VL53L0X: Medidor de distancia Laser I2C 940nm ToF 
Tamaño: 4.40 x 2.40 x 1.00 mm
------------------------------------------------------
LIBRERÍA: "Adafruit_VL53L0X" (por Adafruit)
FUNCIONES CLAVE:
  -lox.begin()                         : Inicializa el sensor via I2C
  -lox.readRangeSingleMillimeters()    : Devuelve la distancia(mm)
  -lox.timeoutOccurred()               : Verifica si hubo un error de tiempo de esper

TCS34725: Sensor de Reconocimiento de Color RGB (Rango optimo de 2 mm a 6mm)
Tamaño: 
-------------------------------------------------------
LIBRERÍA: "Adafruit TCS34725" (por Adafruit)
FUNCIONES CLAVE:
  -tcs.begin()       : Inicializa el sensor
  -tcs.getRawData()  : Obtiene valores de Rojo, Verde, Azul (Estos tres RGB) y Claro (Lo Blanco que es algo?)
  -tcs.setInterrupt(): Controla el LED blanco integrado (true = apagado, false = encendido *Me pregunto si se podrá cambiar)

IMU MPU6050: 6 Grados de libertad (navegación)
-------------------------------------------------------
LIBRERÍA: "Adafruit MPU6050" (por Adafruit) + requiere "Adafruit Unified Sensor"
FUNCIONES CLAVE:
  -mpu.begin()                                  : Inicializa el sensor
  -mpu.getEvent()                               : Obtiene lecturas actualizadas de aceleración (m/s2), giro(rad/s) y temp( °C *temperatura del chip)
  -mpu.setAccelerometerRange() / setGyroRange() : Modifica las escalas de medición (Medir cambios más o menos brucos)



Seguidor: de Linea TCRT5000 Optico Infrarrojo - Modulo (Rango optimo 2mm a 15mm)
-------------------------------------------------------
LIBRERÍA: Ninguna (Componente analógico/digital básico).
FUNCIONES CLAVE DE ARDUINO:
  -pinMode(pin, INPUT)  : Configura el pin digital/analógico.
  -digitalRead(pin)     : Lee el estado del pin digital DO (HIGH/LOW).
  -analogRead(pin)      : Lee la intensidad reflejada si usas la salida analógica AO.



Motor y Driver

    Motor:
    GM 25-370 Motor con Encoder 12V DC 140RPM / 330RPM - 140 rpm (4)
    Driver:
    Bts7960 (Driver que de sobra soportara estos motores sin quemarse / hasta 43 A)

Electrónica

Conector Compatible XT60 Par (3)
Fusible Automotriz 32V de 10A a 30A - 10A (2)
Fusible Automotriz 32V de 10A a 30A - 15A (4)
Fusible Automotriz 32V de 10A a 30A - 20A (2)
Kit de 250 Capacitores Cerámicos
JUego de 4 pilas AAA 1.5 V alcalinas (Fuente de poder)

MUL-281 Multímetro Profesional RMS con Detector de Voltaje 
