#pragma once

#include <GL/freeglut.h>
#include "Component.h"
#include "DrawComponent.h"
#include "Tracker.hpp"
#include "Vec.h"
#include <list>

class PlayerComponent : public DrawComponent
{
private:
	void drawCircle(float cx, float cy, float r, int num_segments);
	std::function<void(GameObject*, Vec2f)> onCollision;
	std::list<GameObject*>* objects;
	GLuint textureID;

public:
	PlayerComponent() = default;
	PlayerComponent(std::list<GameObject*>* objects, GLuint textureID);
	~PlayerComponent();

	void setCollisionCallback(const std::function<void(GameObject*, Vec2f)> onCollision);

	void update(float elapsedTime) override;
	virtual void draw() override;
};
