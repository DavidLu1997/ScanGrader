#ifndef SCANIMAGE_H
#define SCANIMAGE_H

#include "Pixel.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

class ScanImage
{
public:
	//Creates a ScanImage from a filename, default 8.5x11 paper
	ScanImage(char *name);

	//Creates a ScanImage from a filename, custom sizes
	ScanImage(char *name, double width, double length);

	//Obtain raw image data into pixels
	std::vector< std::vector<Pixel> > rawData();

	//Obtain grayscale image
	std::vector< std::vector<int> > grayScale();

	//Width of sheet in inches, default = 8.5 inches
	double widthI = 8.5;

	//Height of sheet in inches, default = 11 inches
	double heightI = 11;

	//DPI, dots (pixels per inch)
	int dpi;

private:
	//Pixels
	std::vector< std::vector<Pixel> > pixels;
};
#endif