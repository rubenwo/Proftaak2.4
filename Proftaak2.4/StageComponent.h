#pragma once

#include "DrawComponent.h"

class StageComponent : public DrawComponent
{
public:
	GLuint sideWallTextureId;
	GLuint rightWallTex;
	GLuint leftPanelTex;
	GLuint rightPanelTex;
	GLuint basePlatformTex;

	StageComponent(GLuint sideWallTexture);
	~StageComponent();

	virtual void draw() override;
};