#include <GL/freeglut.h>
#include "StageComponent.h"
#include "ObjectModel.h"
#include <iostream>

StageComponent::StageComponent(GLuint sideWallTexture)
{
	this->sideWallTextureId = sideWallTexture;
}

StageComponent::~StageComponent()
{
}

void StageComponent::draw()
{
	glBindTexture(GL_TEXTURE_2D, sideWallTextureId);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	//RIGHT WALL
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-3, -2, 2.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-3, -2, 100);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 4, 100);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 4, 2.5f);
	glEnd();

	//LEFT WALL
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(3, -2, 2.5f);
	glTexCoord2f(0, 1);
	glVertex3f(3, -2, 100);
	glTexCoord2f(1, 1);
	glVertex3f(3, 4, 100);
	glTexCoord2f(1, 0);
	glVertex3f(3, 4, 2.5f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//BASE PLATFORM
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(-2, 0.7f, 1);
	glVertex3f(-2, 0.7f, 100);
	glVertex3f(2, 0.7f, 100);
	glVertex3f(2, 0.7f, 1);
	glEnd();
}
