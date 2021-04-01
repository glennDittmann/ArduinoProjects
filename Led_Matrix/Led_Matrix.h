/*
	lead_matrix.h - Library for the led matrix which
	inlcudes mapping (x,y) coordinates to the corresponding 
	pixel number of an adafruitNeoPixel led strip as well as
	checking the inputs of the controller.
*/
#ifndef Led_Matrix_h
#define Led_Matrix_h

#include "Arduino.h"


class LedMatrix{

	public:
		LedMatrix(int numPixels, int width, int height);		
		int coordsToPixelNum(int x, int y);
		void checkInputs();
		int checkDirection();
		void checkButtons();
		bool isPressed(int button);

	private:
		int _numPixels;
		int _width;
		int _height;

		int _directions[5];
		bool _buttons[2];

};


#endif