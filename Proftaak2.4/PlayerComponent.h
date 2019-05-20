#pragma once

#include "Component.h"
#include "DrawComponent.h"
#include "Tracker.hpp"

class PlayerComponent : public DrawComponent
{

private:
	void drawCircle(float cx, float cy, float r, int num_segments);

public:
	PlayerComponent(int width, int height);
	~PlayerComponent();

	void update(float elapsedTime) override;
	virtual void draw() override;

};

