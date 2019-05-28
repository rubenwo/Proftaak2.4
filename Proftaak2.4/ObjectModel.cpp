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

void Texture::initTextures() {
	glGenTextures(2, textures);
	loadTextureFromFile(textureFilenameCube, textures[0]);
	loadTextureFromFile(textureFilenameWalls, textures[1]);
	loadTextureFromFile(textureFilenameLogo, textures[2]);
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
