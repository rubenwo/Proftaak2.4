#pragma once

class Menu {

	GLuint mtextureID;

public:
	Menu(GLuint textureID);
	~Menu();

	void draw();
	void update(float elapsedTime);

};