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

	//Return raw results
	std::vector<bool> getRawResults();

	//Return ID
	int getID();

	//Return question answers
	std::vector<int> getAnswers();

	//Return black percentages
	std::vector<double> getBlacks();

	//Write results to file, image name, all on one line
	bool writeAnswers();

	//Write results to file, custom name, all on one line
	bool writeAnswers(std::string name);

private:
	//ScanImage
	ScanImage img;

	//Image template
	ImageTemplate plate;

	//Values
	std::vector<bool> marks;

	//Blackness
	std::vector<double> blacks;

	//ID
	int id;

	//Answers, 0 to NUM_OPTIONS - 1
	std::vector<int> answers;

	//Image Name
	std::string imgName;

	//Calculated flag
	bool calculated;

	//Returns index of maximum value of a double vector within bounds
	unsigned int maxVal(std::vector <double> v, unsigned int lower, unsigned int upper);
};

#endif