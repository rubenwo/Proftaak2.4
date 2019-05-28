#pragma once


#include <GL\freeglut.h>
#include "DrawComponent.h"
#include "Enums.h"


class CubeComponent : public DrawComponent
{
private:
	float size;
	GLuint textureID;
	HAND handSide;
	ARROWDIRECTION arrowDirection;
	double startPos;
	double endPos;
	void drawTrail();

public:
	CubeComponent(float size, GLuint textureID, HAND handSide, ARROWDIRECTION arrowDirection);// , double startPos, double endPos); //, int startPos, int endPos);// , GLuint textureID, int startPos, int endPos);
	~CubeComponent();
	HAND getHandSide();
	void getTexture(HAND handSide);
	virtual void draw() override;
	//void drawWithTexture(GLuint textureID, int size, int startPos, int endPos);
};