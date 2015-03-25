#include "scene.h"

#include <string.h>

#include <iostream>
#include <fstream>

using namespace std;

Scene::Scene() :
	eyePosition(0, 0, 0),
	eyeDirection(0, 0, -1),
	eyeUp(0, 1, 0),
	fieldOfViewY(20),
	ambientLight(0, 0, 0) {

	countShapes = 0;
	maxShapes = 10;
	shapes = new Shape*[maxShapes];
}

int Scene::parse(const char *inputFileName) {
	fstream inputFile;
	Material m;

	inputFile.open(inputFileName, fstream::in);

	if (!inputFile.is_open()) {
		cout << "Error opening input file " << inputFileName << endl;
		return 0;
	}

	int lineNum = 0;

	//parse file
	while (!inputFile.eof()) {
		const int bufferSize = 256;
		char command[bufferSize];
		inputFile.getline(command, bufferSize); ++lineNum;

		//skip comments
		if (command[0] == '#') {
		}

		//skip blank lines
		else if (command[0] == 0) {
		}

		//read viewing parameters
		else if (strcmp(command, "camera") == 0) {	
			float eyePositionX, eyePositionY, eyePositionZ;
			float eyeLookAtX, eyeLookAtY, eyeLookAtZ;
			float eyeUpX, eyeUpY, eyeUpZ;

			inputFile >> eyePositionX >> eyePositionY >> eyePositionZ; ++lineNum;
			inputFile >> eyeLookAtX >> eyeLookAtY >> eyeLookAtZ; ++lineNum;
			inputFile >> eyeUpX >> eyeUpY >> eyeUpZ; ++lineNum;
			inputFile >> fieldOfViewY; ++lineNum;

			inputFile.ignore(); //extract final newline

			eyePosition.setXYZ(eyePositionX, eyePositionY, eyePositionZ);

			Vector3 eyeLookAt(eyeLookAtX, eyeLookAtY, eyeLookAtZ);
			eyeDirection = eyeLookAt - eyePosition;
			eyeDirection.normalize();

			eyeUp.setXYZ(eyeUpX, eyeUpY, eyeUpZ);
			eyeUp.normalize();

			eyeRight = eyeDirection.cross(eyeUp);
		}

		//read ambient light
		else if (strcmp(command, "ambientLight") == 0) {
			float r, g, b;

			inputFile >> r >> g >> b; ++lineNum;

			inputFile.ignore(); //extract final newline

			ambientLight.setRGB(r, g, b);
		}

		//read direction light
		else if (strcmp(command, "directionLight") == 0) {
			float r, g, b;
			float x, y, z;

			inputFile >> r >> g >> b; ++lineNum;
			inputFile >> x >> y >> z; ++lineNum;

			inputFile.ignore(); //extract final newline

			//TODO
			//add direction lights
		}

		//read point light
		else if (strcmp(command, "pointLight") == 0) {
			float r, g, b;
			float x, y, z;

			inputFile >> r >> g >> b; ++lineNum;
			inputFile >> x >> y >> z; ++lineNum;

			inputFile.ignore(); //extract final newline

			//TODO
			//add point lights
		}

		//read material
		else if (strcmp(command, "material") == 0) {
			float r, g, b;
			float phongExponent;
			float specularFraction;

			inputFile >> r >> g >> b; ++lineNum;
			inputFile >> phongExponent; ++lineNum;
			inputFile >> specularFraction; ++lineNum;

			inputFile.ignore(); //extract final newline

			//TODO
			//store current material setting
			Color color = Color(r, g, b);
			m = Material(color, phongExponent, specularFraction);
		}

		//read triangle
		else if (strcmp(command, "triangle") == 0) {
			float x1, y1, z1;
			float x2, y2, z2;
			float x3, y3, z3;

			inputFile >> x1 >> y1 >> z1; ++lineNum;
			inputFile >> x2 >> y2 >> z2; ++lineNum;
			inputFile >> x3 >> y3 >> z3; ++lineNum;

			inputFile.ignore(); //extract final newline

			//TODO
			//add triangles
			countShapes++;
			if (countShapes >= maxShapes) {
				maxShapes *= 2;
				Shape **temp = new Shape*[maxShapes];
				for (int i = 0; i < countShapes; i++) {
					temp[i] = shapes[i];
				}
				delete[] shapes;
				shapes = temp;
			}
			else {
				Triangle *tr = new Triangle(Vector3(x1, y1, z1), Vector3(x2, y2, z2), Vector3(x3, y3, z3));
				tr->setMaterial(m);
				shapes[countShapes - 1] = tr;
			}

		}

		//read sphere
		else if (strcmp(command, "sphere") == 0) {
			float x, y, z;
			float radius;
		
			inputFile >> x >> y >> z; ++lineNum;
			inputFile >> radius; ++lineNum;

			inputFile.ignore(); //extract final newline

			//TODO
			//add spheres
			countShapes++;
			if (countShapes >= maxShapes) {
				maxShapes *= 2;
				Shape **temp = new Shape*[maxShapes];
				for (int i = 0; i < countShapes; i++) {
					temp[i] = shapes[i];
				}
				delete[] shapes;
				shapes = temp;
			}
			else {
				Sphere *s = new Sphere(x, y, z, radius);
				s->setMaterial(m);
				shapes[countShapes - 1] = s;
			}
		}

		else {
			cout << "Line " << lineNum << ": Unexpected command " << command << endl;
			inputFile.close();
			return 0;
		}
	}

	inputFile.close();

	return 1;
}