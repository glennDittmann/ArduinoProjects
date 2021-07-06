#ifndef StickShip_h
#define StickShip_h

#include "Arduino.h"
#include "SpaceShip.h"

class StickShip : private SpaceShip {
  public:
    StickShip(int cockpit_x, int cockpit_y, LedMatrix* matrixPtr, int weapon=0);
    void move(ShipArray* shipsPtr, LedMatrix* matrixPtr);
    void shoot(BulletArray* bulletsPtr, LedMatrix* matrixPtr);
    void show(Adafruit_NeoPixel* stripPtr, LedMatrix *matrixPtr);
    int getBulletAmount();

  private:
    bool moveDir;
};
#endif
