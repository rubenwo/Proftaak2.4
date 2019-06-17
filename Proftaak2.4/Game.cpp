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
#include "SoundPlayer.hpp"
#include "Util.hpp"
#define FPS_COUNTER
#ifdef FPS_COUNTER
#include "FrameRateCounter.hpp"
#endif

namespace Game
{
#ifdef FPS_COUNTER
	FrameRateCounter frc;
#endif
	int windowWidth, windowHeight;
	bool keys[256];
	Texture* texturess;
	Level currentLevel;
	Camera camera;
	int index;
	bool start,isStarted;

	Menu menu;

	void (*onObjectCollision)(GameObject* obj, Vec2f pos);

	void loadContent()
	{
		ZeroMemory(keys, sizeof keys);
		camera = Camera(0, -4, 0, 0, 0, 0);
		
		SoundPlayer& sp = SoundPlayer::getInstance();
		sp.setListenerPosition(Vec3f(camera.posX, camera.posY, camera.posZ), Vec3f(camera.rotX, camera.rotY, camera.rotZ));
		loadTextures();
		currentLevel = Level(texturess);
		currentLevel.loadContent();

		index = 1;
		isStarted = false;

		menu = Menu(texturess->textures[2], texturess->textures[3], texturess->textures[8], texturess->textures[4],
			texturess->textures[9], texturess->textures[5], texturess->textures[10], texturess->textures[6],
			texturess->textures[11]);
	}


	void update(float deltaTime)
	{
		//currentLevel.update(deltaTime);
		//menu.update(deltaTime, index);
#ifdef FPS_COUNTER
		frc.update(deltaTime);
#endif
		if (start) {
			if (!isStarted) {
				currentLevel.start();
				isStarted = true;
			}

			currentLevel.update(deltaTime);
		}
		else {
			menu.update(deltaTime, index);
		}
	}

	void draw()
	{
#ifdef FPS_COUNTER
		float avgFrames= frc.getAverageFramesPerSecond();
		std::string avgStr = std::to_string(avgFrames);
		std::string fps = "FPS: " + avgStr.substr(0, avgStr.find_last_of('.'));
		Util::drawText(Color4(255, 255, 255, 1), Vec2f(20, windowHeight - 40), windowWidth, windowHeight, fps);
#endif
		if (start) {
			currentLevel.draw();
		}
		else {
			menu.draw();
		}
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
			if (index >= 1 && index < 4) {
				index++;
			}
			break;
		case GLUT_KEY_DOWN:
			camera.posZ += 0.025f;
			if (index > 1 && index <= 4) {
				index--;
			}
			break;
		case VK_RETURN:
			if (index == 1) {
				start = true;
			}
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
