#include "ScanImage.h"
#include "bitmap\bitmap_image.hpp"
#include <cstdio>

ScanImage::ScanImage() {
	pixels = std::vector< std::vector<Pixel> >();
	grayScale = std::vector< std::vector<int> >();
}

ScanImage::ScanImage(std::string name)
{
	//Read data
	readRawData(name);

	//Convert to grayScale
	readGrayScale();
}

//Obtain raw image data into pixels
bool ScanImage::readRawData(std::string name) {

	//TODO: Other file formats

	//Get extension
	std::string ext = name.substr(name.find("."), name.length());

	//BMP
	if (ext == "bmp") {
		bitmap_image image(name.c_str());

		//Error check
		if (!image) {
			std::cerr << "Failed to open image." << std::endl;
			return false;
		}

		//RGB
		unsigned char r, g, b;
		unsigned int pixelCount = 0;

		int width = image.width();
		int height = image.height();

		//Get resolution
		resolution = Point(width, height);

		//Scan in each pixel
		for (int i = 0; i < width; i++) {
			pixels.push_back(std::vector<Pixel>());
			for (int j = 0; j < height; j++) {
				image.get_pixel(i, j, r, g, b);
				pixels[i].push_back(Pixel(r, g, b));
			}
		}
	}
	else {
		std::cerr << ext << " not supported." << std::endl;
		return false;
	}

	//Get grayScale
	readGrayScale();

	return true;
}

bool ScanImage::readGrayScale() {
	//Clear grayScale
	grayScale.clear();

	//Calculate for every pixel
	for (unsigned int i = 0; i < pixels.size(); i++) {

		grayScale.push_back(std::vector<int>());

		for (unsigned int j = 0; j < pixels[i].size(); j++) {

			grayScale[i].push_back(pixels[i][j].grayscale());

			//Validity check
			if (grayScale[i][j] <= 0) {
				std::cerr << "Non-positive pixel magnitude." << std::endl;
				return false;
			}
		}
	}

	return true;
}

//Getter for pixels
std::vector< std::vector<Pixel> > ScanImage::getPixels ()
{
	return pixels;
}

//Getter for grayScale
std::vector< std::vector<int> > ScanImage::getGrayScale()
{
	return grayScale;
}