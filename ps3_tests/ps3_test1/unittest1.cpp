#include "stdafx.h"
#include "CppUnitTest.h"
#include "shape.h"
#include "vector3.cpp"
#include "scene.h"

#include <cassert>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ps3_test1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestPointInTriangle)
		{
			Vector3 a = Vector3(0, 0, 0);
			Vector3 b = Vector3(2, 0, 0);
			Vector3 c = Vector3(1, 1, 0);
			Triangle t = Triangle(a, b, c);
			
			Assert::AreEqual(t.pointInTriangle(Vector3(1.0, 0.5, 0), a, b, c), true); //inside
			Assert::AreEqual(t.pointInTriangle(Vector3(-1, -1, 0),a,b,c), false); //outside
			Assert::AreEqual(t.pointInTriangle(Vector3(1, 0, 0), a, b, c), true); //on an edge
			Assert::AreEqual(t.pointInTriangle(Vector3(0, 0, 0), a, b, c), true); //on vertex
		}

		TEST_METHOD(TestTriangleIntersection) 
		{
			//triangle centered with eye, 2 units away from eye
			Vector3 a = Vector3(-1, -1, -2);
			Vector3 b = Vector3(1, -1, -2);
			Vector3 c = Vector3(0, 1, -2);
			Triangle t = Triangle(a, b, c);

			//ray straight ahead, through center of triangle 2 units away from eye, 1 unit away from plane
			Vector3 eye = Vector3(0, 0, 0);
			Vector3 direction = Vector3(0, 0, -1);
			direction.normalize();
			float t_0 = FLT_MAX;
			Vector3 surfaceNormal = Vector3();
			float t_prime = t.intersect(eye, direction, t_0, surfaceNormal);
			Assert::IsTrue(t_prime < t_0);

			//ray touches edge of triangle
			direction = Vector3(-0.5f, 0, -2);
			direction.normalize();
			t_prime = t.intersect(eye, direction, t_0, surfaceNormal);
			Assert::IsTrue(t_prime < t_0);

			//ray touches vertex of triangle
			direction = Vector3(1, -1, -2);
			direction.normalize();
			t_prime = t.intersect(eye, direction, t_0, surfaceNormal);
			Assert::IsTrue(t_prime < t_0);

			//ray misses triangle
			direction = Vector3(2, -1, -2);
			direction.normalize();
			t_prime = t.intersect(eye, direction, t_0, surfaceNormal);
			Assert::IsFalse(t_prime < t_0);
			
			//ray goes behind eye and misses triangle
			direction = Vector3(-1, -1, 2);
			direction.normalize();
			t_prime = t.intersect(eye, direction, t_0, surfaceNormal);
			Assert::IsFalse(t_prime < t_0);
			
		}

		TEST_METHOD(TestSphereIntersection)
		{
			//sphere centered with eye, 2 units away from eye
			Vector3 center = Vector3(0, 0, -2);
			float radius = 0.5f;
			Sphere s = Sphere(center, radius);

			//ray straight ahead through center of sphere 2 units away
			Vector3 eye = Vector3(0, 0, 0);
			Vector3 direction = Vector3(0, 0, -2);
			direction.normalize();
			float t_0 = FLT_MAX;
			Vector3 surfaceNormal = Vector3();

			float t_prime = s.intersect(eye, direction, t_0, surfaceNormal);
			Assert::IsTrue(t_prime < t_0);

			//ray tangent to sphere
			direction = Vector3(0.5, 0, -2);
			direction.normalize();
			t_prime = s.intersect(eye, direction, t_0, surfaceNormal);
			Assert::IsTrue(t_prime < t_0);

			//ray misses sphere
			direction = Vector3(2, 0, -2);
			direction.normalize();
			t_prime = s.intersect(eye, direction, t_0, surfaceNormal);
			Assert::IsFalse(t_prime < t_0);

			//ray goes behind eye
			direction = Vector3(-2, 0, 2);
			direction.normalize();
			t_prime = s.intersect(eye, direction, t_0, surfaceNormal);
			Assert::IsFalse(t_prime < t_0);
		}
	};
}