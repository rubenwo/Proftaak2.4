#include "Engine.hpp"
#include <GL\freeglut.h>
#include <iostream>


Engine::Engine()
{

}


void display()
{

}

void idle()
{

}

void Engine::reshape(int w, int h)
{

}

void keyboard(unsigned char key, int x, int  y)
{
	
}

void keyboardUp(unsigned char key, int x, int  y)
{

}
void Engine::init(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInit(&argc, argv);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
}
void Engine::run(int argc, char** argv)
{
	init(argc, argv);
	loadContent();

	
}

void Engine::gameLoop()
{

}

void Engine::close()
{

}