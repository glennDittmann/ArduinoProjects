//#include <string>
#include <Adafruit_NeoPixel.h>
#include <Led_Matrix.h>
#include "Snake.h"

#define PIN 6
#define NUM_PIXELS 450
#define WIDTH 15
#define HEIGHT 30

#define TRIGGER 3
#define BUTTONS 4
#define ANALOG_X 0
#define ANALOG_y 1

#define NO_INPUTS 4
#define UP 1
#define DOWN 0
#define RIGHT 3
#define LEFT 2

#define START_X 10
#define START_Y 7
#define START_LEN 4 //length of tail, without head
#define MAX_TAIL_LENGTH 100

//TODO: check inputs makes mistake, e.g. we can still go left, when already going right
//TODO: Make sure the fruit can't spawn on the snake
// something like while(fruit.pos == head || tail[1] || ...) do ( fruit.pos = rand(0,499)
//TODO: start of game screen
// display game name, start message (and high score)
//TODO: end of game screen
// display game over, number of points, and restart message



class Fruit {
    int position;
    int color[3] = {0, 0, 200};

    //TODO: fruit ideas
    //ideas: move fruit und time fruit

  public:
      Fruit(){
          //do while pixel is set
          this->position = (int) random(NUM_PIXELS-1);
      }

      void resetPosition(){
          //do while pixel is set
          this->position = (int) random(NUM_PIXELS-1);
      }

      void setPixel(Adafruit_NeoPixel * strip){
          strip->setPixelColor(this->position, color[0], color[1], color[2]);
      }

      void removePixel(Adafruit_NeoPixel * strip){
          strip->setPixelColor(this->position, 0, 0, 0);
      }

      bool isEaten(Snake * snake) {
          if (snake->headPixelNum() == this->position) return true;
          return false;
      }
};

// game objects
Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GBR);
            Snake snake(START_X, START_Y, START_LEN);
            Fruit fruit;

//pointers to these objects
Adafruit_NeoPixel * stripPtr = &strip;
            Snake * snakePtr = &snake;
            Fruit * fruitPtr = &fruit;


LedMatrix matrix(NUM_PIXELS, WIDTH, HEIGHT, &strip);

unsigned int currentScore = 0;
unsigned int highScore = 0;

void effect1(int x, int y){
  strip.setPixelColor(matrix.coordsToPixelNum(x, y), 255,0,0);
  strip.show();
  delay(100);

  strip.setPixelColor(matrix.coordsToPixelNum(x, y), 0,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-1, y-1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-1, y), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-1, y+1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x, y-1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x, y+1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+1, y-1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+1, y), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+1, y+1), 255,0,0);
  strip.show();
  delay(100);

  strip.clear();

  strip.setPixelColor(matrix.coordsToPixelNum(x-2, y-2), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-2, y-1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-2, y), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-2, y+1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-2, y+2), 255,0,0);

  strip.setPixelColor(matrix.coordsToPixelNum(x-1, y-2), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x, y-2), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+1, y-2), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-1, y+2), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x, y+2), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+1, y+2), 255,0,0);

  strip.setPixelColor(matrix.coordsToPixelNum(x+2, y-2), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+2, y-1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+2, y), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+2, y+1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+2, y+2), 255,0,0);

  strip.show();
  delay(200);

  strip.clear();

  strip.setPixelColor(matrix.coordsToPixelNum(x, y), 0,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-1, y-1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-1, y), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x-1, y+1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x, y-1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x, y+1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+1, y-1), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+1, y), 255,0,0);
  strip.setPixelColor(matrix.coordsToPixelNum(x+1, y+1), 255,0,0);
  strip.show();
  delay(300);

  strip.clear();

  strip.setPixelColor(matrix.coordsToPixelNum(x, y), 255,0,0);
  strip.show();
  delay(500);

  strip.clear();

}

void resetGame(Snake* snake, Fruit* fruit, Adafruit_NeoPixel* strip, LedMatrix* matrix){
  if (currentScore > highScore) {
    effect1(7, 10);
  }

  while(!matrix->isPressed(0)){
    matrix->checkButtons();
    String strCurrentScore = String(currentScore);
    String strHighScore = String(highScore);
    matrix->drawNumber(strCurrentScore, 4, 3);
    matrix->drawNumber(strHighScore, 4, 11);
    matrix->show();
  }
  matrix->clear();
  matrix->show();
  if (currentScore > highScore) {
    highScore = currentScore;
  }
  currentScore = 0;

  snake->resetPosition();
  snake->setPixel(strip);

  fruit->resetPosition();
  fruit->setPixel(strip);
  strip->show();

}


void setup() {
    Serial.begin(9600);
    pinMode(BUTTONS, INPUT_PULLUP);
    pinMode(TRIGGER, INPUT_PULLUP);

    strip.begin();
    strip.clear();
    strip.show();
    resetGame(snakePtr, fruitPtr, stripPtr, &matrix);
    randomSeed(analogRead(0));
}


void loop() {
    snake.advance();
    snake.setPixel(stripPtr);
    if( snake.isDead() ) {
        snake.removePixel(stripPtr);
        fruit.removePixel(stripPtr);
        resetGame(snakePtr, fruitPtr, stripPtr, &matrix);
    }
    if( fruit.isEaten(snakePtr) ){
        fruit.removePixel(stripPtr);
        fruit.resetPosition();
        snake.eatFruit();
        snake.setPixel(stripPtr);
        fruit.setPixel(stripPtr);
        currentScore++;
    }

    strip.show();
    delay(map(analogRead(2), 0, 1023, 20, 200));
}
