#include <iostream> //libreria para imprimir 
using namespace std;

class motor {
    private:
        int pinIn1; // pin digital
        int pinIn2;
        int pinPWM; //pin PWM para modular la velocidad
        int velocidadActual; //variable para guardar la velocidad actuale entre 0 y 255
    
    public:
      motor(int in1, int in2, int pmw) { //asignacion de pines
        pinIn1 = in1; // asignacion del pin de entrada 1
        pinIn2 = in2; // '' 2
        pinPMW = pmw; // '' del pin PWM
        velocidadActual = 0; //inicio de la velocidad en 0 pq esta detenido
      }

      void inicializar() { //preparar los pines
        cout << "Pin configurado: IN1=" << pinIn1 << ", IN2=" << pinIn2 << ", PWM=" << pinPWM << endl;

      }

      void avanzar(int velocidad) { //actualizacion del valor de velocidad
        velocidadActual = velocidad; // En arduino sería algo como:
        //digitalWrite(pinIn1, HIGH);
        //digitalWrite(pinIn2, LOW);
        //analogWrite(pinPWM, velocidad);
        cout << " Motor [PWM= " << pinPWM << "] AVANZANDO a velocidad: " << velocidadActual << endl;
      }

      void retroceder(int velocidad) {
        velocidadActual = velocidad;
        cout << " Motor [PWM=" << pinPWM << "] RETROCEDIENDO a velocidad: " << velocidadActual << endl;
      }

      void detener() {
        velocidadActual = 0;
        cout << " Motor [PWM" << pinPWM << "] FRENADO " << endl;
      }
};

class DriverLado {
  private:
    motor motorFrontal; 
    motor motorTrasero;

  public:
    DriverLado(int fIn1, int fIn2, int fPwm, int tIn1, int tIn2, int tPWm)
      : motorFrontal(fIn1, fIn2, fPwm), motorTrasero(tIn1, tIn2, tPwn){}

    void inicializar(){
      motorFrontal.inicializar();
      motorTrasero.inicializar();
    }

    void avanzar(int velocidad) {
      motorFrontal.avanzar(velocidad);
      motorTrasero.avanzar
    }
}