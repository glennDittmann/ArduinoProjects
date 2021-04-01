#ifndef Bullet_h
#define Bullet_h

#include "Arduino.h"
#include "Led_Matrix.h"
#include <Adafruit_NeoPixel.h> 

class Bullet{

  public:
  
  int x;
  int y;
  int dir_x;
  int dir_y;
  bool isActive;
  
  Bullet(int x=0, int y=0, int dir_x=0, int dir_y=0, bool isActive=false);
  void move();
  void show(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr);
  void unshow(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr);
  void checkBounds();
  void setVals(int x, int y, int dir_x, int dir_y, bool isActive);
};

#endif
