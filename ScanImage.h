#ifndef SCANIMAGE_H
#define SCANIMAGE_H

//#include "jpeglib.h"
//#include "jerror.h"
#include "Pixel.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

class ScanImage
{
	//Source file
	char *filename;

	//Quality of JPEG
	int quality = 50;

	//Creates a ScanImage from a filename
	ScanImage(char *name);

	//Obtain raw image data into pixels
	std::vector< std::vector<Pixel> > rawData();

};
#endif