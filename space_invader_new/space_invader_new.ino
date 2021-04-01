#include <Led_Matrix.h>
#include <Adafruit_NeoPixel.h>
#include <Vector.h>
#include "Space_Ship.h"
#include <Adafruit_NeoPixel.h> 
#include "Bullet.h"

//macros for led matrix
#define PIN 6
#define NUM_PIXELS 450
#define WIDTH 15
#define HEIGHT 30


//for directions array
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

//macros for controller
#define TRIGGER 0
#define BUTTONS 1
#define ANALOG_X 0
#define ANALOG_y 1

//define for game
#define START_MAGAZINE 5



Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GBR);
LedMatrix matrix(NUM_PIXELS, WIDTH, HEIGHT);
SpaceShip playerShip(7, 25, &matrix);

void setup() {
  Serial.begin(9600);
  strip.begin();
  playerShip.show(&strip, &matrix);
  strip.show();
}

void loop() {
  strip.clear();
  
  playerShip.move(&matrix);
  playerShip.shoot(&matrix);
  playerShip.show(&strip, &matrix);

  for(int i = 0; i < playerShip.getBulletAmount(); i++){
      playerShip.bullets[i].move();
      playerShip.bullets[i].checkBounds();
      if (playerShip.bullets[i].isActive){
        playerShip.bullets[i].show(&strip, &matrix);
      }
      else{
        playerShip.bullets[i].unshow(&strip, &matrix);
      }
   }

  strip.show();
  //delay(50);
}
