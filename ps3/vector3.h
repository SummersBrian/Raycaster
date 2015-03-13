#ifndef VECTOR3
#define VECTOR3

#include <math.h>

class Vector3 {
public:
	Vector3();
	Vector3(const Vector3 &b);
	Vector3(float newX, float newY, float newZ);

	float getX() const {return x;}
	float getY() const {return y;}
	float getZ() const {return z;}

	float dot(const Vector3 &b) const;
	Vector3 cross(const Vector3 &b) const;

	float getMagnitude() const;

	void setX(float newX) {x = newX;}
	void setY(float newY) {y = newY;}
	void setZ(float newZ) {z = newZ;}

	void setXYZ(float newX, float newY, float newZ) {setX(newX); setY(newY); setZ(newZ);}

	void normalize();

	void translate(float deltaX, float deltaY, float deltaZ);

	void rotateX(float theta);
	void rotateY(float theta);
	void rotateZ(float theta);

	void rotate(float theta, const Vector3 &axis);

	Vector3 operator+(const Vector3 &b) const;
	Vector3 operator-(const Vector3 &b) const;
	Vector3 operator*(const Vector3 &b) const;
	Vector3 operator*(float b) const;

	Vector3 & operator+=(const Vector3 &rhs);
	Vector3 & operator-=(const Vector3 &rhs);
	Vector3 & operator*=(const Vector3 &rhs);
	Vector3 & operator*=(float b);

	Vector3 & operator=(const Vector3 &rhs);

private:
	float x;
	float y;
	float z;
};

#endif