#include "ImageTemplate.h"
#include <fstream>
#include <iostream>

ImageTemplate::ImageTemplate() {
	rects.push_back(Rectangle(Point(), Point()));
	cali.push_back(Rectangle(Point(), Point()));
}

ImageTemplate::ImageTemplate(std::string name) {
	loadTemplate(name);
}

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

	calculateRectangles();
	
	in.close();
	return true;
}

bool ImageTemplate::savesTemplate(std::string name) {
	std::ofstream out(name.c_str(), std::ios::out);

	//Resolution
	out << resolution.x << resolution.y << std::endl;

	//Number of calibration rectangles
	out << cali.size() << std::endl;

	//Each calibration rectangle
	for (unsigned int i = 0; i < cali.size(); i++) {
		out << cali[i].upper.x << cali[i].upper.y << cali[i].lower.x << cali[i].lower.y << std::endl;
	}

	//Number of rectangles
	out << rects.size() << std::endl;

	//Each rectangle
	for (unsigned int i = 0; i < rects.size(); i++) {
		out << rects[i].upper.x << rects[i].upper.y << rects[i].lower.x << rects[i].lower.y << rects[i].id << std::endl;
	}

	out.close();
	return true;
}

void ImageTemplate::setCalibrate(std::vector<Rectangle> newCali) {
	cali = newCali;
	calculateRectangles();
}

bool ImageTemplate::calculateRectangles() {
	//Calibrate each rectangle
	for (unsigned int i = 0; i < rects.size(); i++) {
		//Bounds check
		if (rects[i].id < 0 || (unsigned int)rects[i].id >= cali.size()) {
			std::cerr << "Invalid id " << rects[i].id << " at " << i << std::endl;
			return false;
		}

		//All rectangles calibrated from upper point
		rects[i].upper += cali[rects[i].id].upper;
		rects[i].lower += cali[rects[i].id].upper;

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

	return true;
}

std::vector<Rectangle> ImageTemplate::getRects() {
	return rects;
}

std::vector<Rectangle> ImageTemplate::getCali() {
	return cali;
}