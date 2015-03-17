#ifndef POINT3_H
#define	POINT3_H

#include "vector3.h"

class Point3 {
public:
	Point3();
	Point3(const Point3 &b);
	Point3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }

	void setX(float newX) { x = newX; }
	void setY(float newY) { y = newY; }
	void setZ(float newZ) { z = newZ; }

	void setXYZ(float newX, float newY, float newZ) { setX(newX); setY(newY); setZ(newZ); }

	Vector3 operator-(const Point3 &b) const;
	Point3 operator+(const Vector3 &b) const;
	Point3 operator-(const Vector3 &b) const;

	/*
	Vector3 & operator-=(const Point3 &rhs) const;
	Point3 & operator+=(const Vector3 &rhs) const;
	Point3 & operator-=(const Vector3 &rhs) const;
	*/

private:
	float x;
	float y;
	float z;
};
#endif