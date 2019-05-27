#pragma once

#include "Component.h"
#include "DrawComponent.h"
#include "Tracker.hpp"

class PlayerComponent : public DrawComponent
{

private:
	void drawCircle(float cx, float cy, float r, int num_segments);

public:
	PlayerComponent();
	~PlayerComponent();

	virtual void draw() override;

};

