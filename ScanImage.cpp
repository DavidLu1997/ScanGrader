#define _CRT_SECURE_NO_WARNINGS
#include "ScanImage.h"
#include <cstdio>

ScanImage::ScanImage() {
	pixels = std::vector< std::vector<Pixel> >();
	grayScale = std::vector< std::vector<int> >();
	dpi = 0;
}

ScanImage::ScanImage(std::string name)
{
	//Read data
	readRawData(name);

	//Convert to grayScale
	readGrayScale();
}

ScanImage::ScanImage(std::string name, double width, double height) {
	widthI = width;
	heightI = height;

	//Read data
	readRawData(name);

	//Convert to grayScale
	readGrayScale();
}

//Obtain raw image data into pixels
bool ScanImage::readRawData(std::string name) {

	//TODO: FIX FILE

	//JPEG only
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, file);

	//Get width and height in pixels from appropriate locations
	//18 for width
	int widthP = *(int*)&info[18];
	//22 for height
	int heightP = *(int*)&info[22];

	//Calculate DPI by averaging width and height
	int dpi = (int)(((double)widthP / widthI + (double)heightP / heightI) / 2);

	//Create data array
	int size = 3 * widthP * heightP;
	unsigned char* data = new unsigned char[size];

	//Read image pixel data
	fread(data, sizeof(unsigned char), size, file);

	//Close file
	fclose(file);

	std::vector<Pixel> temp;
	Pixel tem(0, 0, 0);

	//Create pixel vector
	for (int i = 0; i < widthP; i++)
	{
		pixels.push_back(temp);
		for (int j = 0; j < heightP; j++)
		{
			pixels[i].push_back(tem);
		}
	}

	//Swap blue and red to ensure order of red, green, blue
	for (int i = 0; i < size; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	//Place data into pixel array
	for (int i = 0; i < widthP; i++)
	{
		for (int j = 0; j < heightP; j++)
		{
			pixels[i][j].r = data[j * widthP + i];
			pixels[i][j].g = data[j * widthP + i + 1];
			pixels[i][j].b = data[j * widthP + i + 2];
		}
	}

	resolution = Point(dpi * widthI, dpi * heightI);
}

bool ScanImage::readGrayScale() {
	//Clear grayScale
	grayScale.clear();

	//Calculate for every pixel
	for (int i = 0; i < pixels.size(); i++) {

		grayScale.push_back(std::vector<int>());

		for (int j = 0; j < pixels[i].size(); j++) {

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