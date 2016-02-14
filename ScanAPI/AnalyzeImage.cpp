#define _USE_MATH_DEFINES
#include "AnalyzeImage.hpp"
#include <cmath>
#include <algorithm>
#include <queue>

//Static
double AnalyzeImage::percentage = 0.35;
int AnalyzeImage::threshold = 100;

//Standard constructor for AnalyzeImage
//Beginning of program, call this with required variables
//After initialization, call getAnswers and/or getID for data
AnalyzeImage::AnalyzeImage(std::string imageName, std::string configName) {
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
	//img.image = img.image.scaled(plate.resolution.x, plate.resolution.y);
	plate.scale(xScale, yScale);
	plate.calculateRectangles();
	
	img.calculate();

	calculated = false;

	//Calculate results
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
	ReadDot read(img, threshold);
	
	//Go through rectangles
	for (unsigned int i = 0; i < plate.getRects().size(); i++) {
		marks.push_back(read.black(plate.getRects().at(i)));
	}

	//Get answers
	answers = getAnswers();

	//Get ID
	id = getID();

	calculated = true;
	return true;
}

//Scans for individual calibration squares
//TODO Optimize
Rectangle AnalyzeImage::individual(ReadDot read, Rectangle cali) {
	//If black enough
	if (read.black(cali) > percent) {
		return cali;
	}

	//Radius 1 pixel to start off
	int radius = 1;

	//Lengths
	int xLen = abs(cali.lower.x - cali.upper.x);
	int yLen = abs(cali.lower.y - cali.upper.y);

	//Maximum radius to check for
	//If hit, stop
	int maxRadius = 10 * xLen;

	//Check grid pattern using BFS
	std::queue<Rectangle> que;
	que.push(cali);

	//While not found
	Rectangle temp;
	while (!que.empty() && read.black(que.front()) <= percent) {
		cali = que.front();
		que.pop();

		//All possibilities
		//Search in a square
		temp = cali;
		temp.upper.x += radius;
		temp.lower.x += radius;
		que.push(temp);
		temp = cali;
		temp.upper.y += radius;
		temp.lower.y += radius;
		que.push(temp);
		temp = cali;
		temp.upper.x -= radius;
		temp.lower.x -= radius;
		que.push(temp);
		temp = cali;
		temp.upper.y -= radius;
		temp.lower.y -= radius;
		que.push(temp);
		temp = cali;
		temp.upper.x += radius;
		temp.lower.x += radius;
		temp.upper.y += radius;
		temp.lower.y += radius;
		que.push(temp);
		temp = cali;
		temp.upper.x -= radius;
		temp.lower.x -= radius;
		temp.upper.y -= radius;
		temp.lower.y -= radius;
		que.push(temp);
		temp = cali;
		temp.upper.x -= radius;
		temp.lower.x -= radius;
		temp.upper.y += radius;
		temp.lower.y += radius;
		que.push(temp);
		temp = cali;
		temp.upper.x += radius;
		temp.lower.x += radius;
		temp.upper.y -= radius;
		temp.lower.y -= radius;
		que.push(temp);

		//Increment radius
		radius += 1;
	}

	return que.empty() ? cali : que.front();
}

//Calibration squares are all black
bool AnalyzeImage::calibrate() {
	std::vector<Rectangle> cali = plate.getCali();

	//Create ReadDot
	ReadDot read(img, threshold);

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
	unsigned int temp;
	if (!calculated) {
		answers.clear();
		//Check answers every option
		if (plate.questions.x < 0 || plate.questions.x >= marks.size() || plate.questions.y < 0 || plate.questions.y >= marks.size()) {
			std::cerr << "Invalid bounds for answers or answers section does not exist." << std::endl;
		}
		else {
			for (int i = plate.questions.x; i < plate.questions.y; i += plate.options) {
				temp = maxVal(marks, i, i + plate.options);
				if (marks[temp] < percent) {
					answers.push_back(-1);
				}
				else {
					answers.push_back(temp % plate.options + 1);
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

//Calculates ID entered based on maximum blackness
int AnalyzeImage::getID() {
	if (!calculated) {
		id = -1;
		//Check answers every option
		if (plate.ids.x < 0 || plate.ids.x >= marks.size() || plate.ids.y < 0 || plate.ids.y >= marks.size()) {
			std::cerr << "Invalid bounds for ids or ID section does not exist." << std::endl;
		}
		else {
			id = 0;
			double maxVal;
			int idx;
			std::string idTemp;
			for (int i = 0; i < plate.digits; i++) {
				maxVal = marks[plate.ids.x + i];
				idx = plate.ids.x + i;
				for (int j = plate.ids.x; j <= plate.ids.y; j += plate.digits) {
					if (marks[j + i] > maxVal) {
						maxVal = marks[j + i];
						idx = j + i;
					}
				}
				idx = (idx / plate.digits) + 1;
				if (idx == 10) {
					idx = 0;
				}
				idTemp += ('0' +idx);
			}
			id = stoi(idTemp);
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