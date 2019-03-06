#ifndef TRANSLATIONMOTOR_H
#define TRANSLATIONMOTOR_H

#define THREAD 3
#include "Motor.h"

class TranslationMotor : Motor {
  public:
    int steps;
    int pin1;
    int pin2;

    TranslationMotor(int sp, int p1, int p2) : Motor(sp, p1, p2) {
      steps = sp;
    }
/*
    // Override Motor returnToDefaultPostion()
    void returnToDefaultPosition() {
      this->step(-(this->achievedDistance % this->steps)); // Inutile de faire des tours pour rien, il suffit du décalage minimum
      delay(1000);
    }
    
    void run(double distance) {
      Serial.print("mos30");
      delay(100);
      double rotations = distance / THREAD;
      double stepsToRun = round(steps * rotations);
      Serial.print("mos40");
      delay(100);
      this->step(stepsToRun);
      Serial.print("mos50");
      delay(100);
      delay(1000);
    }
    */
};
#endif
