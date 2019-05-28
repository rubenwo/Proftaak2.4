#include "ObjectModel.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GL/freeglut.h"

const char* textureFilenameCube = "textures12.png";
const char* textureFilenameWalls = "wallTexture.png";
const char* textureFilenameLogo = "smacky_logo_big.png";
const char* textureFilenameCredits = "credits.png";
const char* textureFilenameOptions = "options.png";
const char* textureFilenameQuit = "quit.png";
const char* textureFilenameStart = "start.png";

Texture::Texture(const std::string &dirName) {

}
GLuint Texture::getTextureId()
{
	return blockTextureId;
}

GLuint Texture::getWallTextureId()
{
	return wallTextureId;
}

GLuint Texture::getLogoTextureId()
{
	return logoTextureId;
}

void Texture::initTextures() {
	glGenTextures(7, textures);
	loadTextureFromFile(textureFilenameCube, textures[0]);
	loadTextureFromFile(textureFilenameWalls, textures[1]);
	loadTextureFromFile(textureFilenameLogo, textures[2]);
	loadTextureFromFile(textureFilenameCredits, textures[3]);
	loadTextureFromFile(textureFilenameOptions, textures[4]);
	loadTextureFromFile(textureFilenameQuit, textures[5]);
	loadTextureFromFile(textureFilenameStart, textures[6]);
}

void Texture::loadTextureFromFile(const char *filename, int texture)
{
	int width, height, bpp;
	unsigned char* imgData = stbi_load(filename, &width, &height, &bpp, 4);

	if (!imgData)
	{
		std::cout << "Image could not be loaded succesfully!\r\n" << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D,
		0,					//level
		GL_RGBA,			//internal format
		width,				//32,		//width
		height,				//32,		//height
		0,					//border
		GL_RGBA,			//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData);			//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(imgData);
}
