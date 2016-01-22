#define _USE_MATH_DEFINES // for C++
#include "AnalyzeImage.h"
#include <cmath>

AnalyzeImage::AnalyzeImage(std::string imageName, std::string configName) {
	//Get image
	img = ScanImage(imageName);

	//Store image name
	imgName = imageName;

	//Load config file
	plate = ImageTemplate(configName);

	//Calculate scale needed;
	double xScale = 1.0, yScale = 1.0;

	//xScale = (double)img.resolution.x / plate.resolution.x;
	//yScale = (double)img.resolution.y / plate.resolution.y;

	//Scale config file to image
	plate.scale(xScale, yScale);
}

bool AnalyzeImage::calculate(int threshold, double percent) {
	//Validity check
	if (threshold <= 0 || percent <= 0) {
		std::cerr << "Invalid analysis parameters " << threshold << ", " << percent << std::endl;
		return false;
	}

	calibrate(threshold, percent);

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

Rectangle AnalyzeImage::individual(ReadDot read, Rectangle cali, int threshold, double percent) {
	if (read.black(cali) > percent) {
		return cali;
	}
	
	//Check around rectangle by increment
	//TODO: increment in GUI
	//10% of size of rectangle
	int incre = (int)(cali.size() * 0.1);

	//Courtesy of Marzbarz

	//Get center of original
	Point center = Point(abs(cali.lower.x + cali.upper.x) / 2, abs(cali.lower.y + cali.upper.y) / 2);
	
	//Get initial radius
	int radius = abs(cali.lower.x - cali.upper.x) / 10;

	//Get x side length
	int xLen = abs(cali.lower.x - cali.upper.x);

	//Get y side length
	int yLen = abs(cali.lower.y - cali.upper.y);

	//Angle to rotate in radians
	double angle = 0;

	//Current rectangle
	Rectangle cur;

	//Run through radii and angle
	for (; radius <= xLen; radius += incre) {
		for (; angle <= M_PI; angle += M_PI / 6) {
			cur.upper.x = (int)(center.x + radius * cos(angle));
			cur.upper.y = (int)(center.y + radius * sin(angle));
			cur.lower.x = cur.upper.x + xLen;
			cur.lower.y = cur.upper.y + yLen;

			if (read.black(cur) > percent) {
				return cur;
			}
		}
	}

	//No better alternative found
	return cali;
}

//Calibration squares are all black
bool AnalyzeImage::calibrate(int threshold = 200, double percent = 0.9) {
	std::vector<Rectangle> cali = plate.getCali();

	//Create ReadDot
	ReadDot read(img, threshold, percent);

	//Check each rectangle
	for (unsigned int i = 0; i < cali.size(); i++) {
		//If calibration square isn't black enough
		if (read.black(cali[i]) <= percent) {
			cali[i] = individual(read, cali[i], threshold, percent);
		}
	}

	plate.setCalibrate(cali);
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