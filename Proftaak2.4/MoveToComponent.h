#pragma once

#include "Component.h"
#include "Vec.h"

class MoveToComponent : public Component
{
public:
	float speed = 2.5f;
	Vec3f target;

	MoveToComponent();
	~MoveToComponent();

	virtual void update(float elapsedTime) override;
};

