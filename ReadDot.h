#ifndef READDOT_H
#define READDOT_H

#include "ScanImage.h"
#include <vector>

class ReadDot
{
public:
	//Image area to analyze, square
	std::vector< std::vector<int> > image;

	//Threshold to determine black-ness (0-255)
	int threshold;

	//Percentage black needed to register (0-1)
	double percentage;

	//Constructor, receives 2D vector of grayscale (0-255) pixels
	ReadDot(std::vector< std::vector<int> > img, int thres, double percent);

	//Return percentage black
	double black();

	//Return if registered
	bool check();
};

#endif