#include "HitableList.h"

// @Todo(Darren): Remove this class when i implement BVH
HitableList::HitableList() { }

HitableList::HitableList(Hitable **list, int size)
	: hitableList(list), listSize(size)
{

}

HitableList::~HitableList()
{
	delete[] hitableList;
}

bool HitableList::Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const
{
	bool hitAnything = false;
	float closestSoFar = tMax;

	for (int i = 0; i < listSize; i++)
	{
		if (hitableList[i]->Hit(ray, tMin, closestSoFar, rec))
		{
			hitAnything = true;
			closestSoFar = rec.t;
		}
	}

	return hitAnything;
}

bool HitableList::BoundingBox(float t0, float t1, AABB &box) const
{
	if (listSize < 1)
		return false;

	AABB tempBox;
	bool firstTrue = hitableList[0]->BoundingBox(t0, t1, tempBox);
	if (!firstTrue)
		return false;
	else
		box = tempBox;

	for (int i = 1; i < listSize; i++)
	{
		if (hitableList[0]->BoundingBox(t0, t1, box))
			box = box.GetSurroundingBox(box, tempBox);
		else
			return false;
	}

	return true;
}