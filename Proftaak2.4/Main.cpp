/*
	Engine functionality
*/
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <GL\freeglut.h>
#include "Globals.hpp"
#include "Game.hpp"
#include "ObjectModel.h"
#include <math.h>

#define APP_NAME "Game"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

using namespace std;

struct Camera
{
	float posX = 0;
	float posY = -4;
	float rotX = 0;
	float rotY = 0;
	float posZ = 0;
	float rotZ = 0;
} camera;

bool keys[256];
bool skeys[5]; //for arrow keys


int windowWidth = 1200;
int windowHeight = 800;

void reshape(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
}

//void keyboard(unsigned char key, int x, int  y)
//{
//	Game::onKey(key);
//}
//
//void keyboardup(unsigned char key, int x, int y)
//{
//	Game::onKeyUp(key);
//}
//
//void mousePassiveMotion(int x, int y)
//{
//	Game::onMouseMove(x, y);
//}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, windowWidth / (float)windowHeight, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glRotatef(camera.rotZ, 0, 0, 1);
	glTranslatef(camera.posX, camera.posZ, camera.posY);

	Game::draw();

	glutSwapBuffers();
}

int lastTime = 0;

void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

void idle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	const float speed = 3;
	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);

	glutWarpPointer(windowWidth / 2, windowHeight / 2);

	if (skeys[0]) { //UP ARROW KEY
		camera.posZ -= 0.025;
	}
	if (skeys[1]) { //DOWN ARROW KEY
		camera.posZ += 0.025;
	}

	Game::update(deltaTime);
	// update

	glutPostRedisplay();
}



bool justMovedMouse = false;
void mousePassiveMotion(int x, int y)
{
	int dx = x - windowWidth / 2;
	int dy = y - windowHeight / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400 && !justMovedMouse)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
	}
	if (!justMovedMouse)
	{
		//glutWarpPointer(windowWidth / 2, windowHeight / 2);
		justMovedMouse = true;
	}
	else
		justMovedMouse = false;
}

void keyboard(unsigned char key, int x, int  y)
{
	keys[key] = true;
	if (key == 27)
		exit(0);

	cout << "Key: " << key << std::endl;
}

void keyboardup(unsigned char key, int x, int y)
{
	keys[key] = false;
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		skeys[0] = true;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		skeys[1] = true;
		glutPostRedisplay();
		break;
	}
	std::cout << "Special key: " << key << std::endl;
}

void specialKeysUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		skeys[0] = false;
		break;
	case GLUT_KEY_DOWN:
		skeys[1] = false;
		break;
	}
}

bool initGlut(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInit(&argc, argv);
	glutCreateWindow(APP_NAME);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	return true;
}

bool initOpenGL()
{
	glEnable(GL_DEPTH_TEST);

	return true;
}
int main(int argc, char** argv)
{
	windowWidth = WINDOW_WIDTH;
	windowHeight = WINDOW_HEIGHT;

	if (initGlut(argc, argv))
		std::cout << "Succesfully initialized glut.\n";
	else
	{
		std::cout << "Failed initializing glut.\n";
		return GLUT_INIT_FAILED;
	}

	if (initOpenGL())
		std::cout << "Succesfully initialized OpenGL.\n";
	else
	{
		std::cout << "Failed initializing OpenGL.\n";
		return OPENGL_INIT_FAILED;
	}

	// Start loading in game content.
	Game::loadContent();

	Game::onResize(windowWidth, windowHeight);
	// Start game.
	glutMainLoop();

	Game::onClose();

	return EXIT_SUCCESS;
}