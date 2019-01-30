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

    // Override Motor returnToDefaultPostion()
    void returnToDefaultPosition() {
      step(-(this->achievedDistance % this->steps)); // Inutile de faire des tours pour rien, il suffit du décalage minimum
    }


    void run(double distance) {
      double rotations = distance / THREAD;
      double stepsToRun = round(steps * rotations);
      step(stepsToRun);
    }
};
#endif
