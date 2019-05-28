#include <GL/freeglut.h>
#include <iostream>	
#include "Menu.h"


Menu::Menu(GLuint logoTextureID, GLuint creditTextureId, 
	GLuint optionsTextureId,
	GLuint quitTextureId, GLuint startTextureId) 
	:	mLogoTextureId(logoTextureID), mCreditTextureId(creditTextureId), 
		mOptionsTextureId(optionsTextureId),
		mQuitTextureId(quitTextureId), mStartTextureIdl(startTextureId)
{

}

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::draw() 
{
	drawLogo();
	drawStart();
	drawOptions();
	drawCredits();
	drawQuit();
}

void Menu::update(float deltaTime) 
{

}

void Menu::drawQuit()
{
	glBindTexture(GL_TEXTURE_2D, mQuitTextureId);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.5f, -1.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, -0.30f, -1.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, -0.30f, -1.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.5f, -1.5f);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Menu::drawCredits()
{
	glBindTexture(GL_TEXTURE_2D, mCreditTextureId);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.75f, -1.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, -0.55f, -1.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, -0.55f, -1.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.75f, -1.5f);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Menu::drawOptions()
{
	glBindTexture(GL_TEXTURE_2D, mOptionsTextureId);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.25f, -1.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, -0.05f, -1.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, -0.05f, -1.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.25f, -1.5f);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Menu::drawStart()
{
	glBindTexture(GL_TEXTURE_2D, mStartTextureIdl);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);

	glVertex3f(-0.5f, 0, -1.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, 0.20f, -1.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, 0.20f, -1.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, 0, -1.5f);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Menu::drawLogo()
{
	glBindTexture(GL_TEXTURE_2D, mLogoTextureId);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1.0f, 0.25f, -1.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-1.0f, 0.5f, -1.0f);
	glTexCoord2f(1, 1);
	glVertex3f(1.0f, 0.5f, -1.0f);
	glTexCoord2f(1, 0);
	glVertex3f(1.0f, 0.25f, -1.0f);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}