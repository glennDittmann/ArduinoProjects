#include <LedMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "SpaceShip.h"
#include "StickShip.h"
#include <Adafruit_NeoPixel.h>
#include "BulletArray.h"
#include "ShipArray.h"

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

BulletArray bullets = BulletArray();
ShipArray ships = ShipArray();

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GBR);
LedMatrix matrix(NUM_PIXELS, WIDTH, HEIGHT, &strip);

SpaceShip playerShip(7, 25, &matrix, &strip);
StickShip enemyStick(0, 5, &matrix);


void setup() {
  Serial.begin(9600);
  strip.begin();
  playerShip.show();
  enemyStick.show(&strip, &matrix);
  strip.show();


}

void loop() {
  strip.clear();

  playerShip.hitByBullet(&bullets);
  playerShip.move(&ships, &matrix);
  playerShip.shoot(&bullets, &matrix);
  playerShip.show();


  //TODO: for all enemys of enemy[?]
  enemyStick.move(&ships, &matrix);
  enemyStick.shoot(&bullets, &matrix);
  enemyStick.show(&strip, &matrix);

  bullets.shift();
  bullets.show(&strip, &matrix);

  strip.show();
  delay(map(analogRead(2), 0, 1023, 20, 200));
}
