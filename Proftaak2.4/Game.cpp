#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>
#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include "MoveToComponent.h"
#include "StageComponent.h"
#include "ObjectModel.h"
#include "Level.h"

namespace Game
{
	int windowWidth, windowHeight;
	bool keys[256];
	Level currentLevel;

	Camera camera;

	void loadContent() {
		ZeroMemory(keys, sizeof(keys));
		camera = Camera(0, -4, 0, 0);
		currentLevel = Level();
		currentLevel.loadContent();
	}

	void update(float deltaTime)
	{
		currentLevel.update(deltaTime);

	}

	void draw()
	{
		currentLevel.draw();
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
