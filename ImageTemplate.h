//Image Template Class
//Loads a template giving pixel locations of possible bubbles

#ifndef IMAGETEMPLATE_H
#define IMAGETEMPLATE_H

#include <string>
#include <vector>
#include "Point.h"
#include "Rectangle.h"

class ImageTemplate {
public:
	//Creates a blank template
	ImageTemplate();

	//Creates a template from a config file
	ImageTemplate(std::string name);
	    
	//Loads template from file
	bool loadTemplate(std::string name);

	//Saves current template to file
	bool savesTemplate(std::string name);

	//Calibrates rectangle locations based on calibration rectangles
	bool calibrate();

	//Scales all locations by a scale factor (2.0 - double)
	bool scale(double xScale, double yScale);

	//Resolution of image
	Point resolution;

	//Getter for rects
	std::vector<Rectangle> getRects();
	
private:
	//Rectangles
	std::vector<Rectangle> rects;

	//Calibration rectangles
	std::vector<Rectangle> cali;
};

#endif