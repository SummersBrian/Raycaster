#include <stdlib.h>
#include <iostream>

#include "BMPImage.h"
#include "scene.h"

using namespace std;

//argv[0] - program name
//argv[1] - scene file name
//argv[2] - image file name
//argv[3] - image pixel width
//argv[4] - image pixel height
int main (int argc, char** argv) {
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

	if (theImage.save(argv[2]) != 1) {
		return 1;
	}

	return 0;
}