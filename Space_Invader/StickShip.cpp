#include "Arduino.h"
#include "StickShip.h"


#define ENEMYBULLET 2

StickShip::StickShip(int cockpit_x, int cockpit_y, LedMatrix* matrixPtr, int weapon=0): SpaceShip(cockpit_x, cockpit_y, matrixPtr, weapon){
  this->moveDir = true;
}

void StickShip::move(ShipArray* shipsPtr, LedMatrix* matrixPtr){
  if (this->moveDir) { //move right
    if (this->cockpit_x < 15){
      this->cockpit_x ++;
    }
    if (this->cockpit_x == 15){ // reached right end of screen
      //this->cockpit_x --;
      this->moveDir = false; //move one left and set movement status to left
    }
  }
  if (!this->moveDir) { //move left
    if (this->cockpit_x > 0){
      this->cockpit_x --;
    }
    if (this->cockpit_x == 0){ // reached left end of screen
      //this->cockpit_x ++;
      this->moveDir = true; //move one right and set movement status to right
    }
  }
  this->_cockpitPixelNum = matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y);
}

void StickShip::shoot(BulletArray* bulletsPtr, LedMatrix* matrixPtr){
  if( millis()-this->lastShotTime > 300 ){
    bulletsPtr->field[this->cockpit_x][this->cockpit_y] = ENEMYBULLET;
    this->lastShotTime = millis();
  }
}

void StickShip::show(Adafruit_NeoPixel* stripPtr, LedMatrix *matrixPtr){
  stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y), 0,0,250);
  stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y+1), 0,0,200);
}
