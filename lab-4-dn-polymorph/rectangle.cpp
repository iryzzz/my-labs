#include "rectangle.h"
#include "figure.h"
#include "point.h"
#include <iostream>
#include "math.h"

Rectangle::Rectangle(double xMin, double xMax, double yMin, double yMax) noexcept: _a(xMin, yMax),
_b(xMax, yMax), _c(xMax, yMin), _d(xMin, yMin) {}

double Rectangle::getSquare() const {
	auto height = _a.getDistance(_c);
	auto length = _a.getDistance(_b);
	return height * length;
}

double Rectangle::getPerimeter() const {
	auto height = _a.getDistance(_c);
	auto length = _a.getDistance(_b);
	return 2 * (length + height);
}

std::shared_ptr<Figure> Rectangle::getRectangle() const {
	return std::shared_ptr<Figure>(new Rectangle(_a.getX(), _b.getX(), _c.getY(), _a.getY()));
}

void Rectangle::print() const {
	std::cout << "Rectangle is based on points:" << std::endl;
	std::cout << "(" << _a.getX() << "," << _a.getY() << ")" << "(" << _b.getX() << "," << _b.getY() << ")" << std::endl;
	std::cout << "(" << _d.getX() << "," << _d.getY() << ")" << "(" << _c.getX() << "," << _c.getY() << ")" << std::endl;
}

bool Rectangle::equals(const Figure& obj) const {
	auto copy = dynamic_cast<const Rectangle*>(&obj);
	if (copy == nullptr) return false;
	if ((_a.getDistance(_b) != copy->_a.getDistance(copy->_b)) || (_a.getDistance(_d) != copy->_a.getDistance(copy->_d))) return false;
	return true;
}
