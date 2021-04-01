#ifndef Space_Ship_h
#define Space_Ship_h	

#include "Arduino.h"
#include "Bullet.h"
#include <Vector.h>
#include <Adafruit_NeoPixel.h>
#include <Led_Matrix.h>

#define MAX_BULLETS 20

class SpaceShip{

	public:
    int cockpit_x;
    int cockpit_y;
		Bullet bullets[MAX_BULLETS];
   
		SpaceShip(int cockpit_x, int cockpit_y, LedMatrix* matrixPtr);
    void move(LedMatrix* matrixPtr);
		void shoot(LedMatrix* matrixPtr);
    void show(Adafruit_NeoPixel* stripPtr, LedMatrix *matrixPtr);
    int getBulletAmount();

	private:
    int _cockpitPixelNum;
    int _bulletAmount;
};

#endif
