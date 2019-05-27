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
	glVertex3f(-3, -2, -2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-3, -2, 50);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 4, 50);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 4, -2.5);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();

	//LEFT WALL
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glEnable(GL_TEXTURE_BINDING_2D);
	glTexCoord2f(0, 0);
	glVertex3f(3, -2, -2.5);
	glTexCoord2f(0, 1);
	glVertex3f(3, -2, 50);
	glTexCoord2f(1, 1);
	glVertex3f(3, 4, 50);
	glTexCoord2f(1, 0);
	glVertex3f(3, 4, -2.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
