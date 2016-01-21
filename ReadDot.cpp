#include "ReadDot.h"

ReadDot::ReadDot(ScanImage img, int thres, double percent) {
	image = img;
	threshold = thres;
	percentage = percent;
	grayPixels = img.getGrayScale();
}

double ReadDot::black(Rectangle rect) {
	//Sum of all pixels
	int sum = 0;
	for (int i = rect.upper.x; i < rect.lower.x; i++) {
		for (int j = rect.upper.y; j < rect.lower.y; j++) {
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