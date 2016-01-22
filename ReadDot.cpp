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
	for (int i = std::max(rect.upper.x, 0); i < std::min(rect.lower.x, (int)grayPixels.size()); i++) {
		for (int j = std::max(rect.upper.y, 0); j < std::min(rect.lower.y, (int)grayPixels[i].size()); j++) {
			sum += grayPixels[i][j];
		}
	}

	std::cout << 1 - ((double)sum / rect.size()) / 255.0 << ", (" << rect.upper.x << ", " << rect.upper.y << ") " << rect.size() << std::endl;

	//Calculate percent black
	return 1 - ((double)sum / rect.size()) / 255.0;
}

bool ReadDot::check(Rectangle rect) {
	return black(rect) <= percentage;
}