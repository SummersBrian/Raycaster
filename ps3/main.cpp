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
	float halfXOffset = 1.0f / (2.0f * imageWidth);
	float halfYOffset = 1.0f / (2.0f * imageHeight);
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
			
			//for each shape in the scene
			float t_0 = FLT_MAX;
			float t_prime = t_0;
			Shape *closest = NULL;
			Vector3 surfaceNormal = Vector3();
			for (int k = 0; k < theScene.getCountShapes(); k++) {
				//get the intersection of the ray and the shape - returns the value of t_prime for the intersection and gets the surface normal
				t_prime = theScene.getShapes()[k]->intersect(pixelPointLocation, rayDirection, t_0, surfaceNormal);

				if (t_prime < t_0) {
					t_0 = t_prime;
					closest = theScene.getShapes()[k];
				}
			}

			//compute color at intersection point
			if (closest != 0) {
				Color newColor = closest->getMaterial().getColor() * theScene.getAmbientLight();
				newColor.normalize();
				theImage.writePixel(j, i-1, newColor.getR(), newColor.getG(), newColor.getB());
			}
			else {
				theImage.writePixel(j, i-1, 0.0f, 0.0f, 0.0f);
			}
		}
	}

	if (theImage.save(argv[2]) != 1) {
		return 1;
	}

	return 0;
}