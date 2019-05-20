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

PlayerComponent::PlayerComponent(int width, int height)
{
	HandTracker tracker(width, height);

	tracker.startTracking([](std::array<hand, HANDS_AMOUNT> hands) {
		atomic_hands._My_val = hands;
	});
}

PlayerComponent::~PlayerComponent()
{

}

void PlayerComponent::update(float elapsedTime)
{
	for (int i = 0; i < atomic_hands._My_val.size(); i++)
	{
		std::cout << "ID: " << atomic_hands._My_val[i].id << " X: " << atomic_hands._My_val[i].x << " Y: " <<
			atomic_hands._My_val[i].y << std::endl;
	}
}

void PlayerComponent::draw()
{
	for (auto hand : atomic_hands._My_val) {
		drawCircle(hand.x, hand.y, 5, 10);
	}
}

void PlayerComponent::drawCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}