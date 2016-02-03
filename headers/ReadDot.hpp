//ReadDot class
//Checks darkness of a rectangle given an image
//Reduces memory allocation

#ifndef READDOT_H
#define READDOT_H

#include "ScanImage.hpp"
#include "Rectangle.hpp"
#include <vector>

class ReadDot
{
public:
	//Constructor, receives 2D vector of grayscale (0-255) pixels
	ReadDot(ScanImage img, int thresh);

	//Return percentage black of a rectangle
	double black(Rectangle rect);

private:
	//ScanImage
	ScanImage image;

	//grayScale pixels
	std::vector< std::vector<int> > grayPixels;

	//Threshold needed to add to image
	int threshold;
};

#endif