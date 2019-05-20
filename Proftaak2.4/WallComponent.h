#pragma once

#include "DrawComponent.h"

class WallComponent : public DrawComponent
{
public:
	WallComponent();
	~WallComponent();

	virtual void draw() override;
};