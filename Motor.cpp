/* =========================================================================
   Alles Anfag ist schwer (Todo comienzo es dificil)
   ========================================================================= */

 // Primero las librerias
    // #
    // # 


    // Definir constantes
    // Pines correspondientes a cada motor, ejemplo:
    // #define In1 10
    // #define In2 9
    // #define In3 8
    // #define In4 7


    // Otras configuraciones
    // #define Ena 11
    // #define Ena 6

    // Velocidad
    // int speed left
    // int speed right

    // Set up
    // void setup()
    // Inicializar los pines

    // pinMode(trigPin, OUTPUT);
    // PinMode(echoPin, INPUT);

    // Pines de los motores
    // pinMode(INn, OUTPUT);
    // -
    // -
    // -



    // pinMode(Ena, OUTPUT);
    // pinMode(ENB, OUTPUT);



    // Loop
    // void loop()
    // aqui va todo el codigo correspondiente

    // usando el driver del motor, podre controlar individualmente cada uno, o en pares

    // Puedo hacer funciones para que avanzen o retrocedan fuera del scope, para luego
    // integrarlas, o pegar el codigo en bruto aqui 

    // Funciones

    // Ir recto
    // Girar a la derecha
    // Girar a la izquierda
    // Retroceder

/* =========================================================================
   Testeo DE 1 MOTOR CON DRIVERS BTS7960 Y ARDUINO
   ========================================================================= */

    //Pines conectados al driver

    const int Rpwm_Pin = a;     // Bts7960 Pin connected to Arduino pin x
    const int Lpwm_Pin = b;    // Bts7960 Pin connected to Arduino pin y

    // Pwm es el pin analogico, 
    // R_En y L_EN son las salidas digitales (high and low) para dar vuelta en Arduino
    
    void setup()
    {
        // Pines del driver
        pinMode(Rpwm_Pin, OUTPUT);
        pinMode(Lpwm_Pin, OUTPUT);
    }

    void loop()
    {
        // Move forward
        for(int speed = 0; speed <= 255; speed++)
        {
            analogwrite(Rpwm_Pin, speed);
            analogwrite(Lpwm_Pin, 0);
            delay (39) // Aumenta gradualmente velocidad (al frente)
        }

        delay(2000); //Para por dos segundos

        for(int speed = 0; speed <= 255; speed++)
        {
            analogwrite(Lpwm_Pin, speed);
            analogwrite(Rpwm_Pin, 0);
            delay (39) // Aumenta gradualmente velocidad (atras)
        }
        delay(2000);  // Para antes de repetir el loop
    }

/* =========================================================================
   CONTROL DE 4 MOTORES CON DRIVERS BTS7960 (uno para cada uno) Y ARDUINO
   ========================================================================= */


// Estructura para agrupar los pines de un driver BTS7960
struct MotorBTS {
  int rPwmPin; // Giro Derecha / Avanzar (PWM)
  int lPwmPin; // Giro Izquierda / Retroceder (PWM)
  int rEnPin;  // Enable Derecha (Digital)
  int lEnPin;  // Enable Izquierda (Digital)
};

// Configuración de Pines 

MotorBTS motorDI = { 2,  3, 22, 23}; // Delantero Izquierdo (DI)
MotorBTS motorDD = { 4,  5, 24, 25}; // Delantero Derecho   (DD)
MotorBTS motorTI = { 6,  7, 26, 27}; // Trasero Izquierdo   (TI)
MotorBTS motorTD = { 8,  9, 28, 29}; // Trasero Derecho     (TD)


// Funciones para mover el motor
void moverMotor(MotorBTS motor, int velocidad) 
{
  // Aseguramos que la velocidad esté dentro del rango permitido
  velocidad = constrain(velocidad, -255, 255);

  if (velocidad > 0) 
  {
    // Giro a la derecha / Avanzar
    analogWrite(motor.rPwmPin, velocidad);
    analogWrite(motor.lPwmPin, 0);
  } 
  
  else if (velocidad < 0) {
    // Giro a la izquierda / Retroceder
    analogWrite(motor.rPwmPin, 0);
    analogWrite(motor.lPwmPin, abs(velocidad)); // abs() convierte el valor a positivo
  } else {
    // Parar
    analogWrite(motor.rPwmPin, 0);
    analogWrite(motor.lPwmPin, 0);
  }
}

// Configuración de pines de un motor individual
void inicializarMotor(MotorBTS motor) {
  pinMode(motor.rPwmPin, OUTPUT);
  pinMode(motor.lPwmPin, OUTPUT);
  pinMode(motor.rEnPin, OUTPUT);
  pinMode(motor.lEnPin, OUTPUT);

  // Activamos los pines de habilitación (Enable) en HIGH permanentemente
  // Los pines Enable sirven como una puerta para la corriente, si no están activos la señal no llegará
  digitalWrite(motor.rEnPin, HIGH);
  digitalWrite(motor.lEnPin, HIGH);
}


//Funciones elementales

// La estructura basica seria:
        // mover el motor (motor, velocidad(+ avanza, - retrocede, 0 quieto))
    
// Dandoles un valor de velocidad, los motores debrrian de hacer el nombre de cada función 

        
void Avanzar (int velocidad)
{
      
  moverMotor(motorDI, velocidad);
  moverMotor(motorDD, velocidad);
  moverMotor(motorDD, velocidad);
  moverMotor(motorDD, velocidad);
        
}

void Retroceder(int velocidad)
{
    moverMotor(motorDI, -velocidad);
    moverMotor(motorDD, -velocidad);
    moverMotor(motorTI, -velocidad);
    moverMotor(motorTD, -velocidad);
}

// Para detenerse no hace falta ni siquiera pasar argumentos
void Detenerse()
{
  moverMotor(motorDI, 0);
  moverMotor(motorDD, 0);
  moverMotor(motorDD, 0);
  moverMotor(motorDD, 0);
}

// Para girar hacia un lado, las llantas de ese lado, se deberian de parar, asi sirven de eje y  las otras llantas lo hacen girar hacia ese lado
// Se me ocurre tambien girar más lento para tener mejor control (velocidad/2)
// Otra idea seria girar con velocidad contraria las otras llantas, para no desplazar tanto el carro al girar.

void Giro_derecha(int velocidad)
{
  moverMotor(motorDI, velocidad);
  moverMotor(motorDD, 0);
  moverMotor(motorTI, velocidad);
  moverMotor(motorTD, 0);
}

void Giro_izquierda(int velocidad)
{
  moverMotor(motorDI, 0);
  moverMotor(motorDD, velocidad);
  moverMotor(motorTI, 0);
  moverMotor(motorTD, velocidad);
}

   
// Void Set up y void loop
void setup() 
{
  // Inicializamos cada uno de los 4 motores
  inicializarMotor(motorDI);
  inicializarMotor(motorDD);
  inicializarMotor(motorTI);
  inicializarMotor(motorTD);
}

void loop() 
{
  // Ejemplo: Aceleración progresiva hacia adelante
  for (int speed = 0; speed <= 255; speed++) {
    Avanzar(speed);
    delay(20);
  }

  delay(2000); // Mantener avance 2 segundos

  Detenerse();
  delay(1000);

  // Ejemplo: Giro sobre su propio eje a la derecha
  Giro_derecha(180);
  delay(1500);

  Detenerse();
  delay(2000);
}
