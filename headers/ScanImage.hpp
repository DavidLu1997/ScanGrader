//ScanImage Class
//Loads an image and stores it in pixel form
//Converts image to grayscale if needed

#ifndef SCANIMAGE_H
#define SCANIMAGE_H

//Visual Studio warning suppression
#if defined(_MSC_VER) && _MSC_VER >= 1400 
#pragma warning(push) 
#pragma warning(disable:4996) 
#endif 

#include "Pixel.hpp"
#include "Point.hpp"
#include <iostream>

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

	//Obtain grayscale image
	bool readGrayScale();

	//Getter for pixels
	std::vector< std::vector<Pixel> > getPixels();

	//Get ID
	int getID();

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

//Visual Studio warning suppression
#if defined(_MSC_VER) && _MSC_VER >= 1400 
#pragma warning(pop) 
#endif 

#endif