/*
   Billarduino Main
*/

boolean debug = true;

/*
   Rotation Motor
*/
#include "RotationMotor.h"

#define ROTATION_STEPS 64
#define IN1 3
#define IN2 5
#define IN3 4
#define IN4 2

// RotationMotor rotationMotor(ROTATION_STEPS, IN1, IN2, IN3, IN4);

Stepper rotationMotor(ROTATION_STEPS, IN1, IN2, IN3, IN4);

/*
   Translation Motor
*/
#define THREAD 0.128
#include "TranslationMotor.h"

#define TRANSLATION_STEPS 200
#define DIR  6
#define STEP 7

// TranslationMotor translationMotor(TRANSLATION_STEPS, DIR, STEP);
//Stepper translationMotor(TRANSLATION_STEPS, DIR, STEP);

/*
   PixyCam
*/
#include "SPI.h"
#include "Pixy.h"

Pixy pixy;


#include "Point.h"

Point stickers[2]; // Initialisation des points de l'échelle
Point balls[2]; // Initialisation de la liste des billes
Point origin;

/*
   Dimensions (in cm)
*/

// Billard
double width = 31.55; // Largeur du billard
double height = 51.30; // doubleeur du billard
double woodWidth = 1.25; // Epaisseur de du rebord en bois
double cushionWidth = 2.75; // Epaisseur de la bande
double border = woodWidth + cushionWidth; // Epaisseur totale
double holeShift = 4.8; // Décalage du trou
double moduleShiftX = 2.6; // Position d'origine du module en X
double moduleShiftY = 3; // Position d'origine du module en Y
double stickerShift = 2.4; // Décallage du centre de la gomette par rapport à l'angle

double internHeight = height - 2 * border; // Largeur interne
double internWidth = width - 2 * border; // Largeur externe

// Billes
double ballRadius = 2.4 / 2;


#include "Scale.h"

Scale scale;



int i;
bool acquisition = false;

double centToCart;
double cartToCent;

void setup()
{
  Serial.begin(19200);
  Serial.println("Starting...");

  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  //  translationMotor.setSpeed(500);
  rotationMotor.setSpeed(20);

  pixy.init(); // Initialisation de la PixyCam
}

void loop()
{
  while (!acquisition) {
    uint16_t blocks;
    blocks = pixy.getBlocks(4);
    if (blocks == 4) { // Nous avons probablement détecté les deux billes et et les deux stickers
      i++;
      if (i % 25 == 0) {
        Serial.println("Acquisition in progress...");
        doAcquisition(blocks); // On lance le processus d'acquisition
      }
    }
  }
  prepareStrike(); // L'acquisition est réalisée, on prépare les moteurs pour le tir

}

//// BILLARDUINO API ////

void doAcquisition(uint16_t blocks) {
  Serial.println("Acquisition in progress...");
  delay(100);
  int stickersCount = 0;

  for (int j = 0; j < blocks; j++) {
    delay(100);
    String name = "";
    Block block = pixy.blocks[j];
    switch (block.signature) {
      case 1: // Bille 1
        name = "Bille 1";
        balls[0] = Point(block.x, block.y);
        break;
      case 2: // Bille 2
        name = "Bille 2";
        balls[1] = Point(block.x , block.y);
        break;
      case 3: // sticker [1 ou 2]
        stickers[stickersCount] = Point(block.x, block.y);
        stickersCount++;
        //        name = "Stickers " + stickersCount;
        name = "Stickers";
        break;
    }
    if (name != "") {
      Serial.print(name);
      delay(100);
      Serial.print(" at x: ");
      delay(100);
      Serial.print(block.x);
      delay(100);
      Serial.print(", y: ");
      delay(100);
      Serial.println(block.y);
      delay(100);
    } else {
      Serial.println("Error during acqusition! Are there all the elements required?");
      delay(100);
    }
  }

  if (stickersCount == 2 and balls[0].isDefined() and balls[1].isDefined()) { // Vérifions si on a bien repéré les deux billes et les deux stickers pour valider l'acquisition

    reorderStickers(); // On réordonne l'ordre des stickers
    defineScale();
    acquisition = true; // On termine la phase d'acquisition (tout s'est bien passé)
    defineOrigin();
    Serial.println("Acquisition done!");
    delay(100);
  }
}

void prepareStrike() {

  Serial.print("scale: ");
  delay(100);
  Serial.println(scale.getDistance());
  delay(100);
  Serial.println(centimeterToCartesian(56.45));
  delay(100);



  /*
     Defining holes positions
  */
  Point firstHole = Point(origin.x + centimeterToCartesian(holeShift), origin.y + centimeterToCartesian(holeShift));
  Point secondHole = Point(origin.x + centimeterToCartesian(holeShift), origin.y + centimeterToCartesian(width - holeShift));

  Serial.println("firstHole");
  delay(100);
  firstHole.toString();

  Serial.println("secondHole");
  delay(100);
  secondHole.toString();

  /*
     Determine which hole to aim
  */

  Point aimedHole;
  if (balls[0].y > balls[1].y) {
    aimedHole = firstHole;
  } else {
    aimedHole = secondHole;
  }

  Serial.println("aimedHole");
  delay(100);
  aimedHole.toString();

  /*
     Determine GhostBall position
  */
  Point ghostBall = Point(aimedHole.x + (balls[1].x - aimedHole.x) * (1 + centimeterToCartesian(ballRadius)*2 / aimedHole.distanceTo(balls[1])),
                          aimedHole.y + (balls[1].y - aimedHole.y) * (1 + centimeterToCartesian(ballRadius)*2 / aimedHole.distanceTo(balls[1])));


  Serial.println("ghostBall");
  delay(100);
  ghostBall.toString();

  /*
     Determine cartesian position of the module
  */

  Point moduleOrigin = Point(origin.x + centimeterToCartesian(width + moduleShiftX), origin.y - centimeterToCartesian(moduleShiftY));
  delay(100);


  Serial.println("moduleOrigin");
  delay(100);
  moduleOrigin.toString();
  
  double rapport = (double) ((double) (balls[0].y - ghostBall.y) / (double) (balls[0].x - ghostBall.x));

  double phi = atan(rapport);
  double l = cartesianToCentimeter(ghostBall.y + tan(phi) * (centimeterToCartesian(height + moduleShiftX) - ghostBall.x));


  Serial.print("l: ");
  delay(100);
  Serial.println(l);
  delay(100);
  Serial.print("phi: ");
  delay(100);
  Serial.println(phi);
  delay(100);


  // TRANSLATION //
  double rotations = l / THREAD;
  double transStepsToRun = -abs(round(TRANSLATION_STEPS * rotations));

  Serial.print("Translation: ");
  delay(100);
  Serial.println(transStepsToRun);
  delay(100);

  translateSteps(transStepsToRun);

  delay(1000);

  // ROTATION //

  double radianAngle = phi;
  double rotStepsToRun = -abs(round(radianAngle * ROTATION_STEPS / 2 * PI)); // Règle de trois pour savoir combien de pas parcourir pour un angle en radian donné
  rotationMotor.step(rotStepsToRun);

  Serial.print("Rotation: ");
  delay(100);
  Serial.println(rotStepsToRun);
  delay(100);

  delay(10000);

  rotationMotor.step(-rotStepsToRun);
  translateSteps(-transStepsToRun);
  //  translationMotor.step(-transStepsToRun);

  // translationMotor.returnToDefaultPosition();
  // rotationMotor.returnToDefaultPosition();
  delay(10000);
}

void reorderStickers() {
  if (stickers[0].x > stickers[1].x) {
    Point tmp = stickers[0];
    stickers[0] = stickers[1];
    stickers[1] = tmp;
  }
}

void defineScale() {
  double x1 = stickers[0].x;
  double x2 = stickers[1].x;
  double y1 = stickers[0].y;
  double y2 = stickers[1].y;
  scale.setPoints(Point(x1, y1), Point(x2, y2));
  centToCart = scale.getCentToCart();
  cartToCent = scale.getCartToCent();
}

void defineOrigin() {
  double x = stickers[0].x - centimeterToCartesian(stickerShift);
  double y = stickers[0].y - centimeterToCartesian(stickerShift);
  origin.setPosition(x, y);
}


double centimeterToCartesian(double d) {
  if (acquisition) {
    return d * centToCart;
  } else {
    Serial.print("Error: Please acquisitionate first!");
  }
}

double cartesianToCentimeter(double d) {
  if (acquisition) {
    return d * cartToCent;
  } else {
    Serial.print("Error: Please acquisitionate first!");
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



///// Commentaries ///////

/*
  static int i = 0;
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
    if (i % 50 == 0) {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (int j = 0; j < blocks; j++) {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf);
        pixy.blocks[j].print();
      }
    }
  }
*/
