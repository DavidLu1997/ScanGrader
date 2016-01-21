#include "AnalyzeImage.h"

AnalyzeImage::AnalyzeImage(std::string imageName, std::string configName) {
	//Get image
	img = ScanImage(imageName);

	//Store image name
	imgName = imageName;

	//Load config file
	plate = ImageTemplate(configName);

	//Calculate scale needed;
	double xScale = 1.0, yScale = 1.0;

	xScale = (double)img.resolution.x / plate.resolution.x;
	yScale = (double)img.resolution.y / plate.resolution.y;

	//Scale config file to image
	plate.scale(xScale, yScale);
}

bool AnalyzeImage::calculate(int threshold, double percent) {
	//Validity check
	if (threshold <= 0 || percent <= 0) {
		std::cerr << "Invalid analyze parameters." << std::endl;
		return false;
	}

	//Clear marks
	marks.clear();

	//Initialize ReadDot
	ReadDot read(img, threshold, percent);
	
	//Go through rectangles
	for (unsigned int i = 0; i < plate.getRects().size(); i++) {
		marks.push_back(read.check(plate.getRects().at(i)));
	}

	return true;
}

std::vector<bool> AnalyzeImage::getResults() {
	return marks;
}

bool AnalyzeImage::writeResults() {
	return writeResults(imgName);
}

bool AnalyzeImage::writeResults(std::string name) {

	std::ofstream out(name.c_str(), std::ios::out);

	for (unsigned int i = 0; i < marks.size(); i++) {
		out << marks[i] << std::endl;
	}

	out.close();
	return true;
}