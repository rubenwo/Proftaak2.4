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
#include <functional>

namespace Game
{
	int windowWidth, windowHeight;
	bool keys[256];
	Texture* texturess;
	Level currentLevel;
	Camera camera;
	GameObject* player;


	//Menu menu(1);

	void (*onObjectCollision)(GameObject* obj, Vec2f pos);

	void loadContent()
	{
		ZeroMemory(keys, sizeof keys);
		camera = Camera(0, -4, 0, 0, 0, 0);
		loadTextures();

		// std::function<void(GameObject*, Vec2f)> onCollision = std::bind(onObjectCollision, std::placeholders::_1, std::placeholders::_2);

		currentLevel = Level(texturess);
		currentLevel.loadContent();

		player = new GameObject();
		player->position = Vec3f(0, 0, -1);
		player->addComponent(new PlayerComponent(&currentLevel.objects, texturess->textures[3], 0.25f));		//fix texturess->textures[3]
		player->getComponent<PlayerComponent>()->setCollisionCallback([](GameObject* obj)
		{
			obj->removeComponent<DrawComponent>();
			//TODO explosion
		});
	}


	void update(float deltaTime)
	{
		player->update(deltaTime);
		currentLevel.update(deltaTime);
		//menu.update(deltaTime);
	}

	void draw()
	{
		//menu.draw();
		player->draw();
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

	void loadTextures()
	{
		texturess = new Texture("texture");
		texturess->initTextures();
	}

	int lastTime = 0;

	void idle()
	{
		int currentTime = glutGet(GLUT_ELAPSED_TIME);
		float deltaTime = (currentTime - lastTime) / 1000.0f;

		lastTime = currentTime;
		//
		// const float speed = 3;
		// if (keys['a']) move(0, deltaTime*speed);
		// if (keys['d']) move(180, deltaTime*speed);
		// if (keys['w']) move(90, deltaTime*speed);
		// if (keys['s']) move(270, deltaTime*speed);
		//
		// //glutWarpPointer(windowWidth / 2, windowHeight / 2);
		//
		// if (keys[0]) { //UP ARROW KEY
		// 	camera.posZ -= 0.025f;
		// }
		// if (keys[1]) { //DOWN ARROW KEY
		// 	camera.posZ += 0.025f;
		// }

		// update
		Game::update(deltaTime);

		glutPostRedisplay();
	}
}
