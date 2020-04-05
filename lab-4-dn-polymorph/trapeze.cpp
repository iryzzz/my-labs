#include "rectangle.h"
#include "figure.h"
#include "point.h"
#include "math.h"
#include <iostream>
#include "trapeze.h"

Trapeze::Trapeze(double aX, double bX, double cX, double dX, double yMax, double yMin): _a(aX, yMax),_b(bX, yMax),
_c(cX, yMin), _d(dX, yMin) {}

double Trapeze::getSquare() const {
	return ((_a.getY())-(_d.getY())*((_a.getDistance(_b)+_c.getDistance(_d))/2));
}

double Trapeze::getPerimeter() const {
	return _a.getDistance(_b) + _b.getDistance(_c) + _c.getDistance(_d) + _d.getDistance(_a);
}

std::shared_ptr<Figure> Trapeze::getRectangle() const {
	auto xMax = _a.getX();
	auto xMin = xMax;
	auto xB = _b.getX();
	auto xC = _c.getX();
	auto xD = _d.getX();
	if (xMax < xB) xMax = xB;
	else if (xMax < xC) xMax = xC;
	else if (xMax < xD) xMax = xD;
	if (xMin > xB) xMin = xB;
	else if (xMin > xC) xMin = xC;
	else if (xMin > xD) xMin = xD;
	return std::shared_ptr<Rectangle>(new Rectangle(xMin, xMax, _a.getY(), _d.getY()));
}

void Trapeze::print() const {
	std::cout << "Trapeze is based on points:" << std::endl;
	std::cout << "(" << _a.getX() << "," << _a.getY() << ")" << "(" << _b.getX() << "," << _b.getY() << ")" << std::endl;
	std::cout << "(" << _d.getX() << "," << _d.getY()<< ")" << "(" << _c.getX() << "," << _c.getY()<< ")" << std::endl;
}

bool Trapeze::equals(const Figure& obj) const {
	auto copy = dynamic_cast<const Trapeze*>(&obj);
	if (copy == nullptr) return false;
	if ((_a.getDistance(_b) != copy->_a.getDistance(copy->_b)) || (_b.getDistance(_c) != copy->_b.getDistance(copy->_c))
		|| (_c.getDistance(_d) != copy->_c.getDistance(copy->_d)) || (_d.getDistance(_a) != copy->_d.getDistance(copy->_a))) return false;
	return true;
}
