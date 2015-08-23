#define _CRT_SECURE_NO_WARNINGS
#include "ScanImage.h"
#include <cstdio>

//Scans an image to the ScanImage object
ScanImage::ScanImage(char *name)
{
	//Opens file
	FILE *file;
	file = fopen(name, "r");
	if (file == NULL)
	{
		printf("Invalid filename, %s not found.", name);
	}

	//Reads information from file
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
}

//Getter for raw pixels
std::vector< std::vector<Pixel> > ScanImage::rawData()
{
	return pixels;
}

//Turns pixel data into grayscale
//Averages RGB values
std::vector< std::vector<int> > ScanImage::grayScale()
{
	std::vector< std::vector<int> > newImage(pixels.size());
	for (int i = 0; i < pixels.size(); i++)
	{
		for (int j = 0; j < pixels[i].size(); j++)
		{
			newImage[i].push_back(pixels[i][j].grayscale());
		}
	}
}