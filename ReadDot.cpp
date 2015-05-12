#include "ReadDot.h"

//Standard constructor
ReadDot::ReadDot(std::vector< std::vector<int> > img, int thres, double percent)
{
	image = img;
	threshold = thres;
	percentage = percent;
}

//Returns percentage of blackness
double ReadDot::black()
{
	//Sum of grayscale pixel values
	int sum = 0;

	//Number of rows
	int x = 0;

	//Number of columns
	int y = 0;

	//Loop through array
	for (int i = 0; i < image.size(); i++)
	{
		//Increment rows count
		x++;

		for (int j = 0; j < image[i].size(); j++)
		{
			//Increment sum
			sum += image[i][j];

			//Increment columns count
			y++;
		}
	}

	//Calculate percentage
	return (double)sum / (x * y * 255);
}

//Checks if blackness is over threshold
bool ReadDot::check()
{
	if (black() > threshold)
	{
		return true;
	}
	else
	{
		return false;
	}
}