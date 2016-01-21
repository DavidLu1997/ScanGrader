#ifndef SCANIMAGE_H
#define SCANIMAGE_H

#include "Pixel.h"
#include "Point.h"
#include <iostream>

#include <vector>

class ScanImage
{
public:
	//Creates a blank ScanImage
	ScanImage();

	//Creates a ScanImage from a filename, default 8.5x11 paper
	ScanImage(std::string name);

	//Creates a ScanImage from a filename, custom sizes
	ScanImage(std::string name, double width, double height);

	//Obtain raw image data into pixels
	bool readRawData(std::string name);

	//Obtain grayscale image
	bool readGrayScale();

	//Width of sheet in inches, default = 8.5 inches
	double widthI = 8.5;

	//Height of sheet in inches, default = 11 inches
	double heightI = 11;

	//DPI, dots (pixels per inch)
	int dpi;

	//Getter for pixels
	std::vector< std::vector<Pixel> > getPixels();

	//Getter for grayScale
	std::vector< std::vector<int> > getGrayScale();

	//Resolution
	Point resolution;

private:
	//Pixels
	std::vector< std::vector<Pixel> > pixels;

	//Grayscale
	std::vector< std::vector<int> > grayScale;
};
#endif