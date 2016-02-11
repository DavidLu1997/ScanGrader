//Image Template Class
//Loads a template giving pixel locations of possible bubbles

#ifndef IMAGETEMPLATE_H
#define IMAGETEMPLATE_H

#include <string>
#include <vector>
#include "Point.hpp"
#include "Rectangle.hpp"

class ImageTemplate {
public:
	//Creates a blank template
	ImageTemplate();

	//Creates a template from a config file
	ImageTemplate(std::string name);
	    
	//Loads template from file
	bool loadTemplate(std::string name);

	//Saves current template to file
	//Currently unused
	//bool savesTemplate(std::string name);

	//Sets calibration locations based on image analysis
	void setCalibrate(std::vector<Rectangle> newCali);

	//Calculates rectangle locations based on calibration rectangles
	bool calculateRectangles();

	//Scales all locations by a scale factor (2.0 - double)
	bool scale(double xScale, double yScale);

	//Resolution of image
	Point resolution;

	//Getter for rects
	std::vector<Rectangle> getRects();

	//Getter for cali
	std::vector<Rectangle> getCali();

	//ID Section, rectangle indexes
	Point ids;

	//Number of digits in ID
	int digits;

	//Questions, question indexes
	Point questions;

	//Options per question
	int options;
	
private:
	//Scaling
	void scaleRects(double xScale, double yScale);
	void scaleCali(double xScale, double yScale);

	//Rectangles
	std::vector<Rectangle> rects;

	//Original rectangles
	std::vector<Rectangle> origRects;

	//Scale
	double xS, yS;

	//Calibration rectangles
	std::vector<Rectangle> cali;

	//Original cali
	std::vector<Rectangle> origCali;
};

#endif