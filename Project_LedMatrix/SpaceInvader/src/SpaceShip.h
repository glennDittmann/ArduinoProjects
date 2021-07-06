#ifndef SpaceShip_h
#define SpaceShip_h

#include "Arduino.h"
#include "BulletArray.h"
#include "ShipArray.h"
#include <Adafruit_NeoPixel.h>
#include <LedMatrix.h>

#define MAX_BULLETS 10

class SpaceShip{

	public:
    int cockpit_x;
    int cockpit_y;
    int weapon;

		SpaceShip(int cockpit_x, int cockpit_y, LedMatrix* matrixPtr, Adafruit_NeoPixel* stripPtr, int weapon=0);
    void move(ShipArray* shipsPtr, LedMatrix* matrixPtr);
    void hitByBullet(BulletArray* bulletsPtr);
		void shoot(BulletArray* bulletsPtr, LedMatrix* matrixPtr);
    void show(int alpha=1);
    int getBulletAmount();

	protected:
    LedMatrix* matrixPtr;
	  Adafruit_NeoPixel* stripPtr;
    int _cockpitPixelNum;
    int _bulletAmount;
    unsigned long lastShotTime;
};

#endif
