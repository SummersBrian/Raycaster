#ifndef SHAPE_H
#define SHAPE_H

#include "vector3.h"

class Shape {
public:
	Shape();
	float virtual intersect(Vector3 ray);
};

class Line : public Shape {
public:
	Line();
	Line(Vector3 start, Vector3 end) {
		this->start = start;
		this->end = end;
	}
	const Vector3 &getStartPoint() const { return start; }
	const Vector3 &getendPoint() const { return end; }

private:
	Vector3 start;
	Vector3 end;
};

class Triangle : public Shape {
public:
	Triangle(Vector3 a, Vector3 b, Vector3 c) {
		ab = Line(a, b);
		bc = Line(b, c);
		ca = Line(c, a);
	}
	float intersect(Vector3 ray) {
		
	}

private:
	Line ab;
	Line bc;
	Line ca;
};

class Sphere : public Shape {
public:
	Sphere();
	Sphere(Vector3 center, float radius) {
		c = center;
		r = radius;
	}
	Sphere(float x, float y, float z, float radius) {
		c = Vector3(x, y, z);
		r = radius;
	}

private:
	Vector3 c;
	float r;
};
#endif