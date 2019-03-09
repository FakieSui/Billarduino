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

void setup() {
  Serial.begin(9600);
  rotation.setSpeed(15);
}

void loop() {
  if (true) {
    int s1 = 100;
    int s2 = 1000;

    translateSteps(s1);
    Serial.print("ROTATION ENDED");
    rotation.step(s2);
    Serial.print("TRANSLATION ENDED");
  }

  if (true) {
    ////////////////////////////////////
    /// Origial code from arduino.cc ///
    ////////////////////////////////////
    static int i = 0;
    int j;
    uint16_t blocks;
    char buf[32];

    // grab blocks!
    blocks = pixy.getBlocks();

    // If there are detect blocks, print them!
    if (blocks)
    {
      i++;

      // do this (print) every 50 frames because printing every
      // frame would bog down the Arduino
      if (i % 50 == 0)
      {
        sprintf(buf, "Detected %d:\n", blocks);
        Serial.print(buf);
        for (j = 0; j < blocks; j++)
        {
          sprintf(buf, "  block %d: ", j);
          Serial.print(buf);
          pixy.blocks[j].print();
        }
      }
    }
  }
}

// Need this method for translation as Stepper.step runs until a limited maximum value
void translateSteps(long steps) {
  if (steps > 0) {
    digitalWrite(DIR, HIGH);
  } else {
    digitalWrite(DIR, LOW);
  }
  for (long x = 0; x < abs(steps); x++) {
    digitalWrite(STEP, LOW);
    delayMicroseconds(800);
    digitalWrite(STEP, HIGH);
    delayMicroseconds(800);
  }
}
