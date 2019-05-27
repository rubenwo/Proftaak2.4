#pragma once
#include "Component.h"

class CollisionComponent : public Component
{
private:

public:
	CollisionComponent();
	~CollisionComponent();

	virtual void update(float elapsedTime) override;
};
