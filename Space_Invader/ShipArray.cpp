#include "Arduino.h"
#include "Led_Matrix.h"
#include <Adafruit_NeoPixel.h> 
#include "ShipArray.h"

//macros for led matrix
#define WIDTH 15
#define HEIGHT 30

//for bullet types 
#define PLAYERSHIP 1
#define ENEMYSHIP 2

ShipArray::ShipArray(){
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      this->field[i][j] = 0;
    }
  }
}
