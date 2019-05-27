#pragma once
#include "Vec.h"


class Sphere
{
public:
	Vec3f center;
	float radius;

	Vec3f min(const Vec3f& other) const
	{
		Vec3f result(center.x - other.x, center.y - other.y, center.z - other.z);
		return result;
	}

	float lengthSq(Vec3f& vec) const
	{
		return (vec.x * vec.x + vec.y * vec.y + vec.z + vec.z);
	}

	bool collides(const Sphere& other) const
	{
		float dist = radius + other.radius;

		Vec3f distance = min(other.center);
		return lengthSq(distance) < dist * dist;
	}
};
