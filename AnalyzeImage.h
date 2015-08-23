//AnalyzeImage Class
//Analyzes scanned image and returns result of each mark

#ifndef ANALYZEIMAGE_H
#define ANALYZEIMAGE_H

#include "ScanImage.h"
#include <string>
#include <vector>

class AnalyzeImage
{
public:
	//Takes in a scanned image and a data file storing parameters for the scan
	AnalyzeImage(ScanImage s, std::string filename);

	//Return results
	std::vector<int> results();

private:

	std::vector<int> marks;
};

#endif