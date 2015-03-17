#include "point3.h"
#include "vector3.h"

//vector <- point - point
Vector3 Point3::operator-(const Point3 &b) const {
	Vector3 result(getX() - b.getX(), getY() - b.getY(), getZ() - b.getZ());
	return result;
}

//point <- point + vector
Point3 Point3::operator+(const Vector3 &b) const {
	Point3 result(getX() + b.getX(), getY() + b.getY(), getZ() + b.getZ());
	return result;
}

//point <- point - vector
Point3 Point3::operator-(const Vector3 &b) const {
	Point3 result(getX() - b.getX(), getY() - b.getY(), getZ() - b.getZ());
	return result;
}