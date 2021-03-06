#include "AABB.h"

AABB::AABB() { }

AABB::AABB(const Vector3 &a, const Vector3 &b)
	: min(a), max(b)
{

}

bool AABB::Hit(const Ray &ray, float &tMin, float &tMax) const
{
	for (int a = 0; a < 3; a++) 
	{
		float t0 = fminf((min[a] - ray.Origin()[a]) / ray.Direction()[a],
			(max[a] - ray.Origin()[a]) / ray.Direction()[a]);
		float t1 = fmaxf((min[a] - ray.Origin()[a]) / ray.Direction()[a],
			(max[a] - ray.Origin()[a]) / ray.Direction()[a]);

		tMin = fmaxf(t0, tMin);
		tMax = fminf(t1, tMax);

		if (tMax <= tMin)
			return false;
	}

	return true;
}

uint8_t AABB::GetLongestAxis() const
{
	Vector3 vec = max - min;

	if (vec.x > vec.y && vec.x > vec.z)	return 0;
	if (vec.y > vec.x && vec.y > vec.z)	return 1;
	if (vec.z > vec.x && vec.z > vec.y)	return 2;

	return 0;
}

Vector3 AABB::GetCentroidPoint() const
{
	return Vector3(0.5f * min + 0.5f * max);
}

AABB AABB::ExpandBoundingBox(const AABB &box)
{
	Vector3 min(fminf(min.x, box.min.x), fminf(min.y, box.min.y), fminf(min.z, box.min.z));
	Vector3 max(fmaxf(max.x, box.max.x), fmaxf(max.y, box.max.y), fmaxf(max.z, box.max.z));

	return AABB(min, max);
}

AABB AABB::GetSurroundingBox(const AABB &box0, const AABB& box1)
{
	Vector3 min(fminf(box0.min.x, box1.min.x), fminf(box0.min.y, box1.min.y), fminf(box0.min.z, box1.min.z));
	Vector3 max(fmaxf(box0.max.x, box1.max.x), fmaxf(box0.max.y, box1.max.y), fmaxf(box0.max.z, box1.max.z));

	return AABB(min, max);
}