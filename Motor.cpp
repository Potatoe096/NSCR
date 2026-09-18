#include <iostream> //libreria para imprimir 
using namespace std;

class motor {
    private:
        int pinAdelante;
        int pinReversa;
        int pinVelocidad; //pin PWM para modular la velocidad
        int velocidadActual; //variable para guardar la velocidad actuale entre 0 y 255
    
    public:
      void Motor(int adelante, int reversa, int velocidad) { //asignacion de pines
        pinAdelante = adelante;
        pinReversa = reversa;
        pinVelocidad = velocidad;
        velocidadActual = 0; //inicio de la velocidad en 0 pq esta detenido
      }

      void preparacion() { //preparar los pines
        cout << "Pines configurados como salida: ADELANTE =" << pinAdelante << ", REVERSA =" << pinReversa << ", VELOCIDAD =" << pinVelocidad << endl;

      }

      void avanzar(int potencia) {
        int potenciaActual = potencia; // En arduino sería algo como:
        //digitalWrite(pinAdelante, HIGH);
        //digitalWrite(pinReversa, LOW);
        //analogWrite(pinVelocidad, potencia);
        cout << "Motor [VELOCIDAD = " << pinVelocidad << "] AVANZANDO a velocidad: " << velocidadActual << endl;
      }

};