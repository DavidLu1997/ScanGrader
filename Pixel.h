#ifndef PIXEL_H
#define PIXEL_H

class Pixel
{
	//Red, green and blue
	int r, g, b;

	//Standard constructor
	Pixel(int red, int green, int blue)
	{
		r = red;
		g = green;
		b = blue;
	}

	//Magnitude of pixel (grayscale)
public: int grayscale()
	{
		return (r + g + b) / 3;
	}
};

#endif