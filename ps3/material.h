#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

class Material {
public:
	Material() {}
	Material(Color color, float phongExp, float specularFrac) {
		this->color = color;
		this->phongExp = phongExp;
		this->specularFrac = specularFrac;
	}

private:
	Color color;
	float phongExp;
	float specularFrac;
};

#endif