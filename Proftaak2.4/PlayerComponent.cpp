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

HandTracker* tracker;
GLuint textureID;
std::atomic<std::array<hand, HANDS_AMOUNT>> atomic_hands;

PlayerComponent::PlayerComponent(std::list<GameObject*>* objects, GLuint textureID)
{
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
		float radius = 1.0f;
		float radian, x, y, tx, ty;
		
		glColor3f(1, 0, 0);
		//glPushMatrix();
		glTranslatef(hand.x, hand.y, 0);

		glBindTexture(GL_TEXTURE_2D, textureID);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		//draw circles with textures here!
		glBegin(GL_POLYGON);

		for (double angle = 0.0; angle < 360.0; angle += 2.0)
		{
			radian = angle * (M_PI / 180.0f);

			float xcos = (float)cos(radian);
			float ysin = (float)sin(radian);
			x = xcos * radius + hand.x;
			y = ysin * radius + hand.y;
			tx = xcos * 0.5 + 0.5;
			ty = ysin * 0.5 + 0.5;

			glTexCoord2f(tx, ty);
			glVertex2f(x, y);
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);

		//glPopMatrix();

		////=================
		//glColor3f(1, 0, 0);
		//glPushMatrix();
		//glTranslatef(hand.x, hand.y, 0);
		//glutSolidSphere(0.25, 30, 20);
		//glPopMatrix();
		////drawCircle(hand.x, hand.y, 0.25, 50);
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
