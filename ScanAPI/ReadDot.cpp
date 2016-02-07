#include "ReadDot.hpp"
#include <algorithm>

//ReadDot constructor, given ScanImage and percent
ReadDot::ReadDot(ScanImage img, int thresh) {
	image = img;
	threshold = thresh;
	grayPixels = img.getGrayScale();
}

//Adds up all pixels within given rectangle
//TODO: Make more efficient
//Memory is less valuable than time
double ReadDot::black(Rectangle rect) {
	//Sum of all pixels
	int sum = 0;
	for (int i = std::max(rect.upper.x, 0); i < std::min(rect.lower.x, (int)grayPixels.size()); i++) {
		for (int j = std::max(rect.upper.y, 0); j < std::min(rect.lower.y, (int)grayPixels[i].size()); j++) {
			if (grayPixels[i][j] >= threshold) {
				sum += grayPixels[i][j];
			}
		}
	}

	//Calculate percent black
	return 1 - ((double)sum / rect.size()) / 255.0;
}