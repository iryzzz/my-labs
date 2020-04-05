#include "point.h"
#include <iostream>
#include <cmath>

Point::Point() noexcept: _x(0), _y(0) {}

Point::Point(const double& x, const double& y) noexcept : _x(x), _y(y) {}

double Point::getDistance(const Point& obj) const noexcept {
	return sqrt(((_x-obj._x)* (_x - obj._x)) + ((_y-obj._y)* (_y - obj._y)));
}

double Point::getX() const noexcept {
	return _x;
}

double Point::getY() const noexcept
{
	return _y;
}
