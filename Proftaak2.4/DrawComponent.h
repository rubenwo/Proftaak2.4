#pragma once

#include "Component.h"

class DrawComponent : public Component
{
public:
	DrawComponent();
	virtual ~DrawComponent();
	virtual void draw() = 0;
};

