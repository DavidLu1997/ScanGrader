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
	AnalyzeImage(std::string imageName, std::string configName, double percentage);

	//Return raw results
	std::vector<double> getRawResults();

	//Return ID
	int getID();

	//Return question answers
	std::vector<int> getAnswers();

	//Write results to file, custom name
	bool writeAnswers(std::string name);

private:
	//Percentage
	double percent;

	//ScanImage
	ScanImage img;

	//Image template
	ImageTemplate plate;

	//Marks in terms of percentage black
	std::vector<double> marks;

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

	//Calculate results given percentage black needed to registered
	bool calculate();

	//Find calibration rectangles
	bool calibrate();

	//Calibrate individual
	Rectangle individual(ReadDot read, Rectangle cali);

	//Clears all vectors
	void clearAll();
};

#endif