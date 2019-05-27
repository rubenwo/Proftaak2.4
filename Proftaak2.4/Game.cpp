#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>
#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include "PlayerComponent.h"
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
		o->position = Vec3f(0, 0, -1);
		objects.push_back(o);
		o->addComponent(new PlayerComponent());
		GameObject* o = new GameObject();
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
