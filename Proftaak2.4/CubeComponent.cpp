#include "CubeComponent.h"
#include <GL/freeglut.h>
#include <iostream>
#include "ObjectModel.h"

int textureID[];
float startPos;
float endPos;
HAND handSide;

CubeComponent::CubeComponent(float size, GLuint textureID, HAND handSide, ARROWDIRECTION arrowDirection)
{
	this->size = size;
	this->textureID = textureID;
	this->arrowDirection = arrowDirection;
	this->handSide = handSide;
}

CubeComponent::~CubeComponent()
{
}

HAND CubeComponent::getHandSide() {
	return handSide;
}

void CubeComponent::getTexture(HAND handSide) {
	if (handSide == HAND::leftHand) {
		//cout << "\r\nLEFT";
		startPos = 0.0f;
		endPos = 0.5f;
	}
	else {
		//std::cout << "\r\nRIGHT";
		startPos = 0.5f;
		endPos = 1.0f;
	}
}

void CubeComponent::draw()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	//FRONT
	if (arrowDirection == ARROWDIRECTION::left) {
	}
	else if (arrowDirection == ARROWDIRECTION::right) {
		glRotatef(180, 0, 0, 1.0f);
	}
	else if (arrowDirection == ARROWDIRECTION::up)
		glRotatef(90, 0, 0, 1.0f);
	else if (arrowDirection == ARROWDIRECTION::down)
		glRotatef(270, 0, 0, 1.0f);

	getTexture(handSide);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glTexCoord2f((float)startPos, (float)startPos);
	glVertex3f(-size, -size, -size);
	glTexCoord2f((float)startPos, (float)endPos);
	glVertex3f(size, -size, -size);
	glTexCoord2f((float)endPos, (float)endPos);
	glVertex3f(size, size, -size);
	glTexCoord2f((float)endPos, (float)startPos);
	glVertex3f(-size, size, -size);
	glDisable(GL_TEXTURE_2D);

	if (handSide == HAND::leftHand)
		glColor3f(0.2274f, 0.0156f, 0.0392f);	//red
	else
		glColor3f(0.0392f, 0.0235f, 0.2627f);	//blue

	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size); 
	glVertex3f(size, size, size); 
	glVertex3f(-size, size, size);

	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, -size, size);

	glVertex3f(size, -size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, size, size);
	glVertex3f(size, -size, size);

	glVertex3f(-size, -size, -size);
	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(-size, -size, size);

	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, size, size);
	glVertex3f(-size, size, size);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

