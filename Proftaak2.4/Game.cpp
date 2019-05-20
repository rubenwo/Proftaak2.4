#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>

#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include "PlayerComponent.h"

namespace Game
{
	int windowWidth, windowHeight;
	bool keys[256];

	Camera camera;
	std::list<GameObject*> objects;
	//GameObject* player;
	//CameraComponent* camComponent;

	void loadContent(HandTracker& tracker)
	{
		ZeroMemory(keys, sizeof(keys));
		camera = Camera(0, -4, 0, 0);

		GameObject* o = new GameObject();
		//o->addComponent(new CubeComponent(0.5));
		//HandTracker tracker(windowWidth, windowHeight);
		o->addComponent(new PlayerComponent(tracker));


		o->position = Vec3f(0, 0, -2);

		objects.push_back(o);
	}

	void update(float deltaTime)
	{
		for (const auto& o : objects)
			o->update(deltaTime);
	}

	void draw()
	{
		//glRotatef(camera.rotX, 1, 0, 0);
		//glRotatef(camera.rotY, 0, 1, 0);
		//glTranslatef(camera.posX, 0, camera.posY);

		// Floor
		glColor3f(0.1f, 1.0f, 0.2f);

		glBegin(GL_QUADS);
		glVertex3f(-15, -1, -15);
		glVertex3f(15, -1, -15);
		glVertex3f(15, -1, 15);
		glVertex3f(-15, -1, 15);
		glEnd();
		glColor3f(0.5f, 0.8f, 0.2f);
		for (const auto& o : objects)
			o->draw();
		//glBegin(GL_QUADS);
		//glVertex3f(-15, -1, -15);
		//glVertex3f(15, -1, -15);
		//glVertex3f(15, -1, 15);
		//glVertex3f(-15, -1, 15);
		//glEnd();
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
}
