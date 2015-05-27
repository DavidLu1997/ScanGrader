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
	//Creates a ScanImage from a filename
	ScanImage(char *name);

	//Obtain raw image data into pixels
	std::vector< std::vector<Pixel> > rawData();

	//Obtain grayscale image
	std::vector< std::vector<int> > grayScale();

private:
	//Pixels
	std::vector< std::vector<Pixel> > pixels;
};
#endif