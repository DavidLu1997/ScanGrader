//AnalyzeImage Class
//Analyzes scanned image and returns result of each mark

#ifndef ANALYZEIMAGE_H
#define ANALYZEIMAGE_H

#include "ScanImage.h"
#include "ImageTemplate.h"
#include "ReadDot.h"
#include <string>
#include <vector>
#include <fstream>

class AnalyzeImage
{
public:
	//Takes in an image name and a data file storing parameters for the scan
	AnalyzeImage(std::string imageName, std::string configName);

	//Calculate results given blackness threshold and percentage black needed to registered
	bool calculate(int threshold, double percent);

	//Find calibration rectangles
	bool calibrate(int threshold, double percent);

	//Calibrate individual
	Rectangle individual(ReadDot read, Rectangle cali, int threshold, double percent);

	//Return results
	std::vector<bool> getResults();

	//Return black percent
	std::vector<double> getBlacks();

	//Write results to file, image name, all on one line
	bool writeResults();

	//Write results to file, custom name, all on one line
	bool writeResults(std::string name);

	//Write results to file, image name, custom line size
	bool writeResults(int n);

	//Write results to file, custom name and line size
	bool writeResults(std::string name, int n);

private:
	//ScanImage
	ScanImage img;

	//Image template
	ImageTemplate plate;

	//Values
	std::vector<bool> marks;

	//Blackness
	std::vector<double> blacks;

	//Image Name
	std::string imgName;
};

#endif