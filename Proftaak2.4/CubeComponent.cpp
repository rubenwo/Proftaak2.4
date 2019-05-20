#include "CubeComponent.h"
#include <GL/freeglut.h>
#include <iostream>

int textureID;
int startPos;
int endPos;
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

double CubeComponent::getStartPos() {
	return startPos;
}

double CubeComponent::getEndPos() {
	return endPos;
}

void CubeComponent::setStartPos(double sP) {
	startPos = sP;
}

void CubeComponent::setEndPos(double eP) {
	endPos = eP;
}

void CubeComponent::getTexture(HAND handSide) {
	std::cout << "\r\nGettexture: " << handSide;
	if (handSide == 0) {
		//cout << "\r\nLEFT";
		startPos = 0;
		endPos = 0.5;
	}
	else {
		std::cout << "\r\nRIGHT";
		startPos = 0.5;
		endPos = 1;
	}
}

void CubeComponent::draw()
{
	glBegin(GL_QUADS);

	//glRotatef(180, 0, 0, 1);

	//Red
	if (handSide == HAND::leftHand) {
		//red
		glColor3f(0.2274f, 0.0156f, 0.0392f);
	}
	else {
		//blue
		glColor3f(0.0392f, 0.0235f, 0.2627f);
	}
	glVertex3f(-size, -size, -size);
	glVertex3f(size, -size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(-size, size, -size);
	glEnd();

	//FRONT
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDisable(GL_BLEND);
	if (arrowDirection == ARROWDIRECTION::left) {
		//printf("\r\nLEFT");
		glRotatef(180, 0, 0, 1.0f);
	}
	else if (arrowDirection == ARROWDIRECTION::right) {
		//printf("\r\nRIGHT");
		glRotatef(0, 0, 0, 1.0f);
	}
	else if (arrowDirection == ARROWDIRECTION::up) {
		//printf("\r\nUP");
		glRotatef(90, 0, 0, 1.0f);
	}
	else if (arrowDirection == ARROWDIRECTION::down) {
		//printf("\r\nDOWN");
		glRotatef(270, 0, 0, 1.0f);
	}

	getTexture(handSide);
	//printf("\r\nTexture ID: " + textureID);

	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glTexCoord2f(startPos, startPos);
	glVertex3f(-size, -size, size);
	glTexCoord2f(startPos, endPos);
	glVertex3f(size, -size, size); 
	glTexCoord2f(endPos, endPos);
	glVertex3f(size, size, size); 
	glTexCoord2f(endPos, startPos);
	glVertex3f(-size, size, size);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glRotatef(180, 1.0f, 0, 0);

	glBegin(GL_QUADS);
	if (handSide == HAND::leftHand) {
		//red
		glColor3f(0.2274f, 0.0156f, 0.0392f);
	}
	else {
		//blue
		glColor3f(0.0392f, 0.0235f, 0.2627f);
	}
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

	//glRotatef(9, 0, 0, 1);

	//========================

	//glColor3f(1, 0, 0);
	//glVertex3f(-size, -size, -size);
	//glVertex3f(-size, -size, size);
	//glVertex3f(-size, size, size);
	//glVertex3f(-size, size, -size);

	//glVertex3f(size, -size, -size);
	//glVertex3f(size, -size, size);
	//glVertex3f(size, size, size);
	//glVertex3f(size, size, -size);

	//glColor3f(0, 1, 0);
	//glVertex3f(-size, -size, -size);
	//glVertex3f(-size, -size, size);
	//glVertex3f(size, -size, size);
	//glVertex3f(size, -size, -size);

	//glVertex3f(-size, size, -size);
	//glVertex3f(-size, size, size);
	//glVertex3f(size, size, size);
	//glVertex3f(size, size, -size);

	//glColor3f(0, 0, 1);
	//glVertex3f(-size, -size, -size);
	//glVertex3f(-size, size, -size);
	//glVertex3f(size, size, -size);
	//glVertex3f(size, -size, -size);

	//glVertex3f(-size, -size, size);
	//glVertex3f(-size, size, size);
	//glVertex3f(size, size, size);
	//glVertex3f(size, -size, size);

	//glDisable(GL_TEXTURE_2D);
	//glEnd();
}

