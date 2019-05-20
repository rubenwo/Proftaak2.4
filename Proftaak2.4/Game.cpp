#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>

#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include "MoveToComponent.h"
#include "Camera.hpp"

namespace Game
{
	int windowWidth, windowHeight;
	bool keys[256];

	Camera camera;
	std::list<GameObject*> objects;

	void drawRoom();
	void createMovingRubeRight();
	void createMovingRubeLeft();

	//GameObject* player;
	//CameraComponent* camComponent;	

	void loadContent()
	{
		ZeroMemory(keys, sizeof(keys));
		camera = Camera(0, -4, 0, 0);

		createMovingRubeRight();
		createMovingRubeLeft();
	}
	void update(float deltaTime)
	{
		for (const auto& o : objects)
			o->update(deltaTime);
	}
	void draw()
	{
		glRotatef(180, 1, 0, 0);

		drawRoom();

		for (const auto& o : objects)
			o->draw();
	}

	void onKey(Key key)
	{
		keys[key] = true;
	}

	void onKeyUp(Key key)
	{
		keys[key] = false;

		switch (key)
		{
		case VK_ESCAPE:
			glutLeaveMainLoop();
			break;
		default:
			break;
		}
	}

	void onMouseMove(int x, int y)
	{
		/*static bool justMoved = false;

		if (justMoved)
		{
			justMoved = false;
			return;
		}
		int dx = x - windowWidth / 2;
		int dy = y - windowHeight / 2;
		if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
		{
			camera.rotY += dx / 10.0f;
			camera.rotX += dy / 10.0f;
			glutWarpPointer(windowWidth / 2, windowHeight / 2);
			justMoved = true;
		}*/
	}

	void onResize(int w, int h)
	{
		windowWidth = w;
		windowHeight = h;
	}

	void onClose()
	{
		std::cout << "Cleaning up game\n";

		/*for (auto& o : objects)
			delete o;
		objects.clear();*/

		std::cout << "Closing game.\n";
	}

	void drawRoom()
	{
		//RIGHT WALL
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);

		glVertex3f(-3, -2, 2.5);
		glVertex3f(-3, -2, 100);
		glVertex3f(-3, 4, 100);
		glVertex3f(-3, 4, 2.5);
		glEnd();

		//START WALL RIGHT
		glBegin(GL_QUADS);
		glColor3f(1, 0, 1);
		glColor3f(0, 1, 0);
		glVertex3f(-2.5, -2, 2.49);
		glVertex3f(-3.5, -2, 2.49);
		glVertex3f(-3.5, 4, 2.49);
		glVertex3f(-2.5, 4, 2.49);
		glEnd();

		//LEFT WALL
		glBegin(GL_QUADS);
		glColor3f(0, 1, 0);
		glVertex3f(3, -2, 2.5);
		glVertex3f(3, -2, 100);
		glVertex3f(3, 4, 100);
		glVertex3f(3, 4, 2.5);
		glEnd();

		//START WALL LEFT
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex3f(2.5, -2, 2.49);
		glVertex3f(3.5, -2, 2.49);
		glVertex3f(3.5, 4, 2.49);
		glVertex3f(2.5, 4, 2.49);
		glEnd();

		//BASE PLATFORM
		glBegin(GL_QUADS);
		glColor3f(0, 0, 1);
		glVertex3f(-2, 0.7, 1);
		glVertex3f(-2, 0.7, 100);
		glVertex3f(2, 0.7, 100);
		glVertex3f(2, 0.7, 1);
		glEnd();
	}

	void createMovingRubeRight()
	{
		//Add moving cube right side of platform, TODO zorg ervoor dat dit gebaseerd op muziek gebeurt
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(0.1));
		o->addComponent(new MoveToComponent());

		o->position = Vec3f(0, 0, 30);
		o->getComponent<MoveToComponent>()->target = Vec3f(1.5, 0.6, -5);

		objects.push_back(o);
	}

	void createMovingRubeLeft()
	{
		//Add moving cube right side of platform, TODO zorg ervoor dat dit gebaseerd op muziek gebeurt
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(0.1));
		o->addComponent(new MoveToComponent());

		o->position = Vec3f(0, 0, 30);
		o->getComponent<MoveToComponent>()->target = Vec3f(-1.5, 0.6, -5);

		objects.push_back(o);
	}
}
