#include "PlayerComponent.h"
#include "GameObject.h"
#include "Tracker.hpp"
#include "Component.h"

#include <array>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <atomic>
#include <GL/freeglut.h>
#include "StageComponent.h"
#include "CubeComponent.h"

HandTracker* tracker;
std::atomic<std::array<hand, HANDS_AMOUNT>> atomic_hands;

PlayerComponent::PlayerComponent(std::list<GameObject*>* objects)
{
	/*tracker = new HandTracker();
	tracker->startTracking([](std::array<hand, HANDS_AMOUNT> hands)
	{
		atomic_hands.store(hands);
	});*/
	this->onCollision = nullptr;
	this->objects = objects;
}

PlayerComponent::~PlayerComponent()
{
	delete tracker;
}


void PlayerComponent::update(float elapsedTime)
{
	for (auto obj : *objects)
	{
		if (!obj->getComponent<StageComponent>())
		{
			if (obj->position.z < 0.01 && obj->position.z > -0.01f)
			{
				for (auto hand : atomic_hands.load())
				{
					hand.x = 0;
					hand.y = 0;

					Vec2f pos(hand.x, hand.y);
					if (obj->sphere.collides(pos, 0.25))
					{
						if (this->onCollision != nullptr)
							this->onCollision(hand.id, pos);
						else
						{
							std::cout << "Collision detected with: " << obj
							                                            ->getComponent<CubeComponent>()->getHandSide()
								<< "\n";
						}
					}
				}
			}
		}
	}
}


void PlayerComponent::setCollisionCallback(const std::function<void(int, Vec2f)> onCollision)
{
	this->onCollision = onCollision;
}


void PlayerComponent::draw()
{
	for (auto hand : atomic_hands.load())
	{
		glColor3f(1, 0, 0);
		glPushMatrix();
		glTranslatef(hand.x, hand.y, 0);
		glutSolidSphere(0.25, 30, 20);
		glPopMatrix();
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
