#ifndef COLOR_H
#define COLOR_H

class Color {
public:
	Color() {setRGB(0, 0, 0);}
	Color(const Color &rhs) {setRGB(rhs.getR(), rhs.getG(), rhs.getB());}
	Color(float newR, float newG, float newB) {setRGB(newR, newG, newB);}

	void setR(float newR) {r = newR;}
	void setG(float newG) {g = newG;}
	void setB(float newB) {b = newB;}
	void setRGB(float newR, float newG, float newB) {setR(newR); setG(newG); setB(newB);}

	float getR() const {return r;}
	float getG() const {return g;}
	float getB() const {return b;}
	void getRGB(float &curR, float &curG, float &curB) const {curR = getR(); curG = getG(); curB = getB();}

	void clamp(); //set RGB to the range [0, 1] by rounding values that are outside the range
	void normalize(); //set RGB to the range [0, 1] by scaling all values such that the hue is preserved

	Color operator+(const Color &rhs) const;
	Color operator*(const Color &rhs) const;
	Color operator*(float rhs) const;

	Color & operator+=(const Color &rhs);
	Color & operator*=(const Color &rhs);
	Color & operator*=(float rhs);

	Color & operator=(const Color &rhs);

private:
	float r, g, b;

	float maxRGB();
	float minRGB();
};

#endif