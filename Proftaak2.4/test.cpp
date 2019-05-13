#include <GL\freeglut.h>

int windoWidth, windowHeight;

void display()
{

}

void idle()
{

}

void reshape(int w, int h)
{
	windoWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int  y)
{

}

void keyboardUp(unsigned char key, int x, int  y)
{

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