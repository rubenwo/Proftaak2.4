#include "PlayerComponent.h"
#include "GameObject.h"
#include "Tracker.hpp"
#include "Component.h"

#include <array>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <atomic>
#include <GL/freeglut.h>

std::atomic<std::array<hand, HANDS_AMOUNT>> atomic_hands;

PlayerComponent::PlayerComponent(HandTracker& tracker)
{
	tracker.startTracking([](std::array<hand, HANDS_AMOUNT> hands)
	{
		for (auto hand : hands)
		{
			//std::cout << "ID: " << hand.id << " X: " << hand.x << " Y: " << hand.y << std::endl;
		}
		atomic_hands._My_val = hands;
	});
}

PlayerComponent::~PlayerComponent()
{
}


void PlayerComponent::draw()
{
	for (auto hand : atomic_hands._My_val)
	{
		std::cout << "ID: " << hand.id << " X: " << hand.x << " Y: " << hand.y << std::endl;
		drawCircle(hand.x, hand.y, 100, 10);
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
		glVertex2f(x + cx, y + cy); //output vertex 
	}
	glEnd();
}
