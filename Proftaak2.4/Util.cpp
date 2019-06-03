#include "Util.hpp"
#include "Globals.hpp"
#include <GL\freeglut.h>
#include <Windows.h>
#include "Vec.h"

namespace Util
{
	void drawText(const Color4& clr, const Vec2f& pos, int windowWidth, int windowHeight, const std::string& text)
	{
		glColor4f(clr.r / 255.0f, clr.g / 255.0f, clr.b / 255.0f, clr.a);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, windowWidth, 0, windowHeight);
		glRasterPos2i(pos.x, pos.y);

		const unsigned char* str = reinterpret_cast<const unsigned char *>(text.c_str());
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

	std::string getExePath()
	{
		HMODULE handle = GetModuleHandle(NULL);

		if (handle == NULL)
			return "";
		char path[MAX_PATH];
		GetModuleFileName(handle, path, (sizeof(path)));
		std::string pathStr = std::string(path);
		const size_t index = pathStr.find_last_of("/\\");
		
		return pathStr.substr(0, index);
	}
}