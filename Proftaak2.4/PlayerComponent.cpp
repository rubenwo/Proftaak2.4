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
#include "StageComponent.h"
#include "CubeComponent.h"
#include <iostream>

HandTracker* tracker;
GLuint textureID;
float size;
std::atomic<std::array<hand, HANDS_AMOUNT>> atomic_hands;

PlayerComponent::PlayerComponent(std::list<GameObject*>* objects, GLuint textureID, float size)
{
	this->size = size;
	this->textureID = textureID;
	tracker = new HandTracker();
	tracker->startTracking([](std::array<hand, HANDS_AMOUNT> hands)
	{
		atomic_hands.store(hands);
	});
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
			if (obj->position.z < 0 && obj->position.z > -1.0f)
			{
				for (auto hand : atomic_hands.load())
				{
					hand.x = 0;
					hand.y = 0;

					Vec2f pos(hand.x, hand.y);
					if (obj->sphere.collides(pos, 0.25))
					{
						if (this->onCollision != nullptr)
							this->onCollision(obj, pos);
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


void PlayerComponent::setCollisionCallback(const std::function<void(GameObject*, Vec2f)> onCollision)
{
	this->onCollision = onCollision;
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
