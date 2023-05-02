#pragma once

#include "point.h"

namespace robopath {

	class LineSegment;

	class Circle {
	public:
		Circle() {}
		Circle(const Point& center, double radius) :
			center(center), radius(radius) {
		}
		Circle(double x, double y, double radius) :
			center(x, y), radius(radius) {
		}

		bool collidesWith(const Point& p) const;
		bool collidesWith(const Circle& c) const;

	public:
		Point center;
		double radius;
	};

}