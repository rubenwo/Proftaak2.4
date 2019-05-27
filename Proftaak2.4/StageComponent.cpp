#include <GL/freeglut.h>
#include "StageComponent.h"
#include "ObjectModel.h"
#include <iostream>

GLuint wallTex;

StageComponent::StageComponent()
	// GLuint leftWallTex, GLuint rightWallTex, GLuint leftPanelTex, GLuint rightPanelTex, GLuint basePlatformTex)
	// : leftWallTex(leftWallTex), rightWallTex(rightWallTex), leftPanelTex(leftPanelTex), rightPanelTex(rightPanelTex), basePlatformTex(basePlatformTex)
{
}

StageComponent::~StageComponent()
{
}

void StageComponent::draw()
{
	glEnable(GL_TEXTURE_BINDING_2D);
	glDisable(GL_BLEND);

	//RIGHT WALL
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-3, -2, 2.5);
	glTexCoord2f(0, 1);
	glVertex3f(-3, -2, 100);
	glTexCoord2f(1, 1);
	glVertex3f(-3, 4, 100);
	glTexCoord2f(1, 0);
	glVertex3f(-3, 4, 2.5);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();


	//START WALL RIGHT
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(-2.5, -2, 2.49);
	glVertex3f(-3.5, -2, 2.49);
	glVertex3f(-3.5, 4, 2.49);
	glVertex3f(-2.5, 4, 2.49);
	glEnd();

	//LEFT WALL
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glEnable(GL_TEXTURE_BINDING_2D);
	glVertex3f(3, -2, 2.5);
	glVertex3f(3, -2, 100);
	glVertex3f(3, 4, 100);
	glVertex3f(3, 4, 2.5);
	glEnd();
	glDisable(GL_TEXTURE_BINDING_2D);

	//START WALL LEFT
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(2.5, -2, 2.49);
	glVertex3f(3.5, -2, 2.49);
	glVertex3f(3.5, 4, 2.49);
	glVertex3f(2.5, 4, 2.49);
	glEnd();

	//BASE PLATFORM
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(-2, 0.7, 1);
	glVertex3f(-2, 0.7, 100);
	glVertex3f(2, 0.7, 100);
	glVertex3f(2, 0.7, 1);
	glEnd();
}

void loadWallTexture()
{

}
