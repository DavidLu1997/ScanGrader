#include "AnalyzeImage.h"

AnalyzeImage::AnalyzeImage(std::string imageName, std::string configName) {
	//Get image
	img = ScanImage(imageName);

	//Load config file
	plate = ImageTemplate(configName);

	//Calculate scale needed;
	double xScale = 1.0, yScale = 1.0;

	xScale = (double)img.resolution.x / plate.resolution.x;
	yScale = (double)img.resolution.y / plate.resolution.y;

	//Scale config file to image
	plate.scale(xScale, yScale);
}

std::vector<int> results() {
	std::vector<int> res;

	return res;
}