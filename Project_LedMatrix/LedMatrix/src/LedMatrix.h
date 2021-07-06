/*
	lead_matrix.h - Library for the led matrix which
	inlcudes mapping (x,y) coordinates to the corresponding
	pixel number of an adafruitNeoPixel led strip as well as
	checking the inputs of the controller.
*/
#ifndef LedMatrix_h
#define LedMatrix_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class LedMatrix{

	public:
		LedMatrix(int numPixels, int width, int height, Adafruit_NeoPixel* stripPtr);
		void begin();
		void show();
		void clear();
		int coordsToPixelNum(int x, int y);
		void drawDigit(int digit, int x, int y, int alpha=1);
		void drawNumber(String number, int x, int y, int alpha=1);
		void checkInputs();
		int checkDirection();
		void checkButtons();
		bool isPressed(int button);

	protected:
		Adafruit_NeoPixel* stripPtr;

	private:
		int _numPixels;
		int _width;
		int _height;

		int _directions[9];
		bool _buttons[2];

		void _draw0(int x, int y, int alpha=1);
		void _draw1(int x, int y, int alpha=1);
		void _draw2(int x, int y, int alpha=1);
		void _draw3(int x, int y, int alpha=1);
		void _draw4(int x, int y, int alpha=1);
		void _draw5(int x, int y, int alpha=1);
		void _draw6(int x, int y, int alpha=1);
		void _draw7(int x, int y, int alpha=1);
		void _draw8(int x, int y, int alpha=1);
		void _draw9(int x, int y, int alpha=1);

		void _drawA(int x, int y, int alpha=1);
		void _drawB(int x, int y, int alpha=1);
		// ...
		void _drawY(int x, int y, int alpha=1);
		void _drawZ(int x, int y, int alpha=1);

};


#endif
