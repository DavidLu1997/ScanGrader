#include "ScanImage.hpp"
#include <cstdio>

//Standard constructor
ScanImage::ScanImage() {
	grayScale = std::vector< std::vector<int> >();
}

//Constructor loading image
ScanImage::ScanImage(std::string name)
{
	//Read data
	readRawData(name);
}

//Obtain raw image data into pixels
bool ScanImage::readRawData(std::string name) {

	//QImageReader
	QImageReader *imageReader = new QImageReader(name.c_str());
	resolution.x = imageReader->size().width();
	resolution.y = imageReader->size().height();

	image = imageReader->read();

	return true;
}

//Converts image to grayScale by averaging
void ScanImage::calculate() {
	grayScale.clear();
	for (int i = 0; i < resolution.x; i++) {
		grayScale.push_back(std::vector<int>());
		for (int j = 0; j < resolution.y; j++) {
			grayScale[i].push_back(qGray(image.pixel(i, j)));
		}
	}
}

//Getter for grayScale
const std::vector< std::vector<int> >& ScanImage::getGrayScale()
{
	return grayScale;
}