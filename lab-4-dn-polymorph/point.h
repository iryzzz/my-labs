#pragma once

struct Point {
	double _x, _y;
public:
	Point() noexcept;

	Point(const double& x, const double& y) noexcept;

	double getDistance(const Point&) const noexcept;

	double getX() const noexcept;

	double getY() const noexcept;

};