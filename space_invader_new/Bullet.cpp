#include "Arduino.h"
#include "Led_Matrix.h"
#include <Adafruit_NeoPixel.h> 
#include "Bullet.h"

#define HEIGHT 30



Bullet::Bullet(int x=0, int y=0, int dir_x=0, int dir_y=0, bool isActive=false){
    this->x = x;
    this->y = y;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
    this->isActive = isActive;
} 

void Bullet::move(){
    this->x += this->dir_x;
    this->y += this->dir_y;
}

void Bullet::checkBounds(){
  if (this->y < 0 || this->y > HEIGHT-1){
    this->isActive = false;
  }
}

void Bullet::show(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr){
  stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->x, this->y), 0, 255, 0);
}

void Bullet::unshow(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr){
  stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->x, this->y), 0, 0, 0);
}

void Bullet::setVals(int x, int y, int dir_x, int dir_y, bool isActive){
  this->x = x;
  this->y = y;
  this->dir_x = dir_x;
  this->dir_y = dir_y;
  this->isActive = isActive;
}
