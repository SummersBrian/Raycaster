#ifndef SHAPE_H
#define SHAPE_H

#include "vector3.h"

class Shape {
public:
	Shape() {}
	float virtual intersect(Vector3 origin, Vector3 direction, float t, Vector3 &surfaceNormal) { return t; }
};

class Line : public Shape {
public:
	Line();
	Line(Vector3 start, Vector3 end) {
		this->start = start;
		this->end = end;
	}
	const Vector3 &getStartPoint() const { return start; }
	const Vector3 &getendPoint() const { return end; }

private:
	Vector3 start;
	Vector3 end;
};

class Triangle : public Shape {
public:
	Triangle(Vector3 a, Vector3 b, Vector3 c) {
		tr_a = a;
		tr_b = b;
		tr_c = c;
	}
	float intersect(Vector3 origin, Vector3 direction, float t, Vector3 &surfaceNormal) {

		//get the normal of the plane
		Vector3 tr_ab = tr_b - tr_a;
		Vector3 tr_ac = tr_c - tr_a;
		Vector3 normal = tr_ab.cross(tr_ac);

		//equation for plane : ax + by + cz + d = 0
		// here a = normal.x, b = normal.y, c = normal.z
		//float pl_d = -1.0f * ( ( normal.getX() * tr_a.getX() ) + ( normal.getY() * tr_a.getY() ) + ( normal.getZ() * tr_a.getZ() ) );
		float denominator = (normal.getX() * direction.getX()) + (normal.getY() * direction.getY()) + (normal.getZ() * direction.getZ());

		//if denominator is zero, then the ray is parallel to the plane containing the triangle
		if (denominator == 0) {
			return t;
		}
		else {
			float t_0 = -1.0f * (((normal.getX() * origin.getX()) + (normal.getY() * origin.getY()) + (normal.getZ() * origin.getZ()))
				/ denominator);

			//if t_0 is less than 0, then the intersection is behind the camera's view - ignore it
			//if t_0 is less than the parameter t, then we found a closer intersection than t
			if (t_0 < t && t_0 > 0) {
				
				//check to see if ray intersects the triangle - if point of intersection is in the triangle
				//using orthographic projection to check - ignoring z values
				Vector3 intersection = origin + (direction * t_0); //point of intersection
				
				if (pointInTriangle(intersection, tr_a, tr_b, tr_c)) {
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

	/*
		This function tests to see if the intersection point is on the same side as the compareVertex using orthographic projection.
		After projection, all the points will remain in the same orientation/direction relative to one another, so the point will not
		change sides after projection.

		intersection is the point of interest
		compareVertex is the vertex on the triangle we're using to compare to see if the intersection is on the same side
		testVertex1 and testVertex2 make up the edge we are testing the intersection with

		Let triangle ABC have vertices A at (0,0), B at (2,0) and C at (1,1). We wish to see which side point P is on with respect
		to the edge we are testing. Let testVertex1 = A, testVertex2 = B, testEdge = testVertex2 - testVertex1, and let 
		compareVertex = C. We take the dot product of C-A with testEdge. We then take the dot product of P-A with testEdge and 
		compare the signs of the two dot products. If they both have the same sign, then P is on the same side of AB as vertex C is.

		Use this test in conjuction with pointInTriangle() to test the intersection with all three edges of the triangle.
	*/
	bool sameSide(Vector3 intersection, Vector3 compareVertex, Vector3 testVertex1, Vector3 testVertex2) {
		//using orthographic project -- ignore z values
		intersection.setZ(0.0f);
		compareVertex.setZ(0.0f);
		testVertex1.setZ(0.0f);
		testVertex2.setZ(0.0f);

		Vector3 testEdge = testVertex2 - testVertex1;
		Vector3 aToIntersection = intersection - testVertex1;
		Vector3 compareEdge = compareVertex - testVertex1;

		float compareDir = testEdge.dot(compareEdge);
		float intersectDir = testEdge.dot(aToIntersection);

		//the point of intersection is on the testEdge -- it's on the edge -- same side
		//both are on the same side
		if (intersectDir == 0 || (intersectDir > 0 && compareDir > 0)
				|| (intersectDir < 0 && compareDir < 0)) {
			return true;
		}
		//intersection is on opposite side
		else {
			return false;
		}
	}

	//uses sameSide() to determine if the intersection is within the triangle by comparing with all edges
	bool pointInTriangle(Vector3 intersection, Vector3 vertexA, Vector3 vertexB, Vector3 vertexC) {
		return sameSide(intersection, vertexC, vertexA, vertexB) && sameSide(intersection, vertexA, vertexB, vertexC) &&
			sameSide(intersection, vertexB, vertexC, vertexA);
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

private:
	Vector3 c;
	float r;
};
#endif