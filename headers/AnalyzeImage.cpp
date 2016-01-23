#define _USE_MATH_DEFINES
#include "AnalyzeImage.hpp"
#include <cmath>
#include <algorithm>

//Standard constructor for AnalyzeImage
//Beginning of program, call this with required variables
//After initialization, call getAnswers and/or getID for data
AnalyzeImage::AnalyzeImage(std::string imageName, std::string configName, double percentage) {
	//Get image
	img = ScanImage(imageName);

	//Store image name
	imgName = imageName;

	//Store percentage
	percent = percentage;

	//Default ID
	id = -1;

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

	calculate();
}

//Calculates percentage blackness with user-specified parameters
bool AnalyzeImage::calculate() {
	//Validity check
	if (percent <= 0) {
		std::cerr << "Invalid black percentage " << percent << std::endl;
		return false;
	}

	calibrate();

	//Initialize ReadDot
	ReadDot read(img, percent);
	
	//Go through rectangles
	for (unsigned int i = 0; i < plate.getRects().size(); i++) {
		marks.push_back(read.black(plate.getRects().at(i)));
	}

	//Get answers
	getAnswers();

	//Get ID
	getID();

	calculated = true;
	return true;
}

//Scans for individual calibration squares
Rectangle AnalyzeImage::individual(ReadDot read, Rectangle cali) {
	//If black enough
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
bool AnalyzeImage::calibrate() {
	std::vector<Rectangle> cali = plate.getCali();

	//Create ReadDot
	ReadDot read(img, percent);

	//Check each rectangle
	for (unsigned int i = 0; i < cali.size(); i++) {
		//If calibration square isn't black enough
		if (read.black(cali[i]) <= percent) {
			cali[i] = individual(read, cali[i]);
		}
	}

	plate.setCalibrate(cali);
	return true;
}

//Gets answers by finding maximum blackness
std::vector<int> AnalyzeImage::getAnswers() {
	double temp;
	if (!calculated) {
		answers.clear();
		//Check answers every option
		if (plate.questions.x < 0 || plate.questions.x >= marks.size() || plate.questions.y < 0 || plate.questions.y >= marks.size()) {
			std::cerr << "Invalid bounds for answers or answers section does not exist." << std::endl;
		}
		else {
			for (int i = plate.questions.x; i < plate.questions.y; i += plate.options) {
				temp = (maxVal(marks, i, i + plate.options) % plate.options) + 1;
				if (temp < percent) {
					answers.push_back(-1);
				}
				else {
					answers.push_back(temp);
				}
			}
		}
	}
	return answers;
}

//Returns raw result vector
std::vector<double> AnalyzeImage::getRawResults() {
	return marks;
}

//Writes answers to a file, custom name
bool AnalyzeImage::writeAnswers(std::string name) {
	std::ofstream out(name.c_str(), std::ios::out);
	for (unsigned int i = 0; i < answers.size(); i++) {
		out << answers[i] << std::endl;
	}
	out.close();
	return true;
}

//Calculates ID entered based on maximum blackness
int AnalyzeImage::getID() {
	if (!calculated) {
		id = -1;
		//Check answers every option
		if (plate.ids.x < 0 || plate.ids.x >= marks.size() || plate.ids.y < 0 || plate.ids.y >= marks.size()) {
			std::cerr << "Invalid bounds for ids or ID section does not exist." << std::endl;
		}
		else {
			int index = plate.ids.x;
			for (int i = 0; i < plate.digits; i++) {
				index = plate.ids.x + i;
				for (int j = plate.ids.x; j < plate.ids.y; j += plate.digits) {
					if (marks[j + i] > index) {
						index = j + i;
					}
				}
				id += (int)(index / plate.digits) * pow(10, i);
			}
		}
	}
	return id;
}

//Finds maximum value of vector between upper and lower bounds
//TODO: Write for template T
unsigned int AnalyzeImage::maxVal(std::vector <double> v, unsigned int lower, unsigned int upper) {
	unsigned int index = lower;
	for (unsigned int i = lower; i < upper; i++) {
		if (v[i] > v[index]) {
			index = i;
		}
	}
	return index;
}

//Clears all vectors
void AnalyzeImage::clearAll() {
	marks.clear();
	answers.clear();
	calculated = false;
	id = -1;
}