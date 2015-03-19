#ifndef SHAPE_H
#define SHAPE_H

#include "vector3.h"

class Shape {
public:
	Shape() {}
	float virtual intersect(Vector3 origin, Vector3 direction, float t, Vector3 &surfaceNormal) { return t; }
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
		tr_a = a;
		tr_b = b;
		tr_c = c;
	}
	float intersect(Vector3 origin, Vector3 direction, float t, Vector3 &surfaceNormal) {

		//get the normal of the plane
		Vector3 tr_ab = tr_b - tr_a;
		Vector3 tr_ac = tr_c - tr_a;
		Vector3 normal = tr_ab.cross(tr_ac);

		//equation for plane : ax + by + cz + d = 0
		// here a = normal.x, b = normal.y, c = normal.z
		//float pl_d = -1.0f * ( ( normal.getX() * tr_a.getX() ) + ( normal.getY() * tr_a.getY() ) + ( normal.getZ() * tr_a.getZ() ) );
		float denominator = (normal.getX() * direction.getX()) + (normal.getY() * direction.getY()) + (normal.getZ() * direction.getZ());

		//if denominator is zero, then the ray is parallel to the line
		if (denominator == 0) {
			return t;
		}
		else {
			float t_0 = -1.0f * (((normal.getX() * origin.getX()) + (normal.getY() * origin.getY()) + (normal.getZ() * origin.getZ()))
				/ denominator);

			//if t_0 is less than 0, then the intersection is behind the camera's view - ignore it
			//if t_0 is less than the parameter t, then we found a closer intersection than t
			if (t_0 < t && t_0 > 0) {
				surfaceNormal = normal;
				return t_0;
			}
			else {
				return t;
			}
		}

	}

private:
	Vector3 tr_a;
	Vector3 tr_b;
	Vector3 tr_c;
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