#pragma once

#include <GL/freeglut.h>
#include "Component.h"
#include "DrawComponent.h"
#include "Tracker.hpp"

class PlayerComponent : public DrawComponent
{

private:
	void drawCircle(float cx, float cy, float r, int num_segments);
	float size;
	GLuint textureID;

public:
	PlayerComponent(float size, GLuint textureID);
	~PlayerComponent();

	virtual void draw() override;

};

