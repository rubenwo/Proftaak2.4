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
	std::function<void(GameObject*)> onCollision;
	std::list<GameObject*>* objects;
	float size;
	GLuint textureID;

public:
	PlayerComponent() = default;
	PlayerComponent(std::list<GameObject*>* objects, GLuint textureID, float size);
	~PlayerComponent();

	void setCollisionCallback(const std::function<void(GameObject*)>& onCollision);


	void update(float elapsedTime) override;
	virtual void draw() override;
};
