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

Color trace(Scene scene, Vector3 origin, Vector3 direction, int recursiveStep);
bool inShadow(Scene scene, Vector3 origin, Vector3 direction, Shape *start);

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
			Color c = trace(theScene, pixelPointLocation, rayDirection, 0);

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
Color trace(Scene scene, Vector3 origin, Vector3 direction, int recursiveStep) {
	
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
	}

		//if we've intersected at least one object
		if (closest != 0) {
			//go through all of the lights in the scene
			Color i_a = Color();
			i_a = closest->getMaterial().getColor() * scene.getAmbientLight();
			Color i_d = Color();
			Color i_s = Color();
			Vector3 intersection = origin + (direction * t_0);
	
			Color reflected = Color();
			for (int l = 0; l < scene.getCountLights(); l++) {
				Vector3 n = surfaceNormal;
				Light *light = scene.getLights()[l];
				Vector3 light_dir = light->getVector();
				float distance = (light_dir - intersection).getMagnitude();
				Vector3 l_vec = light_dir - intersection;
				l_vec.normalize();

				//see if we have a point light or direction light
				DirectionLight *test = dynamic_cast<DirectionLight*>(light);
				//direction light
				if (test != 0) {
					if (inShadow(scene, intersection, light_dir, closest) == false) {
						i_d += light->getColor() * closest->getMaterial().getColor() * fmax(0.0, n.dot(light_dir));
					}
				}
				//point light
				else {
					if (inShadow(scene, intersection, light_dir - intersection, closest) == false) {
						i_d += (light->getColor() * closest->getMaterial().getColor() * fmax(0.0, n.dot(l_vec))) * (1 / (distance * distance));
					}
				}
				if (inShadow(scene, intersection, light_dir, closest) == false) {
					light_dir.normalize();
					Vector3 reflection = (n * (n.dot(light_dir) * 2.0f)) - light_dir;
					float abc = reflection.dot(direction);
					i_s += closest->getMaterial().getColor() * closest->getMaterial().getSpecularFrac()
						* pow(fmax(0.0, reflection.dot(direction * -1.0f)), closest->getMaterial().getPhongExp());
				}

				if (closest->getMaterial().getSpecularFrac() > 0 && recursiveStep <= 5) {
					Vector3 v = direction * -1.0f;
					v.normalize();
					Vector3 v_ref = (n * n.dot(v) * 2.0f) - (v);
					reflected += trace(scene, intersection, v_ref, recursiveStep++);
				}
			}
			newColor = i_a + i_d + i_s + reflected;
			newColor.clamp();
		}
	
	return newColor;
	
	/*
	//for each shape in the scene
	float t_0 = FLT_MAX;
	float t_prime = t_0;
	Shape *closest = NULL;
	Vector3 surfaceNormal = Vector3();Color newColor = Color();
	for (int k = 0; k < scene.getCountShapes(); k++) {
		//get the intersection of the ray and the shape - returns the value of t_prime for the intersection and gets the surface normal
		t_prime = scene.getShapes()[k]->intersect(origin, direction, t_0, surfaceNormal);

		//save the closest intersection
		if (t_prime < t_0) {
			t_0 = t_prime;
			closest = scene.getShapes()[k];
		}
	}

		//if we've intersected at least one object
		if (closest != 0) {
			//go through all of the lights in the scene and compute the color at the intersection point
			Color i_a = Color(); //ambient light
			i_a = closest->getMaterial().getColor() * scene.getAmbientLight();

			Color i_d = Color(); //diffuse light
			Color i_s = Color(); //specular light

			Color reflected = Color(); //reflected light

			Vector3 intersection = origin + (direction * t_0); //point of intersection

			//for all lights in the scene
			for (int l = 0; l < scene.getCountLights(); l++) {

				Vector3 n = surfaceNormal;
				Light *light = scene.getLights()[l];
				Vector3 light_vec = light->getVector();
				Vector3 light_pos = light_vec - intersection;
				float distance = (light_pos - intersection).getMagnitude();
				light_pos.normalize();

				//see if we have a point light or direction light
				DirectionLight *test = dynamic_cast<DirectionLight*>(light);

				bool inShadow = false;
				//direction light
				if (test != 0) {
					/*
					Shape *blockingShape = NULL;
					float t_1 = FLT_MAX;
					float t1_prime = t_1;
					for (int s = 0; s < scene.getCountShapes(); s++) {
						if (!scene.getShapes()[s]->equals(closest)) {
							t1_prime = scene.getShapes()[s]->intersect(intersection, light_vec, t_1, Vector3());
							if (t1_prime < t_1) {
								inShadow = true;
								//i_d += closest->getMaterial().getColor();
								break;
							}
						}
					}
					if (inShadow == false) {
						i_d += light->getColor() * closest->getMaterial().getColor() * fmax(0.0, n.dot(light_vec));
					}
				}
				//point light
				else {
					/*
					Shape *blockingShape = NULL;
					float t_1 = FLT_MAX;
					float t1_prime = t_1;
					for (int s = 0; s < scene.getCountShapes(); s++) {
						if (!scene.getShapes()[s]->equals(closest)) {
							t1_prime = scene.getShapes()[s]->intersect(intersection, light_vec - intersection, t_1, Vector3());
							if (t1_prime < t_1) {
								inShadow = true;
								//i_d += closest->getMaterial().getColor();
								break;
							}
						}
					}
					if (inShadow == false) {
						i_d += (light->getColor() * closest->getMaterial().getColor() * fmax(0.0, n.dot(light_pos))) * (1 / (distance * distance));
					}
				}
				//specular lighting
				if (inShadow == false) {
					light_vec.normalize();
					Vector3 r_vec = (n * (n.dot(light_vec) * 2.0f)) - (light_vec);
					float abc = r_vec.dot(direction);
					i_s += closest->getMaterial().getColor() * closest->getMaterial().getSpecularFrac()
						* pow(fmax(0.0, r_vec.dot(direction * -1.0f)), closest->getMaterial().getPhongExp());
				}
				else {
					//i_s += closest->getMaterial().getColor();
				}

				//cast rays if object is reflective
				if (closest->getMaterial().getSpecularFrac() > 0 && recursiveStep <= 5) {
					Vector3 v = direction * -1.0f;
					v.normalize();
					Vector3 v_ref = (n * n.dot(v) * 2.0f) - (v);
					reflected += trace(scene, intersection, v_ref, recursiveStep++);
				}
				
			}
			newColor = i_a + i_d + i_s + reflected;
			newColor.clamp();
			if (newColor.getR() == 0.0f && newColor.getG() == 0.0f && newColor.getB() == 0.0f) {
				newColor;
			}
		}
	return newColor;
	*/

}

bool inShadow(Scene scene, Vector3 origin, Vector3 direction, Shape *start) {
	float t1 = FLT_MAX;
	for (int s = 0; s < scene.getCountShapes(); s++) {
		if (start->equals(scene.getShapes()[s]) == false) {
			t1 = scene.getShapes()[s]->intersect(origin, direction, FLT_MAX, Vector3());
			if (t1 < FLT_MAX) {
				return true;
			}
		}
	}
	return false;
}