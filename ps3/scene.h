#ifndef SCENE_H
#define SCENE_H

#include "vector3.h"
#include "color.h"
#include "shape.h"

class Scene {
public:
	Scene();

	//Returns 1 on success, 0 on failure
	int parse(const char *inputFileName);

	const Vector3 &getEyePosition() const {return eyePosition;}
	const Vector3 &getEyeDirection() const {return eyeDirection;}
	const Vector3 &getEyeUp() const {return eyeUp;}
	const Vector3 &getEyeRight() const {return eyeRight;}
	float getFieldOfViewY() const {return fieldOfViewY;}

	const Color &getAmbientLight() const {return ambientLight;}

	Shape **getShapes() const { return shapes; }
	int getCountShapes() const { return countShapes; }
	int getMaxShapes() const { return maxShapes; }

private:
	Vector3 eyePosition;
	Vector3 eyeDirection;
	Vector3 eyeUp;
	Vector3 eyeRight;
	float fieldOfViewY;

	Color ambientLight;

	Shape **shapes;
	int maxShapes;
	int countShapes;
};

#endif