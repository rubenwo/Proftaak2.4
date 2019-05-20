#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>

#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include "MoveToComponent.h"
#include "StageComponent.h"

namespace Game
{
	int windowWidth, windowHeight;
	bool keys[256];

	Camera camera;
	std::list<GameObject*> objects;

	void createMovingCubeRight(float height = 0);
	void createMovingCubeLeft(float height = 0);	

	void loadContent()
	{
		ZeroMemory(keys, sizeof(keys));
		camera = Camera(0, -4, 0, 0);

		// //Load room with TODO textures
		GameObject* room = new GameObject();
		room->addComponent(new StageComponent());
		objects.push_back(room);

		//EXAMPLE CUBES
		createMovingCubeRight(1);
		createMovingCubeLeft();
	}

	void update(float deltaTime)
	{
		for (const auto& o : objects)
		{
			o->update(deltaTime);
			//
			// if (o->position.z == o->getComponent<MoveToComponent>()->target.z)
			// 	objects.remove(o);
		}
	}

	void draw()
	{
		glRotatef(180, 1, 0, 0);

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

	void createMovingCubeRight(float height)
	{
		//Add moving cube right side of platform, TODO zorg ervoor dat dit gebaseerd op muziek gebeurt
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(0.2f, 1, HAND::rightHand, ARROWDIRECTION::right));
		o->addComponent(new MoveToComponent());

		o->position = Vec3f(2, 0, 30);
		o->getComponent<MoveToComponent>()->target = Vec3f(1.5, -height + 0.6, -5);

		objects.push_back(o);
	}

	void createMovingCubeLeft(float height)
	{
		//Add moving cube right side of platform, TODO zorg ervoor dat dit gebaseerd op muziek gebeurt
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(0.2f, 1, HAND::leftHand, ARROWDIRECTION::down));
		o->addComponent(new MoveToComponent());

		o->position = Vec3f(-2, 0, 30);
		o->getComponent<MoveToComponent>()->target = Vec3f(-1.5, -height + 0.6, -5);

		objects.push_back(o);
	}
}
