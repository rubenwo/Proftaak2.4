#pragma once
#include "Vec.h"
#include <iostream>


class CollisionSphere
{
	Vec3f center;
	float radius;
public:
	CollisionSphere() = default;

	CollisionSphere(Vec3f& center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}

	~CollisionSphere()
	{
	}

	Vec3f min(const Vec3f& other) const
	{
		Vec3f result(center.x - other.x, center.y - other.y, center.z - other.z);
		return result;
	}

	float lengthSq(const Vec3f& vec) const
	{
		return (vec.x * vec.x + vec.y * vec.y + vec.z + vec.z);
	}

	bool collides(const CollisionSphere& other) const
	{
		float dist = radius + other.radius;

		Vec3f distance = min(other.center);
		return lengthSq(distance) < dist * dist;
	}

	bool collides(const Vec3f& other, float radius) const
	{
		float area = this->radius + radius;
		Vec3f distance = min(other);
		std::cout << "Max Area: " << area << "\n";
		std::cout << "Distance SQR: " << lengthSq(distance) << "\n";

		return lengthSq(distance) < area * area;
	}
};
