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
		
		TEST_METHOD(TestMethod1)
		{
			Vector3 a = Vector3(0, 0, 0);
			Vector3 b = Vector3(2, 0, 0);
			Vector3 c = Vector3(1, 1, 0);
			Triangle t = Triangle(a, b, c);
			
			Assert::AreEqual(t.pointInTriangle(Vector3(1.0, 0.5, 0), a, b, c), true);
			Assert::AreEqual(t.pointInTriangle(Vector3(-1, -1, 0),a,b,c), false);
		}

	};
}