#include "ImageTemplate.hpp"
#include <fstream>
#include <iostream>

//Default constructor for image template
ImageTemplate::ImageTemplate() {
	rects.push_back(Rectangle(Point(), Point()));
	cali.push_back(Rectangle(Point(), Point()));
}

//Standard constructor with name of template
ImageTemplate::ImageTemplate(std::string name) {
	loadTemplate(name);
}

//Loads template from file
bool ImageTemplate::loadTemplate(std::string name) {
	std::ifstream in(name.c_str(), std::ios::in);

	if (!in.is_open()) {
		std::cerr << name << " not found." << std::endl;
		return false;
	}

	//Clear vectors
	rects.clear();
	cali.clear();
	resolution = Point();

	//TODO: Incorporate config file library with comments

	//First pair, resolution of image
	in >> resolution.x >> resolution.y;

	//Next integer, number of calibration rectangles
	int c;
	in >> c;

	//Gets each calibration rectangle
	int x1, y1, x2, y2;
	for (int i = 0; i < c; i++) {
		//Two pairs of integers
		in >> x1 >> y1 >> x2 >> y2;
		cali.push_back(Rectangle(Point(x1, y1), Point(x2, y2)));
		//std::cout << cali[i].upper.x << " " << cali[i].upper.y << " " << cali[i].lower.x << " " << cali[i].lower.y << " " << std::endl;
	}

	//Next integer, number of rectangles
	int n;
	in >> n;

	//Gets each rectangle
	int id;
	for (int i = 0; i < n; i++) {
		//Two pairs of integers and an id
		in >> x1 >> y1 >> x2 >> y2 >> id;
		rects.push_back(Rectangle(Point(x1, y1), Point(x2, y2), id));
	}

	//Next integer, locations of ID,indexes of rectangles
	//-1 means no ID section
	in >> ids.x >> ids.y;

	//Digits of ID
	in >> digits;

	//Next integer, locations of questions, indexes of rectangles
	//-1 means no questions
	in >> questions.x >> questions.y;

	//Next integer, options per question
	in >> options;

	//calculateRectangles();
	
	in.close();
	return true;
}

//Set calibration rectangles, and recalculates everything else from it
void ImageTemplate::setCalibrate(std::vector<Rectangle> newCali) {
	cali = newCali;
	calculateRectangles();
}

//Calculates rectangles
bool ImageTemplate::calculateRectangles() {
	//Calibrate each rectangle
	for (unsigned int i = 0; i < rects.size(); i++) {
		//Bounds check
		if (rects[i].id < 0 || (unsigned int)rects[i].id >= cali.size()) {
			std::cerr << "Invalid id " << rects[i].id << " at " << i << std::endl;
			return false;
		}

		//All rectangles calibrated from upper point
		rects[i].upper.x += cali[rects[i].id].upper.x;
		rects[i].upper.y += cali[rects[i].id].upper.y;
		rects[i].lower.x += cali[rects[i].id].upper.x;
		rects[i].lower.y += cali[rects[i].id].upper.y;

		//Testing for bounds
		if (rects[i].upper >= resolution || rects[i].lower >= resolution) {
			std::cerr << "Out of resolution bounds at " << i << std::endl;
			return false;
		}
		if (rects[i].upper.x < 0 || rects[i].upper.y < 0 || rects[i].lower.x < 0 || rects[i].lower.y < 0) {
			std::cerr << "Negative locations at " << i << std::endl;
			return false;
		}
		if (rects[i].size() <= 0) {
			std::cerr << "Non-positive rectangle size at " << i << std::endl;
			return false;
		}
	}
	return true;

}

//Scales rectangles
bool ImageTemplate::scale(double xScale, double yScale) {
	//Bounds check
	if (xScale <= 0 || yScale <= 0) {
		std::cerr << "Non-positive scale: " << xScale << ", " << yScale << std::endl;
		return false;
	}

	//Consistency check
	if (xScale >= 2.0 || yScale >= 2.0) {
		std::cout << "Large scale, may not be intentional: " << xScale << ", " << yScale << std::endl;
	}

	//Scale everything by scale, truncating rounding
	for (unsigned int i = 0; i < cali.size(); i++) {
		cali[i].upper.x = (int)((double)cali[i].upper.x * xScale);
		cali[i].upper.y = (int)((double)cali[i].upper.y * yScale);
		cali[i].lower.x = (int)((double)cali[i].lower.x * xScale);
		cali[i].lower.y = (int)((double)cali[i].lower.y * yScale);
	}
	for (unsigned int i = 0; i < rects.size(); i++) {
		rects[i].upper.x = (int)((double)rects[i].upper.x * xScale);
		rects[i].upper.y = (int)((double)rects[i].upper.y * yScale);
		rects[i].lower.x = (int)((double)rects[i].lower.x * xScale);
		rects[i].lower.y = (int)((double)rects[i].lower.y * yScale);
	}

	resolution.x *= xScale;
	resolution.y *= yScale;

	return true;
}

//Get standard rectangles
std::vector<Rectangle> ImageTemplate::getRects() {
	return rects;
}

//Get calibration rectangles
std::vector<Rectangle> ImageTemplate::getCali() {
	return cali;
}