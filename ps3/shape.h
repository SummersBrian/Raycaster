#ifndef SHAPE_H
#define SHAPE_H

#include "vector3.h"
#include "material.h"
#include <cmath>

class Shape {
public:
	//Shape() {}

	float virtual intersect(Vector3 origin, Vector3 direction, float t, Vector3 &surfaceNormal) { return t; }

	const Material &getMaterial() const { return material; }
	
	void setMaterial(Material newMaterial) { material = newMaterial; }

private:
	Material material;
};

class Triangle : public Shape {
public:
	Triangle(Vector3 a, Vector3 b, Vector3 c) {
		tr_a = a;
		tr_b = b;
		tr_c = c;
	}
	float intersect(Vector3 origin, Vector3 direction, float t, Vector3 &surfaceNormal) {
		const float TINY = 0.01;
		//get the normal of the plane
		Vector3 tr_ab = tr_b - tr_a;
		Vector3 tr_ac = tr_c - tr_a;
		Vector3 normal = tr_ab.cross(tr_ac);
		normal.normalize();

		//equation for plane : ax + by + cz + d = 0
		// here a = normal.x, b = normal.y, c = normal.z
		float pl_d = -1.0f * ( ( normal.getX() * tr_a.getX() ) + ( normal.getY() * tr_a.getY() ) + ( normal.getZ() * tr_a.getZ() ) );
		float denominator = (normal.getX() * direction.getX()) + (normal.getY() * direction.getY()) + (normal.getZ() * direction.getZ());

		//if denominator is zero, then the ray is parallel to the plane containing the triangle
		if (denominator == 0) {
			return t;
		}
		else {
			float t_0 = -1.0f * (((normal.getX() * origin.getX()) + (normal.getY() * origin.getY()) + (normal.getZ() * origin.getZ() + pl_d))
				/ denominator);

			//if t_0 is less than 0, then the intersection is behind the camera's view - ignore it
			//if t_0 is less than the parameter t, then we found a closer intersection than t
			if (t_0 < t && t_0 > TINY) {
				
				//check to see if ray intersects the triangle - if point of intersection is in the triangle
				//using orthographic projection to check - ignoring z values
				Vector3 intersection = origin + (direction * t_0); //point of intersection
				
				if (pointInTriangle(intersection, tr_a, tr_b, tr_c)) {
					//if there is an intersection with the triangle, we also want the surface normal
					surfaceNormal = normal;
					return t_0;
				}
				else {
					return t;
				}
			}
			else {
				return t;
			}
		}

	}

	bool sameSide(Vector3 intersection, Vector3 vertexC, Vector3 vertexA, Vector3 vertexB) {
		//using orthographic project -- ignore z values
		intersection.setZ(0.0f);
		vertexC.setZ(0.0f);
		vertexA.setZ(0.0f);
		vertexB.setZ(0.0f);

		//everything in relation to vertexA
		Vector3 testVector = vertexB - vertexA; //vector from A to another vertex on triangle
		Vector3 intersectVector = intersection - vertexA; //vector from A to point of intersection
		Vector3 compareVector = vertexC - vertexA; //vector from A to C

		Vector3 cross1 = testVector.cross(intersectVector);
		Vector3 cross2 = testVector.cross(compareVector);

		if (cross1.dot(cross2) >= 0) {
			return true;
		}
		else {
			return false;
		}
	}

	//uses sameSide() to determine if the intersection is within the triangle by comparing with all edges
	bool pointInTriangle(Vector3 intersection, Vector3 vertexA, Vector3 vertexB, Vector3 vertexC) {
		return sameSide(intersection, vertexC, vertexA, vertexB) && sameSide(intersection, vertexA, vertexB, vertexC) &&
			sameSide(intersection, vertexB, vertexA, vertexC);
	}

private:
	Vector3 tr_a;
	Vector3 tr_b;
	Vector3 tr_c;
};

class Sphere : public Shape {
public:
	Sphere();
	Sphere(Vector3 center, float radius) {
		c = center;
		r = radius;
	}
	Sphere(float x, float y, float z, float radius) {
		c = Vector3(x, y, z);
		r = radius;
	}

	float intersect(Vector3 origin, Vector3 direction, float t, Vector3 &surfaceNormal) {
		Vector3 w_vec = c - origin;
		const double TINY = 1E-3;

		//quadratic constants
		double q_a = 1; // direction.dot(direction) = 1 since direction is normalized
		double q_b = (direction.dot(w_vec)) * -2.0;
		double q_c = w_vec.dot(w_vec) - (r * r);
		double det = (q_b * q_b) - ((q_a * q_c) * 4.0);

		if (det >= TINY) {
			double t_minus = ((q_b * -1.0) - sqrt(det)) / 2.0;
			double t_plus = ((q_b * -1.0) + sqrt(det)) / 2.0;

			//t_minus is the smallest and is greater than 0
			if (t_minus > TINY) {
				//calculate surface normal
				Vector3 normal = origin + (direction * t_minus) - c;
				surfaceNormal = normal;
				surfaceNormal.normalize();
				return t_minus;
			}
			//t_minus is less than 0, but t_plus is greater than 0 and so is the smallest
			else if (t_plus > TINY) {
				//calculate surface normal
				Vector3 normal = origin + (direction * t_plus) - c;
				surfaceNormal = normal;
				surfaceNormal.normalize();
				return t_plus;
			}
			//both are less than 0
			else {
				return t;
			}
		}
		//there is no root
		else {
			return t;
		}
	}

private:
	Vector3 c;
	float r;
};
#endif