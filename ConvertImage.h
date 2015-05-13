#ifndef CONVERTIMAGE_H
#define CONVERTIMAGE_H

#include <vector>
#include "Pixel.h"

class ConvertImage
{
public:
	std::vector< std::vector<Pixel> > rawImage;
	
	//Standard constructor
	ConvertImage(std::vector< std::vector<Pixel> > img)
	{
		rawImage = img;
	}

	//Convert image to grayscale
std::vector< std::vector<int> > grayscale()
	{
		std::vector< std::vector<int> > newImage(rawImage.size());
		for (int i = 0; i < rawImage.size(); i++)
		{
			for (int j = 0; j < rawImage[i].size(); j++)
			{
				newImage[i].push_back(rawImage[i][j].grayscale());
			}
		}
	}
};

#endif