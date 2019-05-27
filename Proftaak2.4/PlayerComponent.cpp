#include "PlayerComponent.h"
#include "GameObject.h"
#include "Tracker.hpp"
#include "Component.h"

#include <array>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <atomic>
#include <GL/freeglut.h>

HandTracker* tracker;
std::atomic<std::array<hand, HANDS_AMOUNT>> atomic_hands;

PlayerComponent::PlayerComponent()
{
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
		drawCircle(hand.x, hand.y, 0.25, 50);
	}
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
