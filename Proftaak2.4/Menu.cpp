#include <GL/freeglut.h>
#include <iostream>	
#include "Menu.h"

Menu::Menu(GLuint textureID) : mtextureID(textureID)
{

}

Menu::~Menu()
{

}

void Menu::draw() 
{
	//glRotatef(90, 1, 0, 0);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glVertex3f(-1.0f, 0.25f,-1.0f);
	glVertex3f(-1.0f, 0.5f, -1.0f);
	glVertex3f(1.0f, 0.5f, -1.0f);
	glVertex3f(1.0f, 0.25f, -1.0f);
	glEnd();
}

void Menu::update(float deltaTime) 
{

}