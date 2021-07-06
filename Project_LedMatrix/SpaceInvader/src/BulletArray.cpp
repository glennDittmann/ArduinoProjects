#include "Arduino.h"
#include <LedMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "BulletArray.h"

//macros for led matrix
#define WIDTH 15
#define HEIGHT 30

//for bullet types
#define PLAYERBULLET 1
#define ENEMYBULLET 2

BulletArray::BulletArray(){
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      this->field[i][j] = 0;
    }
  }
}

void BulletArray::shift(){
  // loop for bullets going upwards
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      if(this->field[i][j] == PLAYERBULLET && j > 0){
        this->field[i][j-1] = PLAYERBULLET;
        this->field[i][j] = 0;
      }
      if((j == 0 || j==HEIGHT-1) && (this->field[i][j] != 0)){ // check out of y bounds -> delete bullet
        this->field[i][j] = 0;
      }
    }
  }

  //loop for bullets going downwards
  for(int i = 0; i < WIDTH; i++){
    for(int j = HEIGHT; j > 0; j--){
      if(this->field[i][j] == ENEMYBULLET && j > 0){
        this->field[i][j+1] = ENEMYBULLET;
        this->field[i][j] = 0;
      }
      if((j == 0 || j==HEIGHT-1) && (this->field[i][j] != 0)){ // check out of y bounds -> delete bullet
        this->field[i][j] = 0;
      }
    }
  }
}



void BulletArray::show(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr){
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      if(this->field[i][j] != 0 && j >= 0){
        if(this->field[i][j] == PLAYERBULLET){
          stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(i, j), 0, 255, 0);
        }
        else if(this->field[i][j] == ENEMYBULLET){
          stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(i, j), 0, 0, 100);
        }
      }
    }
  }
}
