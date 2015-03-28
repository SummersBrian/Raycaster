#include "vector3.h"

Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(const Vector3 &b) {
	setXYZ(b.getX(), b.getY(), b.getZ());
}

Vector3::Vector3(float newX, float newY, float newZ) {
	setXYZ(newX, newY, newZ);
}

float Vector3::getMagnitude() const {
	return sqrt(getX()*getX() + getY()*getY() + getZ()*getZ());
}

float Vector3::dot(const Vector3 &b) const {
	return (getX()*b.getX() + getY()*b.getY() + getZ()*b.getZ());
}

Vector3 Vector3::cross(const Vector3 &b) const {
	float crossX = getY()*b.getZ() - getZ()*b.getY();
	float crossY = getZ()*b.getX() - getX()*b.getZ();
	float crossZ = getX()*b.getY() - getY()*b.getX();

	Vector3 result(crossX, crossY, crossZ);

	return result;
}

void Vector3::normalize() {
	float magnitude = getMagnitude();

	if (magnitude == 0)
		return;

	setXYZ(getX()/magnitude, getY()/magnitude, getZ()/magnitude);
}

void Vector3::translate(float deltaX, float deltaY, float deltaZ) {
	setXYZ(getX() + deltaX, getY() + deltaY, getZ() + deltaZ);
}

void Vector3::rotateX(float theta) {
	float newY = cos(theta)*getY() - sin(theta)*getZ();
	float newZ = sin(theta)*getY() + cos(theta)*getZ();

	setY(newY);
	setZ(newZ);
}

void Vector3::rotateY(float theta) {
	float newX = cos(theta)*getX() + sin(theta)*getZ();
	float newZ = -sin(theta)*getX() + cos(theta)*getZ();

	setX(newX);
	setZ(newZ);
}

void Vector3::rotateZ(float theta) {
	float newX = cos(theta)*getX() - sin(theta)*getY();
	float newY = sin(theta)*getX() + cos(theta)*getY();

	setX(newX);
	setY(newY);
}

void Vector3::rotate(float theta, const Vector3 &axis) {
	Vector3 u(axis);
	u.normalize();

	float S[3][3] = {{0,         -u.getZ(), u.getY()},
	                 {u.getZ(),  0,         -u.getX()},
	                 {-u.getY(), u.getX(),  0}};

	float uuT[3][3] = {{u.getX()*u.getX(), u.getX()*u.getY(), u.getX()*u.getZ()},
	                   {u.getY()*u.getX(), u.getY()*u.getY(), u.getY()*u.getZ()},
	                   {u.getZ()*u.getX(), u.getZ()*u.getY(), u.getZ()*u.getZ()}};

	float newX = (uuT[0][0] + cos(theta)*(1-uuT[0][0]) + sin(theta)*S[0][0])*getX() +
	             (uuT[0][1] + cos(theta)*(0-uuT[0][1]) + sin(theta)*S[0][1])*getY() +
				 (uuT[0][2] + cos(theta)*(0-uuT[0][2]) + sin(theta)*S[0][2])*getZ();

	float newY = (uuT[1][0] + cos(theta)*(0-uuT[1][0]) + sin(theta)*S[1][0])*getX() +
	             (uuT[1][1] + cos(theta)*(1-uuT[1][1]) + sin(theta)*S[1][1])*getY() +
				 (uuT[1][2] + cos(theta)*(0-uuT[1][2]) + sin(theta)*S[1][2])*getZ();

	float newZ = (uuT[2][0] + cos(theta)*(0-uuT[2][0]) + sin(theta)*S[2][0])*getX() +
	             (uuT[2][1] + cos(theta)*(0-uuT[2][1]) + sin(theta)*S[2][1])*getY() +
				 (uuT[2][2] + cos(theta)*(1-uuT[2][2]) + sin(theta)*S[2][2])*getZ();

	setXYZ(newX, newY, newZ);
}

Vector3 Vector3::operator+(const Vector3 &b) const {
	Vector3 result(getX() + b.getX(), getY() + b.getY(), getZ() + b.getZ());

	return result;
}

Vector3 Vector3::operator-(const Vector3 &b) const {
	Vector3 result(getX() - b.getX(), getY() - b.getY(), getZ() - b.getZ());

	return result;
}

Vector3 Vector3::operator*(const Vector3 &b) const {
	Vector3 result(getX() * b.getX(), getY() * b.getY(), getZ() * b.getZ());

	return result;
}

Vector3 Vector3::operator*(float b) const {
	Vector3 result(getX()*b, getY()*b, getZ()*b);

	return result;
}

Vector3 & Vector3::operator+=(const Vector3 &rhs) {
	setXYZ(getX() + rhs.getX(), getY() + rhs.getY(), getZ() + rhs.getZ());

	return *this;
}

Vector3 & Vector3::operator-=(const Vector3 &rhs) {
	setXYZ(getX() - rhs.getX(), getY() - rhs.getY(), getZ() - rhs.getZ());

	return *this;
}

Vector3 & Vector3::operator*=(const Vector3 &rhs) {
	setXYZ(getX() * rhs.getX(), getY() * rhs.getY(), getZ() * rhs.getZ());

	return *this;
}

Vector3 & Vector3::operator*=(float b) {
	setXYZ(getX()*b, getY()*b, getZ()*b);

	return *this;
}

Vector3 & Vector3::operator=(const Vector3 &rhs) {
	setXYZ(rhs.getX(), rhs.getY(), rhs.getZ());

	return *this;
}

