//ScanImage Class
//Loads an image and stores it in pixel form
//Converts image to grayscale if needed

#ifndef SCANIMAGE_H
#define SCANIMAGE_H

#include "Pixel.hpp"
#include "Point.hpp"
#include <iostream>
#include <QtGui\QImage>
#include <QtGui\QImageReader>
#include <QtGui\QRgb>
#include <vector>

class ScanImage
{
public:
	//Creates a blank ScanImage
	ScanImage();

	//Creates a ScanImage from a filename
	ScanImage(std::string name);

	//Obtain raw image data into pixels
	bool readRawData(std::string name);

	//Get ID
	void calculate();

	//Getter for grayScale
	std::vector< std::vector<int> > getGrayScale();

	//Resolution
	Point resolution;

	//QImage
	QImage image;

private:
	//Grayscale
	std::vector< std::vector<int> > grayScale;
};

#endif