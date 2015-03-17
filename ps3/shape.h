#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
	Shape();
};

class Point : public Shape {
public:
	Point();
	Point(float x, float y, float z) { 
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }

private:
	float x;
	float y;
	float z;
};

class Line : public Shape {
public:
	Line();
	Line(Point start, Point end) {
		this->start = start;
		this->end = end;
	}
	const Point &getStartPoint() const { return start; }
	const Point &getendPoint() const { return end; }

private:
	Point start;
	Point end;
};

class Triangle : public Shape {
public:
	Triangle(Point a, Point b, Point c) {
		ab = Line(a, b);
		bc = Line(b, c);
		ca = Line(c, a);
	}

private:
	Line ab;
	Line bc;
	Line ca;
};

class Sphere : public Shape {
public:
	Sphere();
	Sphere(Point center, float radius) {
		c = center;
		r = radius;
	}
	Sphere(float x, float y, float z, float radius) {
		c = Point(x, y, z);
		r = radius;
	}

private:
	Point c;
	float r;
};
#endif