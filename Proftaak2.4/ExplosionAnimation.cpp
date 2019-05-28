#include "ExplosionAnimation.hpp"
#include "GameObject.h"
#include <GL\freeglut.h>

#define PARTICLE_SIZE 0.5f
ExplosionAnimation::ExplosionAnimation()
{
	drawAllowed = false;

}

void ExplosionAnimation::update(float elapsedTime)
{
	for (auto& p : particles)
	{
		const float speed = p.speed * elapsedTime;
		p.pos += p.dir * speed;
	}
}
void ExplosionAnimation::draw()
{
	// Wait untill instructed to display explosion animation
	if (!drawAllowed) return;


	for (const auto& p : particles)
	{
		//float angle = (rand() % 360) + 1;
		//glRotatef(angle, 0, 0, 1);
		glTranslatef(p.pos.x, p.pos.y, p.pos.z); // 1 van de z van position
		glRotatef(p.rot.x, 1, 0, 0);
		glRotatef(p.rot.y, 0, 1, 0);
		glRotatef(p.rot.z, 0, 0, 1);
		glBegin(GL_TRIANGLES);
		glColor3f(229.0f/255.0f, 229.0f/255.0f, 229.0f/255.0f);
		//glColor4f(COLOR_R / 255.0f, COLOR_G / 255.0f, COLOR_B / 255.0f, 0);
		//glRotatef(i * 20, 1, 0, 0);
		//glRotatef(i* 20, 0, 1, 0);
		//glRotatef(i * 20, 0, 0, 1);

		glVertex3f(-PARTICLE_SIZE, -PARTICLE_SIZE, 0.0);
		glVertex3f(PARTICLE_SIZE, -PARTICLE_SIZE, 0.0);
		glVertex3f(0.0, PARTICLE_SIZE, 0.0);

		glEnd();
	}
}

float getRandomDirection()
{
	return float(rand()) / RAND_MAX * 2 - 1;
	// Random nr in range [-1, 1] with uniform distribution
}

float getRandomSpeed()
{
	return ((rand() % 50) + 1);
}
void ExplosionAnimation::explode()
{
	static bool exploded = false;
	if (exploded) return;
	for (int i = 0; i < 1; i++)
	{
		Vec3f dir = Vec3f(getRandomDirection(), getRandomDirection(), getRandomDirection());
		
		ExplosionParticle particle = ExplosionParticle(Vec3f(gameObject->position), dir.normalized(), Vec3f(0, 0, 0), 0.02f);
		particles.push_back(particle);
	}
	drawAllowed = true;
	exploded = true;
}