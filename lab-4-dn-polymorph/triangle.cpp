#include "triangle.h"
#include "rectangle.h"
#include "figure.h"
#include "point.h"
#include "math.h"
#include <iostream>


Triangle::Triangle(double aX, double aY, double bX, double bY, double cX, double cY):_a(aX, aY), _b(bX, bY),
_c(cX, cY) {}

double Triangle::getSquare() const {
	auto a = _a.getDistance(_b);
	auto b = _b.getDistance(_c);
	auto c = _c.getDistance(_a);
	auto p = (a + b + c) / 2;
	return sqrt(p*(p-a)*(p-b)*(p-c));
}

double Triangle::getPerimeter() const {
	return _a.getDistance(_b)+ _b.getDistance(_c)+ _c.getDistance(_a);
}

std::shared_ptr<Figure> Triangle::getRectangle() const {
	auto xMax = _a.getX();
	auto xMin = xMax;
	auto xB = _b.getX();
	auto xC = _c.getX();
	if (xMax < xB) xMax = xB;
	else if (xMax < xC) xMax = xC;
	if (xMin > xB) xMin = xB;
	else if (xMin > xC) xMin = xC;
	auto yMax = _a.getY();
	auto yMin = yMax;
	auto yB = _b.getY();
	auto yC = _c.getY();
	if (yMax < yB) yMax = yB;
	else if (yMax < yC) yMax = yC;
	if (yMin > yB) yMin = yB;
	else if (yMin > yC) yMin = yC;
	return std::shared_ptr<Rectangle>(new Rectangle (xMin, xMax, yMin, yMax));
}

void Triangle::print() const {
	std::cout << "Triangle is based on points:" << std::endl;
	std::cout << "(" << _a.getX() << "," << _a.getY() << ")" << "(" << _b.getX() << "," << _b.getY() << ")" 
		<< "(" << _c.getX() << "," << _c.getY() << ")" << std::endl;
}

bool Triangle::equals(const Figure& obj) const {
	auto copy = dynamic_cast<const Triangle*>(&obj);
	if (copy == nullptr) return false;
	if ((_a.getDistance(_b) != copy->_a.getDistance(copy->_b)) || (_b.getDistance(_c) != copy->_b.getDistance(copy->_c)) 
		|| (_c.getDistance(_a) != copy->_c.getDistance(copy->_a))) return false;
	return true;
}
