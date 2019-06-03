#include "TrailAnimation.hpp"
#include <GL/freeglut.h>
#include "GameObject.h"

#define PARTICLES 50
#define PARTICLE_SIZE 0.1f
#define COLOR_R 229.0f
#define COLOR_G 229.0f
#define COLOR_B 229.0f

TrailAnimation::TrailAnimation()
{

}

void TrailAnimation::draw()
{
	if (!drawAllowed) return;

	Vec3f pos = gameObject->position;

	for (int i = 1; i <= PARTICLES; i++)
	{

		float angle = (rand() % 360) + 1;
		glRotatef(angle, 0, 0, 1);
		glTranslatef(0, 0, i * 0.002f); // 1 van de z van position
		float alpha = ((rand() % 100) + 0) / 100.0f;
		glBegin(GL_TRIANGLES);
		//glEnableClientState(GL_VERTEX_ARRAY);
		//glColor3f(229.0f/255.0f, 229.0f/255.0f, 229.0f/255.0f);
		glColor4f(COLOR_R / 255.0f, COLOR_G / 255.0f, COLOR_B / 255.0f, 0);
		//glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glRotatef(i * 20, 1, 0, 0);
		//glRotatef(i* 20, 0, 1, 0);
		//glRotatef(i * 20, 0, 0, 1);
		glVertex3f(-PARTICLE_SIZE, -PARTICLE_SIZE, 0.0);
		glVertex3f(PARTICLE_SIZE, -PARTICLE_SIZE, 0.0);
		glVertex3f(0.0, PARTICLE_SIZE, 0.0);

		glEnd();
	}

}

//for (int i = 1; i <= PARTICLES; i++)
//{
//
//	float angle = (rand() % 360) + 1;
//	glRotatef(angle, 0, 0, 1);
//	glTranslatef(0, 0, i * 0.002f); // 1 van de z van position
//	float alpha = ((rand() % 100) + 0) / 100.0f;
//	glBegin(GL_TRIANGLES);
//	//glEnableClientState(GL_VERTEX_ARRAY);
//	//glColor3f(229.0f/255.0f, 229.0f/255.0f, 229.0f/255.0f);
//	glColor4f(COLOR_R / 255.0f, COLOR_G / 255.0f, COLOR_B / 255.0f, 0);
//	//glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
//	//glDrawArrays(GL_TRIANGLES, 0, 3);
//	//glRotatef(i * 20, 1, 0, 0);
//	//glRotatef(i* 20, 0, 1, 0);
//	//glRotatef(i * 20, 0, 0, 1);
//	glVertex3f(-PARTICLE_SIZE, -PARTICLE_SIZE, 0.0);
//	glVertex3f(PARTICLE_SIZE, -PARTICLE_SIZE, 0.0);
//	glVertex3f(0.0, PARTICLE_SIZE, 0.0);
//
//	glEnd();
//}