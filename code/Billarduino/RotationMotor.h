#ifndef ROTATIONMOTOR_H
#define ROTATIONMOTOR_H
#include "Motor.h"

class RotationMotor : Motor {
  public:
    int steps;
    int pin1;
    int pin2;
    int pin3;
    int pin4;

    RotationMotor(int sp, int p1, int p2, int p3, int p4) : Motor(sp, p1, p2, p3, p4) {
      steps = sp;
    }

    void run(double angle) {
      double radianAngle = round(angle) % round(2 * PI);
      double stepsToRun = round(radianAngle * this->steps / 2 * PI); // Règle de trois pour savoir combien de pas parcourir pour un angle en radian donné
      this->step(stepsToRun);
    }

    // Override Motor returnToDefaultPostion()
    void returnToDefaultPosition() {
      step(-(this->achievedDistance % this->steps)); // Inutile de faire des tours pour rien, il suffit du décalage minimum
    }
};
#endif
