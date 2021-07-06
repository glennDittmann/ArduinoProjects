#ifndef ShipArray_h
#define ShipArray_h

#include "Arduino.h"
#include <LedMatrix.h>
#include <Adafruit_NeoPixel.h>

//macros for led matrix
#define WIDTH 15
#define HEIGHT 30

class ShipArray{

  public:

  int field[WIDTH][HEIGHT];

  ShipArray();
  void show(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr);
};

#endif
