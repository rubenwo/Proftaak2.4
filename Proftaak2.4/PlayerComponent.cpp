#include "PlayerComponent.h"
#include "GameObject.h"
#include "Tracker.hpp"
#include "Component.h"

#include <array>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <atomic>
#include <GL/freeglut.h>
void drawCube();
std::atomic<std::array<hand, HANDS_AMOUNT>> atomic_hands;

PlayerComponent::PlayerComponent(HandTracker& tracker)
{
	tracker.startTracking([](std::array<hand, HANDS_AMOUNT> hands)
	{
		atomic_hands.store(hands);
	});
}

PlayerComponent::~PlayerComponent()
{
}


void PlayerComponent::draw()
{
	for (auto hand : atomic_hands.load())
	{
		//drawCircle(hand.x / 1240.0f * 4, -hand.y / 720.0f, 0.25, 100);
		glPushMatrix();
		glTranslatef(hand.x, hand.y, 0);
		glColor3ub(0, 255, 255);
		drawCube();
		glPopMatrix();
	}
}

void drawCube()
{
	const float size = 0.25;
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-size, -size, 0);
	glVertex3f(-size, -size, 0);
	glVertex3f(-size, size, 0);
	glVertex3f(-size, size, 0);

	glVertex3f(size, -size, 0);
	glVertex3f(size, -size, 0);
	glVertex3f(size, size, 0);
	glVertex3f(size, size, 0);

	glColor3f(0, 1, 0);
	glVertex3f(-size, -size, 0);
	glVertex3f(-size, -size, 0);
	glVertex3f(size, -size, 0);
	glVertex3f(size, -size, 0);

	glVertex3f(-size, size, 0);
	glVertex3f(-size, size, 0);
	glVertex3f(size, size, 0);
	glVertex3f(size, size, 0);

	glColor3f(0, 0, 1);
	glVertex3f(-size, -size, 0);
	glVertex3f(-size, size, 0);
	glVertex3f(size, size, 0);
	glVertex3f(size, -size, 0);

	glVertex3f(-size, -size, 0);
	glVertex3f(-size, size, 0);
	glVertex3f(size, size, 0);
	glVertex3f(size, -size, 0);

	glEnd();
}

void PlayerComponent::drawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle 
		float x = r * cosf(theta); //calculate the x component 
		float y = r * sinf(theta); //calculate the y component 
		glColor3f(0, 0, 0);
		glVertex2f(x + cx, y + cy); //output vertex 
	}
	glEnd();
}
