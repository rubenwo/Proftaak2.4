#include <GL\freeglut.h>
#include <opencv2\highgui\highgui.hpp>

#include <math.h>
#include "GameObject.h"
#include "CubeComponent.h"
#include "SpinComponent.h"
#include "PlayerComponent.h"
#include "MoveToComponent.h"
#include "TimerJumper.h"

int height = 800;
int width = 1200;
GameObject* player;


bool keys[256];


std::list<GameObject*> objects;

void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int  y)
{
	keys[key] = true;
	if (key == 27)
		exit(0);
}

void keyboardup(unsigned char key, int x, int y)
{
	keys[key] = false;
}


void init()
{
	glEnable(GL_DEPTH_TEST);

	ZeroMemory(keys, sizeof(keys));

	for (int i = -10; i < 10; i++)
	{
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(0.5));
		o->position = Vec3f(i, 0, 0);
		objects.push_back(o);
	}

	{
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(1.0));
		o->addComponent(new PlayerComponent());
		o->addComponent(new SpinComponent(100));
		o->position = Vec3f(0, 0, 0);
		objects.push_back(o);

		player = o;
	}

	{
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(1.0));
		o->addComponent(new SpinComponent(50));
		o->addComponent(new MoveToComponent());
		o->addComponent(new TimerJumper(Vec3f(5, 0, 0), Vec3f(-5, 0, 0)));
		o->position = Vec3f(10, 0, 0);
		objects.push_back(o);
	}
}

void display()
{
	glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, width / (float)height, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -5, 5,
		player->position.x, player->position.y, player->position.z,
		0, 1, 0);


	for (auto& o : objects)
		o->draw();


	glutSwapBuffers();
}


int lastTime = 0;
void idle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	for (auto& o : objects)
		o->update(deltaTime);

	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);

	//opengl init
	init();

	glutMainLoop();

	return 0;
}



