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
		std::cerr << "File not found." << std::endl;
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
	}

	//Next integer, number of rectangles
	int n;
	in >> n;

	//Gets each rectangle
	int id;
	for (int i = 0; i < c; i++) {
		//Two pairs of integers and an id
		in >> x1 >> y1 >> x2 >> y2 >> id;
		rects.push_back(Rectangle(Point(x1, y1), Point(x2, y2)));
	}

	calibrate();
	
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
	for (int i = 0; i < cali.size(); i++) {
		out << cali[i].upper.x << cali[i].upper.y << cali[i].lower.x << cali[i].lower.y << std::endl;
	}

	//Number of rectangles
	out << rects.size() << std::endl;

	//Each rectangle
	for (int i = 0; i < rects.size(); i++) {
		out << rects[i].upper.x << rects[i].upper.y << rects[i].lower.x << rects[i].lower.y << rects[i].id << std::endl;
	}

	out.close();
	return true;
}

bool ImageTemplate::calibrate() {
	//Calibrate each rectangle
	for (int i = 0; i < rects.size(); i++) {
		//Bounds check
		if (rects[i].id < 0 || rects[i].id > cali.size()) {
			std::cerr << "Invalid id." << std::endl;
			return false;
		}

		//All rectangles calibrated from lower point
		rects[i].upper += cali[rects[i].id].lower;
		rects[i].lower += cali[rects[i].id].lower;

		//Testing for bounds
		if (rects[i].upper >= resolution || rects[i].lower >= resolution) {
			std::cerr << "Out of resolution bounds." << std::endl;
			return false;
		}
		if (rects[i].upper.x < 0 || rects[i].upper.y < 0 || rects[i].lower.x < 0 || rects[i].lower.y < 0) {
			std::cerr << "Negative locations." << std::endl;
			return false;
		}
		if (rects[i].size() <= 0) {
			std::cerr << "Non-positive rectangle size." << std::endl;
			return false;
		}
	}
	return true;

}

bool ImageTemplate::scale(double xScale, double yScale) {
	//Bounds check
	if (xScale <= 0 || yScale <= 0) {
		std::cerr << "Non-positive scale." << std::endl;
		return false;
	}

	//Consistency check
	if (xScale >= 2.0 || yScale >= 2.0) {
		std::cout << "Large scale, may not be intentional." << std::endl;
	}

	//Scale everything by scale, truncating rounding
	for (int i = 0; i < cali.size(); i++) {
		cali[i].upper.x *= xScale;
		cali[i].upper.y *= yScale;
		cali[i].lower.x *= xScale;
		cali[i].upper.y *= yScale;
	}
	for (int i = 0; i < rects.size(); i++) {
		rects[i].upper.x *= xScale;
		rects[i].upper.y *= yScale;
		rects[i].lower.x *= xScale;
		rects[i].lower.y *= yScale;
	}

	return true;
}

std::vector<Rectangle> ImageTemplate::getRects() {
	return rects;
}