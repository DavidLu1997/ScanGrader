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

	//Return results
	std::vector<bool> getResults();

	//Write results to file, image name
	bool writeResults();

	//Write results to file, custom name
	bool writeResults(std::string name);

private:
	//ScanImage
	ScanImage img;

	//Image template
	ImageTemplate plate;

	//Values
	std::vector<bool> marks;

	//Image Name
	std::string imgName;
};

#endif