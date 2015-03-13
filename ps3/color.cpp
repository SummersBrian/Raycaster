#include "color.h"

#include <math.h>

float Color::maxRGB() {
	if ((getR() >= getG()) && (getR() >= getB())) {
		return getR();
	}

	if ((getG() >= getR()) && (getG() >= getB())) {
		return getG();
	}

	return getB();
}

float Color::minRGB() {
	if ((getR() <= getG()) && (getR() <= getB())) {
		return getR();
	}

	if ((getG() <= getR()) && (getG() <= getB())) {
		return getG();
	}

	return getB();
}

void Color::clamp() {
	if (getR() > 1.0f) setR(1.0f);
	if (getG() > 1.0f) setG(1.0f);
	if (getB() > 1.0f) setB(1.0f);

	if (getR() < 0.0f) setR(0.0f);
	if (getG() < 0.0f) setG(0.0f);
	if (getB() < 0.0f) setB(0.0f);
}

void Color::normalize() {
	//convert to HSV
	float H, S, V;

	float maxColor = maxRGB();
	float minColor = minRGB();

	if (maxColor == minColor) {
		H = 0;
	}
	else {
		if (getR() == minColor) {
			H = 3 - (getG() - getB())/(maxColor - minColor);
		}
		else if (getG() == minColor) {
			H = 5 - (getB() - getR())/(maxColor - minColor);
		}
		else {
			H = 1 - (getR() - getG())/(maxColor - minColor);
		}
	}

	S = maxColor - minColor;

	V = maxColor;

	//normalize color
	if (V > 1.0f) V = 1.0f;
	if (V < 0.0f) V = 0.0f;

	if (S > 1.0f) S = 1.0f;
	if (S < 0.0f) S = 0.0f;

	//convert to RGB
	int intH = (int)floor(H);
	float fracH = H - intH;

	if (intH%2 == 0) {
		fracH = 1-fracH;
	}

	float M = V - S;
	float N = V - fracH*S;

	if      (intH == 0) setRGB(V, N, M);
	else if (intH == 1) setRGB(N, V, M);
	else if (intH == 2) setRGB(M, V, N);
	else if (intH == 3) setRGB(M, N, V);
	else if (intH == 4) setRGB(N, M, V);
	else if (intH == 5) setRGB(V, M, N);
	else                setRGB(V, N, M);
}

Color Color::operator+(const Color &rhs) const {
	Color result(getR() + rhs.getR(), getG() + rhs.getG(), getB() + rhs.getB());

	return result;
}

Color Color::operator*(const Color &rhs) const {
	Color result(getR() * rhs.getR(), getG() * rhs.getG(), getB() * rhs.getB());

	return result;
}

Color Color::operator*(float rhs) const {
	Color result(getR() * rhs, getG() * rhs, getB() * rhs);

	return result;
}

Color & Color::operator+=(const Color &rhs) {
	setRGB(getR() + rhs.getR(), getG() + rhs.getG(), getB() + rhs.getB());
	return *this;
}

Color & Color::operator*=(const Color &rhs) {
	setRGB(getR() * rhs.getR(), getG() * rhs.getG(), getB() * rhs.getB());
	return *this;
}

Color & Color::operator*=(float rhs) {
	setRGB(getR() * rhs, getG() * rhs, getB() * rhs);
	return *this;
}

Color & Color::operator=(const Color &rhs) {
	setRGB(rhs.getR(), rhs.getG(), rhs.getB());
	return *this;
}