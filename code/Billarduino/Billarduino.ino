/*
   Billarduino Main
*/

/*
   Rotation Motor
*/
#include "RotationMotor.h"

#define ROTATION_STEPS 64
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

RotationMotor rotationMotor(ROTATION_STEPS, IN1, IN2, IN3, IN4);

/*
   Translation Motor
*/
#include "TranslationMotor.h"

#define TRANSLATION_STEPS 200
#define DIR  6
#define STEP 7

TranslationMotor translationMotor(TRANSLATION_STEPS, DIR, STEP);

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
double height = 51.30; // Longeur du billard
double woodWidth = 1.25; // Epaisseur de du rebord en bois
double cushionWidth = 2.75; // Epaisseur de la bande
double border = woodWidth + cushionWidth; // Epaisseur totale
double moduleShiftX = 2;
double moduleShiftY = 4;
double stickerShift = 2.3;

double internHeight = height - 2 * border;
double internWidth = width - 2 * border;

// Billes
double ballRadius = 2.3;


#include "Scale.h"

Scale scale;



int i;
bool acquisition = false;

double centToCart;
double cartToCent;

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

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
        Serial.print("Acquisition in progress...");
        doAcquisition(blocks); // On lance le processus d'acquisition
      }
    }
  }
  prepareStrike(); // L'acquisition est réalisée, on prépare les moteurs pour le tir

}

//// BILLARDUINO API ////

void doAcquisition(uint16_t blocks) {
  Serial.print("Acquisition in progress...");
  int stickersCount = 0;

  for (int j = 0; j < blocks; j++) {
    String name = "";
    Block block = pixy.blocks[j];
    switch (block.signature) {
      case 1: // Bille 1
        name = "Bille 1";
        balls[0] = Point(block.x - origin.x, block.y - origin.y);
        break;
      case 2: // Bille 2
        name = "Bille 2";
        balls[1] = Point(block.x - origin.x, block.y - origin.y);
        break;
      case 3: // sticker [1 ou 2]
        stickers[stickersCount] = Point(block.x, block.y);
        stickersCount++;
        name = "Stickers " + stickersCount;
        break;
    }
    if (name != "") {
      Serial.print(name);
      Serial.print(" at x: ");
      Serial.print(block.x - origin.x);
      Serial.print(", y: ");
      Serial.println(block.y - origin.y);
    } else {
      Serial.print("Error during acqusition! Are there all the elements required?");
    }
  }
  if (stickersCount == 2 and balls[0].isDefined() and balls[1].isDefined()) { // Vérifions si on a bien repéré les deux billes et les deux stickers pour valider l'acquisition
    reorderStickers(); // On réordonne l'ordre des stickers
    defineScale();
    defineOrigin();
    acquisition = true; // On termine la phase d'acquisition (tout s'est bien passé)
    Serial.print("Acquisition done!");
  }
}

void prepareStrike() {
  /*
     Defining holes positions
  */
  Point firstHole = Point(origin.x + centimeterToCartesian(border), origin.y + centimeterToCartesian(border));
  Point secondHole = Point(origin.x + centimeterToCartesian(width - border), origin.y + centimeterToCartesian(border));
  /*
     Determine which hole to aim
  */

  Point aimedHole;
  if (balls[0].x < balls[1].x) {
    aimedHole = firstHole;
  } else {
    aimedHole = secondHole;
  }

  /*
     Determine GhostBall position
  */
  Point ghostBall = Point((balls[0].x - aimedHole.x) * 2 * cartesianToCentimeter(ballRadius) / aimedHole.distanceTo(balls[0]),
                          (balls[0].y - aimedHole.y) * 2 * cartesianToCentimeter(ballRadius) / aimedHole.distanceTo(balls[0]));

  /*
     Determine cartesian position of the module
  */

  Point moduleOrigin = Point(origin.x - cartesianToCentimeter(moduleShiftX), origin.y + cartesianToCentimeter(moduleShiftY));

  double phi = atan((ghostBall.x - balls[1].x) / (ghostBall.y - balls[1].y));
  double l = centimeterToCartesian(tan(phi)*(moduleOrigin.y-ghostBall.y));

  translationMotor.run(centimeterToCartesian(l));
  rotationMotor.run(phi);

}

void reorderStickers() {
  if (stickers[0].x > stickers[1].x) {
    Point tmp = stickers[0];
    stickers[0] = stickers[1];
    stickers[1] = tmp;
  }
}

void defineScale() {
  x1 = stickers[0].x + stickerShift;
  x2 = stickers[1].x + stickerShift;
  y1 = stickers[0].y + stickerShift;
  y2 = stickers[1].y + stickerShift;
  scale.setPoints(Point(x1, y1), Point(x2, y2));
}

void defineOrigin() {
  origin.setPosition(stickers[0].x- + centimeterToCartesian(stickerShift), stickers[0].y + centimeterToCartesian(stickerShift));
}

double centimeterToCartesian(double d) {
  if (acquisition) {
    return d * centToCart;
  } else {
    Serial.print("Error: Please acquisitionate first!");
    exit(0);
  }
}

double cartesianToCentimeter(double d) {
  if (acquisition) {
    return d * cartToCent;
  } else {
    Serial.print("Error: Please acquisitionate first!");
    exit(0);
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
