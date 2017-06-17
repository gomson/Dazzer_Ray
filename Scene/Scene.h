#ifndef SCENE_H
#define SCENE_H

#include <cfloat>
#include <vector>
#include "..\Math\Ray.h"
// NOTE(Darren): Need to include because of incomplete class type with struct HitRecord
#include "..\Materials\Lambertian.h"
#include "..\Objects\Sphere.h"
#include "..\Math\Sampler.h"
#include "..\Camera\Camera.h"
#include "..\IO\PPM_Image.h"
#include "..\Objects\HitableList.h"

class Scene
{
public:
	Scene();
	~Scene();

	void RenderScene();

private:
	Vector3 Color(Ray &ray, HitableList *world, int depth);

	HitableList* TestScene();
	HitableList *sceneObects;
	Camera camera;
	PPM_Image *ppmImage;
	unsigned int width, height, samples;
};

#endif