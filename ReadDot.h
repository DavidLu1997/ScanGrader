#ifndef READDOT_H
#define READDOT_H

#include "ScanImage.h"
#include "Rectangle.h"
#include <vector>

class ReadDot
{
public:
	//Constructor, receives 2D vector of grayscale (0-255) pixels
	ReadDot(ScanImage img, double percent);

	//Return percentage black of a rectangle
	double black(Rectangle rect);

	//Return if registered in rect
	bool check(Rectangle rect);

private:
	//ScanImage
	ScanImage image;

	//grayScale pixels
	std::vector< std::vector<int> > grayPixels;

	//Percentage black needed to register (0-1)
	double percentage;
};

#endif