#include "ObjectModel.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GL/freeglut.h"

GLuint  textureId;         // Storage For One Texture ( NEW )

Texture::Texture(const std::string &dirName) {


}
GLuint Texture::getTextureId()
{
	return textureId;
}

void Texture::loadTextureFromFile(const char *filename)
{
	// glClearColor(0.0, 0.0, 0.0, 0.0);
	// glShadeModel(GL_FLAT);
	// glEnable(GL_DEPTH_TEST);

	int width, height, bpp;
	unsigned char* imgData = stbi_load(filename, &width, &height, &bpp, 4);

	if (!imgData)
	{
		std::cout << "Image could not be loaded succesfully!\r\n" << std::endl;
	}

	//glRotatef(180, 1, 0, 1);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);


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
