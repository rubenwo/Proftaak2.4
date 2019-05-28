#pragma once
#include <math.h>

class Vec3f
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};
	Vec3f();
	Vec3f(const Vec3f& other);
	Vec3f(float x, float y, float z);
	float& operator [](int);

	Vec3f operator - (const Vec3f& other);
	Vec3f& operator+=(const Vec3f& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3f operator*(float f) const
	{
		return Vec3f(x * f, y * f, z * f);
	}

	Vec3f normalized() const;
	float length() const;
};

class Vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};
	Vec2f();
	Vec2f(float x, float y);
	Vec2f(Vec2f& other);
	float& operator [](int);
};
