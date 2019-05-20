#pragma once

#include <GL\freeglut.h>
#include "DrawComponent.h"
#include "Enums.h"


class CubeComponent : public DrawComponent
{
	float size;
	GLuint textureID;
	HAND handSide;
	ARROWDIRECTION arrowDirection;
	double startPos;
	double endPos;

public:
	CubeComponent(float size, GLuint textureID, HAND handSide, ARROWDIRECTION arrowDirection);// , double startPos, double endPos); //, int startPos, int endPos);// , GLuint textureID, int startPos, int endPos);
	~CubeComponent();
	HAND getHandSide();
	void getTexture(HAND handSide);
	double getStartPos();
	double getEndPos();
	void setStartPos(double startPos);
	void setEndPos(double endPos);
	virtual void draw() override;
	//void drawWithTexture(GLuint textureID, int size, int startPos, int endPos);
};

