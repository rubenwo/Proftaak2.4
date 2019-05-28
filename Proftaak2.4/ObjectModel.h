#pragma once

#include <string>
#include <vector>
#include <list>
#include <windows.h>
#include <gl/GL.h>
//#include "Vec.h"


class Texture
{
public:
	GLuint textures[10];
	Texture(const std::string &dirName);
	const std::string dirName;
	void initTextures();
	GLuint getTextureId();
	GLuint getWallTextureId();
	GLuint getLogoTextureId();
	GLuint wallTextureId;
	GLuint logoTextureId;
	GLuint blockTextureId;
	GLuint * getTextures();

	void loadTextureFromFile(const char* filename, int texture);
};