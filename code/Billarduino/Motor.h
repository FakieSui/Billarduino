#ifndef MOTOR_H
#define MOTOR_H
#include "Stepper.h"

class Motor : Stepper {
  public:
    int achievedDistance = 0;

    Motor(int sp, int p1, int p2, int p3, int p4) : Stepper(sp, p1, p2, p3, p4) {
      int steps = sp;
      int pin1 = p1;
      int pin2 = p2;
      int pin3 = p3;
      int pin4 = p4;
    }

    Motor(int sp, int p1, int p2) : Stepper(sp, p1, p2) {
      int steps = sp;
      int pin1 = p1;
      int pin2 = p2;
    }
    // Override Stepper step(int steps)
    void step(int steps) {
      step(steps);
      this->achievedDistance += steps;
    }

    void returnToDefaultPosition() {
      step(-this->achievedDistance);
    }
};
#endif
