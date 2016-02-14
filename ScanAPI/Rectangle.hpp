//Rectangle class
//Stores a rectangle as two points
//Upper left corner and lower right corner

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cmath>
#include "Point.hpp"

class Rectangle {
public:
	//Storage
	Point upper, lower;
	
	//Reference ID, which calibration rectangle
	int id;

	//Creates a rectangle of size 0
	Rectangle() {
		upper.x = 0;
		upper.y = 0;
		lower.x = 0;
		lower.y = 0;
	}

	//Creates a rectangle from 2 points
	Rectangle(Point a, Point b, int ID = -1) {
		upper = a;
		lower = b;
		id = ID;
	}

	//Get size of rectangle
	int size() {
		return abs(lower.x - upper.x) * abs(lower.y - upper.y);
	}
};

#endif