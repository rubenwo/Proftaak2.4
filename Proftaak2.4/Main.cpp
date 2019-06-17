/*
	Engine functionality
*/
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <GL\freeglut.h>
#include "Globals.hpp"
#include "Game.hpp"
#include <opencv2/highgui.hpp>
#include "Tracker.hpp"
#include <atomic>
#include "HTTPRequest.hpp"

#define APP_NAME "Game"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

using namespace std;

int windowWidth;
int windowHeight;

struct Camera
{
	float posX = 0;
	float posY = 0;
	float rotX = 0;
	float rotY = 0;
	float posZ = 0;
	float rotZ = 0;
} camera;

void reshape(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y)
{
	Game::onKey(key);
}

void keyboardup(unsigned char key, int x, int y)
{
	Game::onKeyUp(key);
}

void mousePassiveMotion(int x, int y)
{
	Game::onMouseMove(x, y);
}

void specialKey(int key, int x, int y)
{
	Game::onKey(key);
}

void specialKeyUp(int key, int x, int y)
{
	Game::onKeyUp(key);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, windowWidth / (float)windowHeight, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Game::draw();

	glutSwapBuffers();
}

bool initGlut(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInit(&argc, argv);
	glutCreateWindow(APP_NAME);
	glutDisplayFunc(display);
	glutIdleFunc(Game::idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialKeyUp);
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
	try
	{
		http::Request request("http://rubenwoldhuis.nl/highscore/test");
		http::Response response = request.send("GET");
		if (response.status == 200)
		{
			string result(response.body.begin(), response.body.end());
			std::cout << result << std::endl;
		}
		else
		{
			std::cout << "internal server error occurred" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Request failed, error: " << e.what() << std::endl;
	}


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
	Game::onResize(windowWidth, windowHeight);

	// Start loading in game content.
	Game::loadContent();

	// Start game.
	glutMainLoop();

	Game::onClose();

	return EXIT_SUCCESS;
}
