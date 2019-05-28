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
#include "Menu.h"

namespace Game
{
	int windowWidth, windowHeight;
	bool keys[256];
	Texture *texturess;

	Level currentLevel;

	Camera camera;
	GameObject player;

	//Menu menu(1);



	void loadContent()
	{
		ZeroMemory(keys, sizeof(keys));

		camera = Camera(0, -4, 0, 0);

		loadTextures();

		currentLevel = Level(texturess);
		currentLevel.loadContent();
		
		player = GameObject();
		player.position = Vec3f(0, 0, -1);
		player.addComponent(new PlayerComponent(1.0f, 1));
	}

	void update(float deltaTime)
	{
		currentLevel.update(deltaTime);
		//menu.update(deltaTime);
	}

	void draw()
	{
		currentLevel.draw();
		//menu.draw();
		player.draw();
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

	void loadTextures()
	{
		texturess = new Texture("texture");
		texturess->initTextures();
	}
}
