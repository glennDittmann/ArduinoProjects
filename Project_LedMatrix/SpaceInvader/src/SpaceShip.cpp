#include "SpaceShip.h"
#include "Arduino.h"

//macros for led matrix
#define WIDTH 15
#define HEIGHT 30

//for directions array
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define UPRIGHT 4
#define DOWNRIGHT 5
#define DOWNLEFT 6
#define UPLEFT 7

//for buttons
#define TRIGGER_PIN 3
#define BUTTONS_PIN 4
#define TRIGGER 0
#define BUTTONS 1

//for shapes
#define DEFAULT_SHAPE 0
#define STICK_SHAPE 1

#define PLAYERBULLET 1

/*shapes  
 *        _            _
 *  0:  _|_|_   ->   _|_|_
 *     |_|_|_|      |_|X|_|  X: Weapon Color
 *        _
 *  1:   |_|
 *       |_|
 *       _ _
 *  2:  |_|_|
 *      |_|_|
 *        _
 *  3:  _|_|_
 *     |_| |_|
 *        _
 *  4:  _|_|_
 *     |_|_|_|
 *       |_|
 *      _   _ 
 *  5: |_|_|_|
 *      _|_|_ 
 *     |_| |_|     
 *        _
 *  6:  _|_|_
 *     |_|_|_|
 *     |_| |_|
 *        _
 *  7:  _|_|_
 *    _|_|_|_|_
 *   |_| |_| |_|
 *       
 */

 /* shooting      
  *                  _
  *        _        |_|           _   _
  *       |_|       |_|          |_| |_|
  *       
  *        _         _              _
  *      _|_|_     _|_|_          _|_|_
  *     |_|_|_|   |_|_|_|        |_|_|_|
  */

SpaceShip::SpaceShip(int cockpit_x, int cockpit_y, LedMatrix* matrixPtr, Adafruit_NeoPixel* stripPtr, int weapon=0){
  this->cockpit_x = cockpit_x;
  this->cockpit_y = cockpit_y;
  this->matrixPtr = matrixPtr;
  this->_cockpitPixelNum = matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y);
  this->stripPtr = stripPtr;
  this->weapon = weapon;
  this->lastShotTime = millis();
}

void SpaceShip::move(ShipArray* shipsPtr, LedMatrix* matrixPtr){
  switch (matrixPtr->checkDirection()) {
    case LEFT:
      if (this->cockpit_x-1 > 0){
        this->cockpit_x--;
      }
      break;
    case RIGHT:
      if (this->cockpit_x+1 < WIDTH-1){
        this->cockpit_x++;
      }
      break;
    case UP:
      if (this->cockpit_y > 0){
        this->cockpit_y--;
      }
      break;
    case DOWN:
      if (this->cockpit_y+1 < HEIGHT-1){
        this->cockpit_y++;
      }
      break;
    case UPRIGHT:
      if (this->cockpit_x+1 < WIDTH-1 && this->cockpit_y > 0){
        this->cockpit_y--;
        this->cockpit_x++;
      }
      break;
    case DOWNRIGHT:
      if (this->cockpit_x+1 < WIDTH-1 && this->cockpit_y+1 < HEIGHT-1){
        this->cockpit_y++;
        this->cockpit_x++;
      }
      break;
    case DOWNLEFT:
      if (this->cockpit_x-1 > 0 && this->cockpit_y+1 < HEIGHT-1){
        this->cockpit_y++;
        this->cockpit_x--;
      }
      break;
    case UPLEFT:
      if (this->cockpit_x-1 > 0 && this->cockpit_y > 0){
        this->cockpit_y--;
        this->cockpit_x--;
      }
      break;
  }
  this->_cockpitPixelNum = matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y);
}

void SpaceShip::hitByBullet(BulletArray* bulletsPtr){
  if(bulletsPtr->field[this->cockpit_x][this->cockpit_y-1] == 2){
    this->stripPtr->clear();
    this->show(0.5);
    this->stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y), 200,200,0);
    this->stripPtr->show();
    delay(1000);
    asm volatile ("jmp 0");
  }else if(bulletsPtr->field[this->cockpit_x-1][this->cockpit_y] == 2){
    this->stripPtr->clear();
    this->show(0.5);
    this->stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x-1, this->cockpit_y), 200,200,0);
    this->stripPtr->show();
    delay(1000);
    asm volatile ("jmp 0");
  } else if(bulletsPtr->field[this->cockpit_x+1][this->cockpit_y] == 2){
    this->stripPtr->clear();
    this->show(0.5);
    this->stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x+1, this->cockpit_y), 200,200,0);
    this->stripPtr->show();
    delay(1000);
    asm volatile ("jmp 0");
  }
}

void SpaceShip::shoot(BulletArray* bulletsPtr, LedMatrix* matrixPtr){
  if(matrixPtr->isPressed(TRIGGER) && millis()-this->lastShotTime > 300){
    bulletsPtr->field[this->cockpit_x][this->cockpit_y] = PLAYERBULLET;
    this->lastShotTime = millis();
  }
}

void SpaceShip::show(int alpha){
   this->stripPtr->setPixelColor(this->_cockpitPixelNum, 250*alpha,250*alpha,0);
   this->stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y+1), 200*alpha,200*alpha,0);
   this->stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x+1, this->cockpit_y+1), 200*alpha,200*alpha,0);
   this->stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x-1, this->cockpit_y+1), 200*alpha,200*alpha,0);
}

int SpaceShip::getBulletAmount(){
  return this->_bulletAmount;
}
