#pragma once

#include "Component.h"
#include "DrawComponent.h"
#include "Tracker.hpp"
#include "Vec.h"
#include <list>

class PlayerComponent : public DrawComponent
{
private:
	void drawCircle(float cx, float cy, float r, int num_segments);
	std::function<void(int, Vec3f)> onCollision;
	std::list<GameObject*> *objects;
public:
	PlayerComponent() = default;
	PlayerComponent(std::list<GameObject*>* objects);
	~PlayerComponent();

	void setCollisionCallback(const std::function<void(int, Vec3f)> onCollision);

	void update(float elapsedTime) override;
	virtual void draw() override;
};
