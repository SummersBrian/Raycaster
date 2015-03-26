/*
CMSC427 Spring 2015 Problem Set 3 - Ray Tracing
Brian Summers - 110656609
3/26/15
*/

#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "BMPImage.h"
#include "scene.h"

using namespace std;

Color trace(Scene scene, Vector3 origin, Vector3 direction);

//argv[0] - program name
//argv[1] - scene file name
//argv[2] - image file name
//argv[3] - image pixel width
//argv[4] - image pixel height
int main (int argc, char** argv) {
	const float PI = 3.1415927;

	if (argc != 5) {
		cout << "Usage: " << argv[0] << " inputFile outputFile imageWidth imageHeight" << endl;
		return 1;
	}

	int imageWidth = atoi(argv[3]);
	int imageHeight = atoi(argv[4]);

	Scene theScene;
	if (theScene.parse(argv[1]) != 1) {
		return 1;
	}

	BMPImage theImage(imageWidth, imageHeight);

	//TODO
	//raytrace the scene

	//image plane setup
	float pThetaYRad = PI * (theScene.getFieldOfViewY() / 180); //y-field of view in radians
	float pAspectRatio = imageWidth / imageHeight; //window's aspect ratio
	float pHeight = 2 * tan(pThetaYRad / 2);
	float pWidth = pHeight * pAspectRatio;
	//Vector3 pImageCenter = Vector3(0, 0, -1);
	//float pPixelWidth = pWidth / imageWidth, pPixelHeight = pHeight / imageHeight;

	//for each pixel in the BMPImage
	//starting world coordinate positions, top left of image is (0, 0)

	for (int i = 1; i <= imageHeight; i++) {
		float rowVertOffset = pHeight * (( (float) i / imageHeight) - 0.5f); //vertical offset for the row
		for (int j = 0; j < imageWidth; j++) {

			//cast a ray from the focal point through the pixel
			float colHorizOffset = pWidth*(( (float) j / imageWidth ) - 0.5f); //horizontal offset for the column
			Vector3 pixelPointLocation = theScene.getEyePosition() + (theScene.getEyeRight() * colHorizOffset) 
				+ ( theScene.getEyeUp() * rowVertOffset ) - ( theScene.getEyeDirection() * -1.0f ); //location of the pixel in the image
			Vector3 rayDirection = pixelPointLocation - theScene.getEyePosition(); //direction vector for the ray from eye to pixel
 			rayDirection.normalize();

			//shoot a ray into the scene passing through pixel
			Color c = trace(theScene, pixelPointLocation, rayDirection);
			theImage.writePixel(j, i - 1, c.getR(), c.getG(), c.getB());
		}
	}

	if (theImage.save(argv[2]) != 1) {
		return 1;
	}

	return 0;
}

/*
	Shoot a ray into scene from origin in direction. Detect intersections of the ray with objects in the scene,
	get the color at the intersection and return the color.
*/
Color trace(Scene scene, Vector3 origin, Vector3 direction) {

	//for each shape in the scene
	float t_0 = FLT_MAX;
	float t_prime = t_0;
	Shape *closest = NULL;
	Vector3 surfaceNormal = Vector3();
	Color newColor = Color();
	for (int k = 0; k < scene.getCountShapes(); k++) {
		//get the intersection of the ray and the shape - returns the value of t_prime for the intersection and gets the surface normal
		t_prime = scene.getShapes()[k]->intersect(origin, direction, t_0, surfaceNormal);

		//save the closest intersection
		if (t_prime < t_0) {
			t_0 = t_prime;
			closest = scene.getShapes()[k];
		}

		//if we've intersected at least one object
		if (closest != 0) {
			//Color diffuse = Color();
			//go through all of the lights in the scene
			Color i_a = Color();
			i_a = closest->getMaterial().getColor() * scene.getAmbientLight();
			Color i_d = Color();
			Color i_s = Color();
			Vector3 intersection = origin + (direction * t_0);
			for (int l = 0; l < scene.getCountLights(); l++) {
				Vector3 a = surfaceNormal;
				Light *light = scene.getLights()[l];
				Vector3 b = light->getVector();
				float distance = (b - intersection).getMagnitude();
				Vector3 l_vec = b - intersection;
				l_vec.normalize();

				//see if we have a point light or direction light
				DirectionLight *test = dynamic_cast<DirectionLight*>(light);
				//direction light
				if (test != 0) {
					i_d += light->getColor() * closest->getMaterial().getColor() * fmax(0.0, a.dot(b));
				}
				//point light
				else {
					i_d += (light->getColor() * closest->getMaterial().getColor() * fmax(0.0, a.dot(l_vec))) * (1 / (distance * distance));
				}
				Vector3 reflection = (a * (a.dot(l_vec) * 2.0f)) - l_vec;
				float abc = reflection.dot(direction);
				i_s += closest->getMaterial().getColor() * closest->getMaterial().getSpecularFrac()
					* pow(fmax(0.0, reflection.dot(direction * -1.0f)), closest->getMaterial().getPhongExp());
			}
			newColor = i_a + i_d + i_s;
			newColor.clamp();
		}
	}
	return newColor;
}