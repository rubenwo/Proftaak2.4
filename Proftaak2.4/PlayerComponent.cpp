#include "PlayerComponent.h"
#include "GameObject.h"
#include "Tracker.hpp"
#include "Component.h"

#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include <math.h>
#include <array>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <atomic>
#include <GL/freeglut.h>
#include <iostream>

HandTracker* tracker;
GLuint textureID;
float size;
std::atomic<std::array<hand, HANDS_AMOUNT>> atomic_hands;

PlayerComponent::PlayerComponent(float size, GLuint textureID)
{
	this->size = size;
	this->textureID = textureID;
	tracker = new HandTracker();
	tracker->startTracking([](std::array<hand, HANDS_AMOUNT> hands)
	{
		atomic_hands.store(hands);
	});
}

PlayerComponent::~PlayerComponent()
{
	free(tracker);
}

void PlayerComponent::draw()
{
	for (auto hand : atomic_hands.load())
	{
		std::cout << "\r\nHandX: " << hand.x;
		if (hand.x > 0) {
			std::cout << "\r\nRIGHT";
		}
		else {
			std::cout << "Scale (-1, 1, 1); Left";
			glScalef(-1, 1, 1);
		}

		std::cout << "\r\nsize";
		glBindTexture(GL_TEXTURE_2D, textureID);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		glPushMatrix();
		glRotatef(-90, 0, 0, 1);
		glTranslatef(hand.x, hand.y, 0);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);	
		glBegin(GL_QUADS);
		glColor4f(1, 1, 1, 1);
		glTexCoord2f(0, 0);
		glVertex3f(-size, -size, -size);
		glTexCoord2f(0, 1);
		glVertex3f(size, -size, -size);
		glTexCoord2f(1, 1);
		glVertex3f(size, size, -size);
		glTexCoord2f(1, 0);
		glVertex3f(-size, size, -size);
		glDisable(GL_BLEND);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}
