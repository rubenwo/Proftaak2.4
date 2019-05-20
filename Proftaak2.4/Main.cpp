/*
	Engine functionality
*/
#include <iostream>
#include <GL\freeglut.h>
#include "Globals.hpp"
#include "Game.hpp"
#include "ObjectModel.h"

#define APP_NAME "Game"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800


int windowWidth;
int windowHeight;
GLuint texture1;
const char* textureFilename = "textures12.png";

void reshape(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int  y)
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

int lastTime = 0;

void idle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	Game::update(deltaTime);
	// update

	glutPostRedisplay();
}

bool initGlut(int argc, char** argv)
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
	Texture texture = Texture(textureFilename);
	texture.loadTextureFromFile(textureFilename);
	texture1 = texture.getTextureId();

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

/*
void display()
{
	glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, windowWidth / (float)windowHeight, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0, -5, 5,
	//	player->position.x, player->position.y, player->position.z,
	//	0, 1, 0);

	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glRotatef(camera.rotZ, 0, 0, 1);
	glTranslatef(camera.posX, camera.posZ, camera.posY);

	for (auto& o : objects)
		o->draw();

	glutSwapBuffers();
}

void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

int lastTime = 0;
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

	if (skeys[0]) { //UP ARROW KEY
		camera.posZ -= 0.025;
	}
	if (skeys[1]) { //DOWN ARROW KEY
		camera.posZ += 0.025;
	}

	for (auto& o : objects)
		o->update(deltaTime);

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Program");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	//Regular keys:
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);

	//Special keys:
	glutSpecialFunc(specialKeys);
	glutSpecialUpFunc(specialKeysUp);
	
	//Texture loading:

	//opengl init
	init();

	glutPassiveMotionFunc(mousePassiveMotion);
	glutWarpPointer(width / 2, height / 2);
	glutMainLoop();
	return 0;
}
*/

