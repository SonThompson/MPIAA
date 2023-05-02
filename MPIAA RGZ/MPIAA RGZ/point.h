#pragma once

namespace robopath {

	class Circle;

	class Point {
	public:
		Point() {}
		Point(double x, double y) :
			x(x), y(y) {
		}

		double distanceTo(const Point& p) const;
		double distanceToSquared(const Point& p) const;

		bool collidesWith(const Point& p) const;
		bool collidesWith(const Circle& c) const;

	public:
		double x = 0.0, y = 0.0;
	};

}