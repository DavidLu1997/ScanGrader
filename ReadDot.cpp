#include "ReadDot.h"
#include <algorithm>

ReadDot::ReadDot(ScanImage img, int thres, double percent) {
	image = img;
	threshold = thres;
	percentage = percent;
	grayPixels = img.getGrayScale();
}

double ReadDot::black(Rectangle rect) {
	//Sum of all pixels
	int sum = 0;
	for (int i = rect.upper.x; i < std::min(rect.lower.x, (int)grayPixels.size()); i++) {
		for (int j = rect.upper.y; j < std::min(rect.lower.y, (int)grayPixels[i].size()); j++) {
			if (grayPixels[i][j] >= threshold) {
				sum++;
			}
		}
	}

	//Calculate percent black
	return (double)sum / rect.size();
}

bool ReadDot::check(Rectangle rect) {
	return black(rect) >= percentage;
}