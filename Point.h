//Point class
//Denotes a x, y pixel location
//Top right pixel is 0, 0

#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point {
public:
	//Storage
	int x, y;

	//Creates a point at 0, 0
	Point() {
		x = 0;
		y = 0;
	}

	//Creates a point at a, b
	Point(int a, int b) {
		x = a;
		y = b;
	}

	//Distance to another point, int
	int distance(Point p) {
		return (int) distanceD(p);
	}

	//Distance to another point, double
	double distanceD(Point p) {
		return sqrt((double)(x - p.x) * (x - p.x) + (double)(y - p.y) * (y - p.y));
	}

	//Equals
	bool operator==(const Point& p) {
		return x == p.x && y == p.y;
	}

	//Less than
	bool operator<(const Point& p) {
		return x < p.y && y < p.y;
	}

	//Less than or equal to
	bool operator<=(const Point& p) {
		return x <= p.y && y <= p.y;
	}

	//Greater than
	bool operator>(const Point& p) {
		return x > p.y && y > p.y;
	}

	//Greater than or equal to
	bool operator>=(const Point& p) {
		return x >= p.y && y >= p.y;
	}

	//Addition to itself
	void operator+=(const Point& p) {
		x += p.x;
		y += p.y;
	}

	//Subtraction from itself
	void operator-=(const Point& p) {
		x -= p.x;
		y -= p.y;
	}

	//Addition
	friend Point operator+(const Point& l, const Point& r) {
		Point n(l.x + r.x, l.y + r.y);
		return n;
	}

	//Subtraction
	friend Point operator-(const Point& l, const Point& r) {
		Point n(l.x - r.x, l.y - r.y);
		return n;
	}

	//Dot
	friend int operator*(const Point& l, const Point& r) {
		return l.x * r.x + l.y * r.y;
	}

	//<<
	std::ostream& operator<< (std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
	}
	//>>
	std::istream& operator>> (std::istream& is, const Point& p) {
	    //TODO: Add error checking
	    is >> p.x >> p.y;
	    return is;
	}
};

#endif
