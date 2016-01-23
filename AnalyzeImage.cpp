#define _USE_MATH_DEFINES
#include "AnalyzeImage.h"
#include <cmath>
#include <algorithm>

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

	std::cout << "Scaling needed (x, y): ("<< xScale << ", " << yScale << ")" << std::endl;

	//Scale config file to image
	plate.scale(xScale, yScale);
	calculated = false;
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

	//Clear blacks
	blacks.clear();

	//Initialize ReadDot
	ReadDot read(img, threshold, percent);
	
	//Go through rectangles
	for (unsigned int i = 0; i < plate.getRects().size(); i++) {
		marks.push_back(read.check(plate.getRects().at(i)));
		blacks.push_back(read.black(plate.getRects().at(i)));
	}

	//Get answers
	getAnswers();

	//Get ID
	getID();

	calculated = true;
	return true;
}

Rectangle AnalyzeImage::individual(ReadDot read, Rectangle cali, int threshold, double percent) {
	if (read.black(cali) > percent) {
		return cali;
	}
	
	//Check around rectangle by increment

	//Get center of original
	Point center = Point(abs(cali.lower.x + cali.upper.x) / 2, abs(cali.lower.y + cali.upper.y) / 2);
	
	//Get initial radius
	int radius = abs(cali.lower.x - cali.upper.x) / 10;

	//Get x side length
	int xLen = abs(cali.lower.x - cali.upper.x);

	//Get y side length
	int yLen = abs(cali.lower.y - cali.upper.y);

	//TODO: increment in GUI
	//10% of x length of rectangle
	int incre = (int)(xLen * 0.1);

	//Angle to rotate in radians
	double angle = 0;

	//Current rectangle
	Rectangle cur = cali;

	//Run through radii and angle
	for (; read.black(cur) <= percent; radius += incre) {
		for (; angle <= 2*M_PI; angle += M_PI / 6) {
			cur.upper.x = (int)(center.x + radius * cos(angle));
			cur.upper.y = (int)(center.y + radius * sin(angle));
			cur.lower.x = cur.upper.x + xLen;
			cur.lower.y = cur.upper.y + yLen;

			if (read.black(cur) > percent) {
				return cur;
			}
		}
		angle = 0;
	}

	//No better alternative found
	return cali;
}

//Calibration squares are all black
bool AnalyzeImage::calibrate(int threshold, double percent) {
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

std::vector<int> AnalyzeImage::getAnswers() {

	if (!calculated) {
		answers.clear();
		//Check answers every option
		if (plate.questions.x < 0 || plate.questions.x >= blacks.size() || plate.questions.y < 0 || plate.questions.y >= blacks.size()) {
			std::cerr << "Invalid bounds for answers." << std::endl;
		}
		else {
			for (int i = plate.questions.x; i < plate.questions.y; i += plate.options) {
				answers.push_back((maxVal(blacks, i, i + plate.options) % plate.options) + 1);
			}
		}
	}
	return answers;
}

std::vector<bool> AnalyzeImage::getRawResults() {
	return marks;
}

std::vector<double> AnalyzeImage::getBlacks() {
	return blacks;
}

bool AnalyzeImage::writeAnswers() {
	return writeAnswers(imgName);
}

bool AnalyzeImage::writeAnswers(std::string name) {
	std::ofstream out(name.c_str(), std::ios::out);
	for (unsigned int i = 0; i < answers.size(); i++) {
		out << answers[i] << std::endl;
	}
	out.close();
	return true;
}

int AnalyzeImage::getID() {
	if (!calculated) {
		id = -1;
		//Check answers every option
		if (plate.ids.x < 0 || plate.ids.x >= blacks.size() || plate.ids.y < 0 || plate.ids.y >= blacks.size()) {
			std::cerr << "Invalid bounds for ids." << std::endl;
		}
		else {
			int index = plate.ids.x;
			for (int i = 0; i < plate.digits; i++) {
				index = plate.ids.x + i;
				for (int j = plate.ids.x; j < plate.ids.y; j += plate.digits) {
					if (blacks[j + i] > index) {
						index = j + i;
					}
				}
				id += (int)(index / plate.digits) * pow(10, i);
			}
		}
	}
	return id;
}

unsigned int AnalyzeImage::maxVal(std::vector <double> v, unsigned int lower, unsigned int upper) {
	unsigned int index = lower;
	for (unsigned int i = lower; i < upper; i++) {
		if (v[i] > v[index]) {
			index = i;
		}
	}
	return index;
}