#include <GL/freeglut.h>
#include <iostream>	
#include "Menu.h"


Menu::Menu(GLuint logoTextureId, 
	GLuint creditTextureId, GLuint creditSelectedTextureId,
	GLuint optionsTextureId, GLuint opetionsSelectedTextureId,
	GLuint quitTextureId, GLuint quitSelectedTextureId,
	GLuint startTextureId, GLuint startSelectedTextureId)
	: mLogoTextureId(logoTextureId), mCreditTextureId(creditTextureId), mCreditSelectedTextureId(creditSelectedTextureId),
	mOptionsTextureId(optionsTextureId), mOptionsSelectedTextureId(opetionsSelectedTextureId), 
	mQuitTextureId(quitTextureId), mQuitSelectedTextureId(quitSelectedTextureId),
	mStartTextureIdl(startTextureId), mStartSelectedTextureIdl(startSelectedTextureId)
{
	this->mIndex = 0;
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

	if (this->mIndex == 1) {
		drawStart(mStartSelectedTextureIdl);
	}
	else {
		drawStart(mStartTextureIdl);
	}

	if (this->mIndex == 2) {
		drawOptions(mOptionsSelectedTextureId);
	}
	else {
		drawOptions(mOptionsTextureId);
	}

	if (this->mIndex == 4) {
		drawCredits(mQuitSelectedTextureId);
	}
	else {
		drawCredits(mQuitTextureId);
	}

	if (this->mIndex == 3) {
		drawQuit(mCreditSelectedTextureId);
	}
	else {
		drawQuit(mCreditTextureId);
	}

	//drawCredits(mCreditTextureId);
}

void Menu::update(float deltaTime, int index) 
{
	this->mIndex = index;
}

void Menu::drawQuit(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	//glTranslatef(2.0f, -2.0f, 2.0f);

	glDisable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);

	glScalef(1.0f, -1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, 0.30f, -1.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, 0.50f, -1.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, 0.50f, -1.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, 0.30f, -1.5f);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Menu::drawCredits(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.55f, -1.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, -0.75f, -1.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, -0.75f, -1.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.55f, -1.5f);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Menu::drawOptions(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.05f, -1.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, -0.25f, -1.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, -0.25f, -1.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.05f, -1.5f);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Menu::drawStart(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);

	glVertex3f(-0.5f, 0.20f, -1.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, 0, -1.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, 0, -1.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, 0.20f, -1.5f);
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
	glVertex3f(-1.0f, 0.5f, -1.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-1.0f, 0.25f, -1.0f);
	glTexCoord2f(1, 1);
	glVertex3f(1.0f, 0.25f, -1.0f);
	glTexCoord2f(1, 0);
	glVertex3f(1.0f, 0.5f, -1.0f);
	glDisable(GL_TEXTURE_BINDING_2D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}