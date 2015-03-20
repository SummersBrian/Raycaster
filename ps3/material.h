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

	const Color &getColor() const { return color; }
	float getPhongExp() const { return phongExp; }
	float getSpecularFrac() const { return specularFrac; }

	void setColor(Color newColor) { color = newColor; }
	void setPhongExp(float newPhongExp) { phongExp = newPhongExp; }
	void setSpecularFrac(float newSpecularFrac) { specularFrac = newSpecularFrac; }

private:
	Color color;
	float phongExp;
	float specularFrac;
};

#endif