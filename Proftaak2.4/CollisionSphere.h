#pragma once
#include "Vec.h"
#include <iostream>


class CollisionSphere
{
	float *x, *y;
	float radius;
public:
	CollisionSphere() = default;

	CollisionSphere(float* x, float* y, float radius)
	{
		this->x = x;
		this->y = y;
		this->radius = radius;
	}

	~CollisionSphere()
	{
	}

	bool collides(Vec2f& other, float radius) const
	{
		std::cout << other.x << "\n";
		float distance = radius + this->radius;
		distance *= distance;

		float a = (*x) + other.x;
		float b = (*y) + other.y;

		float hypotenuse = (a * a) + (b * b);

		return hypotenuse < distance;
	}
};
