#ifndef GLOBALS_HPP
#define GLOBALS_HPP
// Status codes
#define GLUT_INIT_FAILED 1
#define OPENGL_INIT_FAILED 2

typedef unsigned char Key;

struct Color4
{
	float r, g, b, a;
	Color4(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
};

#endif