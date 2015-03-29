echo off
echo running ambient_light_triangle_sphere
start "" "./Debug/ps3.exe" ./input/ambient_light_triangle_sphere.txt ./output/ambient_light_triangle_sphere.bmp 128 128
echo running direction_light_diffuse_sphere
start "" "./Debug/ps3.exe" ./input/direction_light_diffuse_sphere.txt ./output/direction_light_diffuse_sphere.bmp 128 128
echo running points_lights_diffuse_triangles
start "" "./Debug/ps3.exe" ./input/point_lights_diffuse_triangles.txt ./output/point_lights_diffuse_triangles.bmp 128 128
echo running direction_light_specular_sphere
start "" "./Debug/ps3.exe" ./input/direction_light_specular_sphere.txt ./output/direction_light_specular_sphere.bmp 128 128
echo running shadow_point_lights_diffuse_triangles
start "" "./Debug/ps3.exe" ./input/shadow_point_lights_diffuse_triangles.txt ./output/shadow_point_lights_diffuse_triangles.bmp 128 128
echo running hall_of_mirrors
start "" "./Debug/ps3.exe" ./input/hall_of_mirrors.txt ./output/hall_of_mirrors.bmp 128 128
