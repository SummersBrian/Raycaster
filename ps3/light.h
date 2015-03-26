#ifndef LIGHT_H
#define LIGHT_H

#include "vector3.h"
#include "color.h"

class Light {
public:
	Light(float r, float g, float b) { 
		intensity = Color(r, g, b);
	}
	const Color &getColor() const { return intensity; }
	virtual const Vector3 &getVector() const { return Vector3(); }
private:
	Color intensity;
};

class DirectionLight : public Light {
public:
	DirectionLight(float r, float g, float b, float x, float y, float z) : Light (r,g,b){
		directionTo = Vector3(x, y, z);
	}
	
	const Vector3 &getVector() const { return directionTo; }

private:
	Vector3 directionTo;
};

class PointLight : public Light {
public:
	PointLight(float r, float g, float b, float x, float y, float z) : Light(r, g, b) {
		position = Vector3(x, y, z);
	}

	const Vector3 &getVector() const { return position; }

private:
	Vector3 position;
};
#endif
