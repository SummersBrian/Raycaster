//scrap work for ps3

/*
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
			
		
			//compute color at closest intersection point
			if (closest != 0) {
				Color diffuse = Color();
				for (int l = 0; l < theScene.getCountLights(); l++) {
					Vector3 a = surfaceNormal;
					Vector3 b = theScene.getDirectionLights()[l]->getDirectionTo();
					diffuse = a.dot(b) / (a.getMagnitude * b.getMagnitude()) * theScene.getDirectionLights()[l]->getColor();
				}
				Color newColor = closest->getMaterial().getColor() * theScene.getAmbientLight();
				newColor.normalize();
				theImage.writePixel(j, i-1, newColor.getR(), newColor.getG(), newColor.getB());
			}
			else {
				theImage.writePixel(j, i-1, 0.0f, 0.0f, 0.0f);
			}*/