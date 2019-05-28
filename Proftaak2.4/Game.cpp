#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>
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
	GameObject* player;

	//Menu menu(1);

	void loadContent()
	{
		ZeroMemory(keys, sizeof keys);
		camera = Camera(0, -4, 0, 0, 0, 0);
		currentLevel = Level();

		currentLevel.loadContent();

		loadTextures();

		currentLevel = Level(texturess);
		currentLevel.loadContent();

		player = new GameObject();
		player->position = Vec3f(0, 0, -1);
		player->addComponent(new PlayerComponent(&currentLevel.objects, 3, 1.0f));

	}

	void update(float deltaTime)
	{
		player.update(deltaTime);
		currentLevel.update(deltaTime);
		//menu.update(deltaTime);
	}

	void draw()
	{
	    currentLevel.draw();
		//menu.draw();
		player->draw();
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
		case GLUT_KEY_UP:
			camera.posZ -= 0.025f;
			break;
		case GLUT_KEY_DOWN:
			camera.posZ += 0.025f;
			break;
		default:
			break;
		}
	}

	void onMouseMove(int x, int y)
	{
		//static bool justMovedMouse = false;
		//int dx = x - windowWidth / 2;
		//int dy = y - windowHeight / 2;
		//if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400 && !justMovedMouse)
		//{
		//	camera.rotY += dx / 10.0f;
		//	camera.rotX += dy / 10.0f;
		//}
		//if (!justMovedMouse)
		//{
		//	//glutWarpPointer(windowWidth / 2, windowHeight / 2);
		//	justMovedMouse = true;
		//}
		//else
		//	justMovedMouse = false;
	}

	void onResize(int w, int h)
	{
		windowWidth = w;
		windowHeight = h;
	}

	void onClose()
	{
		std::cout << "Cleaning up game\n";

		std::cout << "Closing game.\n";
	}

	void move(float angle, float fac)
	{
		camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
		camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
	}
	
	void loadTextures()
	{
		texturess = new Texture("texture");
		texturess->initTextures();
	}
}
