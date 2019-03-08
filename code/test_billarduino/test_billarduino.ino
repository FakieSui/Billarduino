const int Pas = 3;
const int Dir = 2;
int i;

#include <Stepper.h>


#define ROTATION_STEPS 64
#define IN1 3
#define IN2 5
#define IN3 4


#define TRANSLATION_STEPS 200
#define DIR  6
#define STEP 7
#define IN4 2

Stepper rotation(ROTATION_STEPS, IN1, IN2, IN3, IN4);
Stepper translation(TRANSLATION_STEPS, DIR, STEP)

void setup() {
  Serial.begin(9600);
  rotation.setSpeed(15);
  translation.setSpeed(15);
}

void loop() {
  if (true) {
    int s1 = 100;
    int s2 = 1000;

    translation.step(s1);
    Serial.print("ROTATION ENDED");
    rotation.step(s2);
    Serial.print("TRANSLATION ENDED");
  }

  if (true) {
    ////////////////////////////////////
    /// Origial code from arduino.cc ///
    ////////////////////////////////////
    
    if (blocks)
    {
      i++;

      // do this (print) every 50 frames because printing every
      // frame would bog down the Arduino
      if (i % 50 == 0)
      {
        sprintf(buf, "Detected %d:\n", blocks);
        Serial.print(buf);
        for (int j = 0; j < blocks; j++)
        {
          sprintf(buf, "  block %d: ", j);
          Serial.print(buf);
          pixy.blocks[j].print();
        }
      }
    }
  }
}
