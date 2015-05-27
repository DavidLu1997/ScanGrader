#define _CRT_SECURE_NO_WARNINGS
#include "ScanImage.h"
#include <cstdio>

ScanImage::ScanImage(char *name)
{
	FILE *file;
	file = fopen(name, "r");
	if (file == NULL)
	{
		printf("Invalid filename, %s not found.", name);
	}

	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, file);

	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size];

	fread(data, sizeof(unsigned char), size, file);
	fclose(file);

	std::vector<Pixel> temp;
	Pixel tem(0, 0, 0);

	for (int i = 0; i < width; i++)
	{
		pixels.push_back(temp);
		for (int j = 0; j < height; j++)
		{
			pixels[i].push_back(tem);
		}
	}

	for (int i = 0; i < size; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			pixels[i][j].r = data[j * width + i];
			pixels[i][j].g = data[j * width + i + 1];
			pixels[i][j].b = data[j * width + i + 2];
		}
	}
}

std::vector< std::vector<Pixel> > ScanImage::rawData()
{
	return pixels;
}

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