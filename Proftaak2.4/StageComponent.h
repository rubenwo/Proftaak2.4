#pragma once

#include "DrawComponent.h"

class StageComponent : public DrawComponent
{
public:
	GLuint leftWallTex;
	GLuint rightWallTex;
	GLuint leftPanelTex;
	GLuint rightPanelTex;
	GLuint basePlatformTex;

	StageComponent();
		// GLuint leftWallTex, GLuint rightWallTex, GLuint leftPanelTex, GLuint rightPanelTex, GLuint basePlatformTex);
	~StageComponent();

	virtual void draw() override;
};