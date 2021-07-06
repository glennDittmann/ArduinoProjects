#ifndef BulletArray_h
#define BulletArray_h

#include "Arduino.h"
#include <LedMatrix.h>
#include <Adafruit_NeoPixel.h>

//macros for led matrix
#define WIDTH 15
#define HEIGHT 30

class BulletArray{

  public:

  int field[WIDTH][HEIGHT];

  BulletArray();
  void shift();
  void show(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr);
};

#endif
